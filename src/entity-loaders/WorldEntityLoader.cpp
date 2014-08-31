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

    lua_State *luaState = luaL_newstate();

    luabind::open(luaState);
	luaL_openlibs(luaState);

	if(luaL_dofile(luaState, "lua-configs/playerConfig.lua")){
        printf("%s\n", lua_tostring(luaState, -1));
	}

	luabind::module(luaState)[
	luabind::class_<b2Vec2>("b2Vec2")
		.def(luabind::constructor<float32, float32>())
	];

	luabind::module(luaState)[
	luabind::class_<std::vector<b2Vec2>>("vectorOfb2Vec2")
		 .def(luabind::constructor<>())
		 .def("push_back",  static_cast<void (std::vector<b2Vec2>::*)(const b2Vec2&)>(&std::vector<b2Vec2>::push_back))
	];


	for(auto& entityLoader : m_entityLoaders) {
		entityLoader->loadEntity(anaxWorld, box2dWorld, luaState);
	}

    lua_close(luaState);
}