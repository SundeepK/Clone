#ifndef SRC_GAME_OBJECTS_SPLITTABLEOBJECT_H_
#define SRC_GAME_OBJECTS_SPLITTABLEOBJECT_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class SplittableObject :  public GameEntityCreator {
public:
	SplittableObject();
	~SplittableObject();

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	GameObjectProperty getProperties();

private:

	class SplittableObjectImpl;
	std::unique_ptr<SplittableObjectImpl> m_impl;

};

#endif /* SRC_GAME_OBJECTS_SPLITTABLEOBJECT_H_ */
