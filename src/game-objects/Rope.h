#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

#ifndef SRC_GAME_OBJECTS_ROPE_H_
#define SRC_GAME_OBJECTS_ROPE_H_

class Rope : public GameEntityCreator  {
public:
	Rope();
	~Rope();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	GameObjectProperty getProperties();
	b2Body* createRope();

private:
	class RopeImpl;
	std::auto_ptr<RopeImpl> m_impl;
};



#endif /* SRC_GAME_OBJECTS_ROPE_H_ */
