#ifndef BOX2DLIS_H_
#define BOX2DLIS_H_


extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <Box2D/Box2D.h>
class Box2dLis :  public b2ContactListener {
public:
	Box2dLis();
	 ~Box2dLis();

	 void BeginContact(b2Contact* contact);
	 void EndContact(b2Contact* contact);
	 void setLua(lua_State* m_luaState);

private:
	 lua_State* m_luaState;
};

#endif /* BOX2DLIS_H_ */
