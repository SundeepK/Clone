#ifndef SRC_GAME_OBJECTS_DYNAMICROTATINGBLADE_H_
#define SRC_GAME_OBJECTS_DYNAMICROTATINGBLADE_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class DynamicRotatingBlade :  public GameEntityCreator  {
public:
	DynamicRotatingBlade();
	~DynamicRotatingBlade();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);


private:

	class DynamicRotatingBladeImpl;
	std::unique_ptr<DynamicRotatingBladeImpl> m_impl;

};

#endif /* SRC_GAME_OBJECTS_DYNAMICROTATINGBLADE_H_ */
