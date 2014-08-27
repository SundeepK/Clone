#ifndef PLAYERENTITYLOADER_H_
#define PLAYERENTITYLOADER_H_

#include "LuaEntityLoader.h"
#include <components/PhysicsComponent.h>

class PlayerEntityLoader : public LuaEntityLoader {
public:
	void loadEntity(anax::World& anaxWorld, lua_State *myLuaState);
};

#endif /* PLAYERENTITYLOADER_H_ */
