#include "WorldEntityLoader.h"
#include <vector>
#include <entity-loaders/PlayerEntityLoader.h>
#include <entity-loaders/InterestPointsEntityLoader.h>
#include <components/PhysicsComponent.h>

extern "C"
{
	#include  <lua-5.1/src/lua.h>
	#include  <lua-5.1/src/lualib.h>
	#include  <lua-5.1/src/lauxlib.h>
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

	for(auto& entityLoader : m_entityLoaders) {
		entityLoader->loadEntity(anaxWorld, box2dWorld, loadedMapData, luaState);
	}

}
