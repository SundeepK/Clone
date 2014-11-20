#include "WorldEntityLoader.h"
#include <vector>
#include <entity-loaders/PlayerEntityLoader.h>
#include <entity-loaders/InterestPointsEntityLoader.h>
#include <components/PhysicsComponent.h>

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
	m_entityLoaders.push_back(std::unique_ptr<LuaEntityLoader>(new InterestPointsEntityLoader()));

}

WorldEntityLoader::~WorldEntityLoader() {
}

void WorldEntityLoader::loadWorldEntities(anax::World& anaxWorld, b2World& box2dWorld, std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State *luaState){

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
		entityLoader->loadEntity(anaxWorld, box2dWorld, loadedMapData, luaState);
	}

}
