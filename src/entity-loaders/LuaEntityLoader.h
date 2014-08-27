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

class LuaEntityLoader{

public:

    virtual ~LuaEntityLoader(){}
	virtual void loadEntity(anax::World& anaxWorld, lua_State *myLuaState) = 0;

};



#endif /* LUAENTITYLOADER_H_ */
