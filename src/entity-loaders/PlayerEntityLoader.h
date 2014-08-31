#ifndef PLAYERENTITYLOADER_H_
#define PLAYERENTITYLOADER_H_

#include <entity-loaders/LuaEntityLoader.h>
#include <components/PhysicsComponent.h>
#include <components/AnimationComponent.h>
#include <B2Builder.h>
#include <B2DWorld.h>
#include <B2BoxBuilder.h>

class PlayerEntityLoader : public LuaEntityLoader {
public:
	void loadEntity(anax::World& anaxWorld, B2DWorld& box2dWorld, lua_State *myLuaState);


};

#endif /* PLAYERENTITYLOADER_H_ */
