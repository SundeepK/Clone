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
#include <game-objects/Rope.h>

WorldEntityLoader::WorldEntityLoader()  {

	m_entityLoaders.push_back(std::unique_ptr<LuaEntityLoader>(new PlayerEntityLoader()));
	m_entityLoaders.push_back(std::unique_ptr<LuaEntityLoader>(new InterestPointsEntityLoader()));

}

WorldEntityLoader::~WorldEntityLoader() {
}

void WorldEntityLoader::loadWorldEntities(anax::World& anaxWorld, b2World& box2dWorld, std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State *luaState){

	for(auto& entityLoader : m_entityLoaders) {
		entityLoader->loadEntity(anaxWorld, box2dWorld, loadedMapData, luaState);
	}

}
