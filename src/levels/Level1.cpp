extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <levels/Level1.h>
#include <lua-exports/ExportBox2d.h>
#include <game-objects/Rope.h>
#include <lua-exports/B2WorldProxy.h>
#include <utilities/Bitwise.h>
#include <SFML/System.hpp>
#include <luabind/luabind.hpp>
#include <components/IgnoreCollisionComponent.h>
#include <components/PhysicsComponent.h>
#include <iostream>

class Level1::Level1Impl {

public:
	lua_State* m_luaState;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;
	B2WorldProxy box2dWorldProxy;
	std::vector<b2Fixture*> m_fixturesInterestedInCollisions;

	Level1Impl(b2World& b2dworld, anax::World& anaxWorld) :
			m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld), box2dWorldProxy(b2dworld) {
		m_luaState = luaL_newstate();
		luabind::open(m_luaState);
		luaL_openlibs(m_luaState);

		if (luaL_dofile(m_luaState, "lua-scripts/levels/level1.lua")) {
			printf("%s\n", lua_tostring(m_luaState, -1));
		}

	}

	~Level1Impl() {

	}

	void loadLevel(std::unordered_map<std::string, tmx::MapObject>& levelObjects) {

		ExportBox2d exportBox2d;
		exportBox2d.exportToLua(m_luaState);

		luabind::module(m_luaState)[
		luabind::class_<sf::Time>("sf_Time")
		      .def(luabind::constructor<>())
			  .def("asSeconds",  &sf::Time::asSeconds)
			  .def("asMilliseconds",  &sf::Time::asMilliseconds)

		];

		luabind::module(m_luaState)[
		luabind::class_<sf::Clock>("sf_Clock")
		      .def(luabind::constructor<>())
			  .def("getElapsedTime",  &sf::Clock::getElapsedTime)
		];

		Rope rope(*m_box2dWorld, *m_anaxWorld);
		b2Body* ropeBox = rope.createRope();
		std::cout << ropeBox->GetPosition().x << std::endl;

//		luabind::object table = luabind::newtable( m_luaState );
//		table[ "RopeBox" ] = ropeBox;
		luabind::globals(m_luaState)["RopeBox"] = ropeBox;
		luabind::globals(m_luaState)["testi"] = 1;

		try {
			luabind::call_function<void>(m_luaState, "init", &box2dWorldProxy);
		} catch (luabind::error& e) {
			std::string error = lua_tostring(e.state(), -1);
			std::cout << error << std::endl;
		}

		try {
			luabind::object levels =  luabind::call_function<luabind::object>(m_luaState, "getFixturesInterestedInCollisions");
			for(int i = 1; ; i++){
				if(levels[i]){
					b2Fixture* collisionFixture =  luabind::object_cast<b2Fixture*>(levels[i]);
				    m_fixturesInterestedInCollisions.push_back(collisionFixture);

				}else{
					break;
				}
			}
		} catch (luabind::error& e) {
		    std::string error = lua_tostring(e.state(), -1);
		    std::cout << error << std::endl;
		}
	}

	void updateLevel() {
		try {
			luabind::call_function<void>(m_luaState, "update");
		} catch (luabind::error& e) {
			std::string error = lua_tostring(e.state(), -1);
			std::cout << error << std::endl;
		}
	}

	void endLevel() {
		lua_close(m_luaState);
	}

	bool shouldIgnore(b2Contact* contact){
		anax::World::EntityArray entities = m_anaxWorld->getEntities();
		for(auto entity : entities){
			if(entity.isValid() && entity.hasComponent<PhysicsComponent>() && entity.hasComponent<IgnoreCollisionComponent>()){
				auto& physicsComp = entity.getComponent<PhysicsComponent>();
				b2Fixture* fixtureToCompare = physicsComp.physicsBody->GetFixtureList();
				while(fixtureToCompare){
					if(fixtureToCompare == contact->GetFixtureA() || fixtureToCompare == contact->GetFixtureB()){
						std::cout << "about to mark as deleted" << std::endl;
						return true;
					}
					fixtureToCompare = fixtureToCompare->GetNext();
				}
			}
		}
		return false;
	}

	void filterContacts(b2Contact* contact,  const char* luaScriptFunctionName){
		if (!shouldIgnore(contact)) {
			for (auto fixture : m_fixturesInterestedInCollisions) {
				if (fixture == contact->GetFixtureA() || fixture == contact->GetFixtureB()) {
					try {
						luabind::call_function<void>(m_luaState,
								luaScriptFunctionName, contact);
					} catch (luabind::error& e) {
						std::string error = lua_tostring(e.state(), -1);
						std::cout << error << std::endl;
					}
				}
			}
		}
	}

	void beginContact(b2Contact* contact) {
		filterContacts(contact, "beginCollision");
	}

	void endContact(b2Contact* contact) {
		filterContacts(contact, "endCollision");
	}

};

Level1::Level1(b2World& b2dworld, anax::World& anaxWorld) :
		m_impl(new Level1Impl(b2dworld, anaxWorld)) {
}

Level1::~Level1() {
}

void Level1::loadLevel(std::unordered_map<std::string, tmx::MapObject>& levelObjects) {
	m_impl->loadLevel(levelObjects);
}

void Level1::updateLevel() {
	m_impl->updateLevel();
}

void Level1::endLevel() {
	m_impl->endLevel();
}

void Level1::BeginContact(b2Contact* contact) {
	m_impl->beginContact(contact);
}

void Level1::EndContact(b2Contact* contact) {
	m_impl->endContact(contact);
}
