#ifndef COMPONENTLOADER_H_
#define COMPONENTLOADER_H_

#include <components/PhysicsComponent.h>
#include <anax/World.hpp>
#include "LuaEntityLoader.h"
#include <memory.h>
#include <vector>

class WorldEntityLoader {
public:

	WorldEntityLoader();
	virtual ~WorldEntityLoader();

	void loadWorldEntities(anax::World& anaxWorld, std::vector<LuaEntityLoader*>& entityLoaders);

};

#endif /* COMPONENTLOADER_H_ */
