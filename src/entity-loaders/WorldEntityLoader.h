#ifndef COMPONENTLOADER_H_
#define COMPONENTLOADER_H_

#include <components/PhysicsComponent.h>
#include <anax/World.hpp>
#include "LuaEntityLoader.h"
#include <memory.h>
#include <vector>
#include <entity-loaders/PlayerEntityLoader.h>
#include <B2DWorld.h>

class WorldEntityLoader {
public:

	WorldEntityLoader();
	virtual ~WorldEntityLoader();

	void loadWorldEntities(anax::World& anaxWorld, B2DWorld& box2dWorld);

private:
	std::vector<std::unique_ptr<LuaEntityLoader>> m_entityLoaders;
};

#endif /* COMPONENTLOADER_H_ */
