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
#include <Box2D/Box2D.h>
#include <unordered_map>
#include <iostream>
#include <tmx/MapObject.h>

class LuaEntityLoader{

public:

    virtual ~LuaEntityLoader(){}
	virtual void loadEntity(anax::World& anaxWorld, b2World& box2dWorld,  std::unordered_map<std::string, tmx::MapObject>& loadedMapData,  lua_State *myLuaState) = 0;

};

#endif /* LUAENTITYLOADER_H_ */
