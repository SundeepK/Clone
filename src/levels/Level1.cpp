extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}
#include <luabind/luabind.hpp>

#include <levels/Level1.h>
#include <lua-exports/ExportBox2d.h>
#include <lua-exports/B2WorldProxy.h>
#include <utilities/Bitwise.h>
#include <SFML/System.hpp>
#include <components/IgnoreCollisionComponent.h>
#include <components/PhysicsComponent.h>
#include <iostream>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <lua-exports/ExportSFML.h>

class LuaScriptLevel::LuaScriptLevelImpl {

public:
	lua_State* m_luaState;
	B2WorldProxy box2dWorldProxy;
	std::vector<b2Fixture*> m_fixturesInterestedInCollisions;
	bool shouldCallScript = false;

	LuaScriptLevelImpl(b2World& b2dworld, std::string levelScriptName) : box2dWorldProxy(b2dworld) {
		m_luaState = luaL_newstate();
		luabind::open(m_luaState);
		luaL_openlibs(m_luaState);

		if(!levelScriptName.empty()){
			shouldCallScript = true;

			std::string scriptPath = "lua-scripts/levels/" + levelScriptName;
			if (luaL_dofile(m_luaState, scriptPath.c_str())) {
				printf("%s\n", lua_tostring(m_luaState, -1));
			}

			ExportBox2d exportBox2d;
			exportBox2d.exportToLua(m_luaState);

			ExportSFML exportSFML;
			exportSFML.exportToLua(m_luaState);
		}


	}

	~LuaScriptLevelImpl() {

		lua_close(m_luaState);
		std::cout << "deleted lua state" << std::endl;
	}

	void loadLevel(std::vector<tmx::MapObject>& levelObjects) {

		if(!shouldCallScript)
			return;

		std::cout << "loadlelve in c++" << std::endl;

		try {
			luabind::call_function<void>(m_luaState, "init", &box2dWorldProxy);
		} catch (luabind::error& e) {
			std::string error = lua_tostring(e.state(), -1);
			std::cout << error << std::endl;
		}

		for (auto object : levelObjects) {
			if (!object.GetName().empty()) {
				try {
					luabind::call_function<void>(m_luaState, "loadMapObject", object.GetName(), object);
				} catch (luabind::error& e) {
					std::string error = lua_tostring(e.state(), -1);
					std::cout << error << std::endl;
				}
			}
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
		if(!shouldCallScript)
			return;

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
//		anax::World::EntityArray entities = m_anaxWorld.getEntities();
//		for(auto entity : entities){
//			if(entity.isValid() && entity.hasComponent<PhysicsComponent>() && entity.hasComponent<IgnoreCollisionComponent>()){
//				auto& physicsComp = entity.getComponent<PhysicsComponent>();
//				b2Fixture* fixtureToCompare = physicsComp.physicsBody->GetFixtureList();
//				while(fixtureToCompare){
//					if(fixtureToCompare == contact->GetFixtureA() || fixtureToCompare == contact->GetFixtureB()){
//						return true;
//					}
//					fixtureToCompare = fixtureToCompare->GetNext();
//				}
//			}
//		}
		return false;
	}

	void filterContacts(b2Contact* contact,  const char* luaScriptFunctionName){
		if(!shouldCallScript)
			return;

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

	void beginContact(b2Contact* contact) {
		//filterContacts(contact, "beginCollision");
	}

	void endContact(b2Contact* contact) {
	//	filterContacts(contact, "endCollision");
	}

};

LuaScriptLevel::LuaScriptLevel(b2World& b2dworld, std::string luaScriptLevel) :
		m_impl(new LuaScriptLevelImpl(b2dworld, luaScriptLevel)) {
}

LuaScriptLevel::~LuaScriptLevel() {
}

void LuaScriptLevel::loadLevel(std::vector<tmx::MapObject>& levelObjects) {
	m_impl->loadLevel(levelObjects);
}

void LuaScriptLevel::updateLevel() {
	m_impl->updateLevel();
}

void LuaScriptLevel::endLevel() {
	m_impl->endLevel();
}

void LuaScriptLevel::BeginContact(b2Contact* contact) {
	m_impl->beginContact(contact);
}

void LuaScriptLevel::EndContact(b2Contact* contact) {
	m_impl->endContact(contact);
}
