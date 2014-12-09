#include <levels/Level1.h>
#include <lua-exports/ExportBox2d.h>
#include <game-objects/Rope.h>

class Level1::Level1Impl {

public:
	lua_State* m_luaState;
	std::unique_ptr<b2World> m_box2dWorld;
	std::unique_ptr<anax::World> m_anaxWorld;


	Level1Impl(b2World& b2dworld, anax::World& anaxWorld, Box2dLis& lis) :
			m_box2dWorld(&b2dworld), m_anaxWorld(&anaxWorld) {
		if (luaL_dofile(m_luaState, "lua-scripts/levels/level1.lua")) {
			printf("%s\n", lua_tostring(m_luaState, -1));
		}

		m_luaState = luaL_newstate();
		luabind::open(m_luaState);
		luaL_openlibs(m_luaState);
		lis.setLua(m_luaState);
	}

	~Level1Impl() {

	}

	void loadLevel(std::unordered_map<std::string, tmx::MapObject>& levelObjects) {


		ExportBox2d exportBox2d;
		exportBox2d.exportToLua(m_luaState);

		Rope rope(*m_box2dWorld, *m_anaxWorld);
		b2Body* ropeBox = rope.createRope();
		std::cout << ropeBox->GetPosition().x << std::endl;

//		luabind::object table = luabind::newtable( m_luaState );
//		table[ "RopeBox" ] = ropeBox;
		luabind::globals(m_luaState)["RopeBox"] = ropeBox;
		luabind::globals(m_luaState)["testi"] = 1;

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

	void beginContact(b2Contact* contact) {
		try {
			luabind::call_function<void>(m_luaState, "beginCollision");
		} catch (luabind::error& e) {
			std::string error = lua_tostring(e.state(), -1);
			std::cout << error << std::endl;
		}
	}

	void endContact(b2Contact* contact) {
		try {
			luabind::call_function<void>(m_luaState, "beginCollision");
		} catch (luabind::error& e) {
			std::string error = lua_tostring(e.state(), -1);
			std::cout << error << std::endl;
		}
	}

};

Level1::Level1(b2World& b2dworld, anax::World& anaxWorld, SensorSystem& sensor) :
		m_impl(new Level1Impl(b2dworld, anaxWorld, m_lis)) {
	sensor.registerb2ContactListener(&m_lis);
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
