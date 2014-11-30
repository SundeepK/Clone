#ifndef ROPE_H_
#define ROPE_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>

class Rope {
public:
	Rope();
	~Rope();

	void createRope(b2World& box2dWorld,  anax::World& anaxWorld);

private:
	class RopeImpl;
	std::auto_ptr<RopeImpl> m_impl;
};

#endif /* ROPE_H_ */
