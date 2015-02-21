#ifndef PLAYERENTITYLOADER_H_
#define PLAYERENTITYLOADER_H_

#include <entity-loaders/LuaEntityLoader.h>
#include <components/PhysicsComponent.h>
#include <components/AnimationComponent.h>
#include <components/PlayerTagComponent.h>
#include <components/PlayerStateComponent.h>
#include <components/Texcoords.h>
#include <components/Sensors.h>
#include <Thor/Animations.hpp>
#include <B2Builder.h>
#include <PhysicsTimeStepSystem.h>
#include <B2BoxBuilder.h>
#include <components/SensorComponent.h>
#include <lua-exports/B2WorldProxy.h>

class PlayerEntityLoader  {
public:

	void loadEntity(anax::World& anaxWorld, b2World& box2dWorld,  tmx::MapObject& loadedMapData, lua_State *myLuaState);

};

#endif /* PLAYERENTITYLOADER_H_ */
