#ifndef LUAENTITYLOADER_H_
#define LUAENTITYLOADER_H_

extern "C"
{
	#include <lua-5.1/src/lua.h>
	#include <lua-5.1/src/lualib.h>
	#include <lua-5.1/src/lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <anax/World.hpp>
#include <iostream>
#include <Box2D/Box2D.h>
#include <B2DWorld.h>

class LuaEntityLoader{

public:

    virtual ~LuaEntityLoader(){}
	virtual void loadEntity(anax::World& anaxWorld, B2DWorld& box2dWorld,  lua_State *myLuaState) = 0;

};



#endif /* LUAENTITYLOADER_H_ */
