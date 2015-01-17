#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include <Box2D/Dynamics/b2Body.h>
#include <anax/Component.hpp>

class PhysicsComponent  : public anax::Component<PhysicsComponent> {

	public:

		b2Body* physicsBody;
		float previousAngle;
		float smoothedAngle;
		b2Vec2 previousPosition;
		b2Vec2 smoothedPosition;
		bool isDead = false;
};

#endif /* PHYSICSCOMPONENT_H_ */
