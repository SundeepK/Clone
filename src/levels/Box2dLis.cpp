#include <levels/Box2dLis.h>

Box2dLis::Box2dLis() {

}

Box2dLis::~Box2dLis() {
	// TODO Auto-generated destructor stub
}

void Box2dLis::BeginContact(b2Contact* contact) {
	std::cout << "begion c++" << std::endl;

	try {
		luabind::call_function<void>(m_luaState, "beginCollision");
	} catch (luabind::error& e) {
		std::string error = lua_tostring(e.state(), -1);
		std::cout << error << std::endl;
	}
}

void Box2dLis::EndContact(b2Contact* contact) {
	try {
		luabind::call_function<void>(m_luaState, "beginCollision");
	} catch (luabind::error& e) {
		std::string error = lua_tostring(e.state(), -1);
		std::cout << error << std::endl;
	}
}

void Box2dLis::setLua(lua_State* luaState) {
	m_luaState = luaState;
}
