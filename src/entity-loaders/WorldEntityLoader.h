#ifndef COMPONENTLOADER_H_
#define COMPONENTLOADER_H_

#include <components/PhysicsComponent.h>
#include <anax/World.hpp>
#include "LuaEntityLoader.h"
#include <memory.h>
#include <vector>
#include <entity-loaders/PlayerEntityLoader.h>
#include <Box2D/Box2D.h>

class WorldEntityLoader {
public:

	WorldEntityLoader();
	virtual ~WorldEntityLoader();

	void loadWorldEntities(anax::World& anaxWorld, b2World& box2dWorld);

private:
	std::vector<std::unique_ptr<LuaEntityLoader>> m_entityLoaders;
};

#endif /* COMPONENTLOADER_H_ */
