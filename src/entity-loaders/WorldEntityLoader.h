#ifndef COMPONENTLOADER_H_
#define COMPONENTLOADER_H_

#include <anax/World.hpp>
#include "LuaEntityLoader.h"
#include <unordered_map>
#include <memory.h>
#include <Box2D/Box2D.h>
#include <tmx/MapObject.h>

class WorldEntityLoader {
public:

	WorldEntityLoader();
	virtual ~WorldEntityLoader();

	void loadWorldEntities(anax::World& anaxWorld, b2World& box2dWorld, std::unordered_map<std::string, tmx::MapObject>& loadedMapData);

private:
	std::vector<std::unique_ptr<LuaEntityLoader>> m_entityLoaders;
};
#endif /* COMPONENTLOADER_H_ */
