#ifndef PLAYERENTITYLOADER_H_
#define PLAYERENTITYLOADER_H_

#include <entity-loaders/LuaEntityLoader.h>
#include <components/PhysicsComponent.h>
#include <components/AnimationComponent.h>
#include <components/PlayerTagComponent.h>
#include <Thor/Animation.hpp>
#include <B2Builder.h>
#include <PhysicsTimeStepSystem.h>
#include <B2BoxBuilder.h>

class PlayerEntityLoader : public LuaEntityLoader {
public:

	void loadEntity(anax::World& anaxWorld, b2World& box2dWorld, lua_State *myLuaState);

};

#endif /* PLAYERENTITYLOADER_H_ */
