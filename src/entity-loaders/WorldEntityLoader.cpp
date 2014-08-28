#include "WorldEntityLoader.h"

extern "C"
{
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <iostream>

WorldEntityLoader::WorldEntityLoader()  {

	m_entityLoaders.push_back(std::unique_ptr<LuaEntityLoader>(new PlayerEntityLoader()));
}

WorldEntityLoader::~WorldEntityLoader() {
}

void WorldEntityLoader::loadWorldEntities(anax::World& anaxWorld, B2DWorld& box2dWorld){

    lua_State *myLuaState = luaL_newstate();

    luabind::open(myLuaState);
	luaL_openlibs(myLuaState);

	if(luaL_dofile(myLuaState, "lua-configs/playerConfig.lua")){
        printf("%s\n", lua_tostring(myLuaState, -1));
	}

	luabind::module(myLuaState)[
	luabind::class_<b2Vec2>("b2Vec2")
		.def(luabind::constructor<float32, float32>())
	];

	for(auto& entityLoader : m_entityLoaders) {
		entityLoader->loadEntity(anaxWorld, box2dWorld, myLuaState);
	}

    lua_close(myLuaState);
}
