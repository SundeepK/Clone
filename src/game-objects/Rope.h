#ifndef ROPE_H_
#define ROPE_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class Rope : public GameEntityCreator  {
public:
	Rope();
	~Rope();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	b2Body* createRope();

private:
	class RopeImpl;
	std::auto_ptr<RopeImpl> m_impl;
};

#endif /* ROPE_H_ */
