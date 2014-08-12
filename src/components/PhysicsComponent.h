#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include <Box2D/Dynamics/b2Body.h>

class PhysicsComponent  : anax::Component<PhysicsComponent> {

	public:
		PhysicsComponent(b2Body* inPhysicsBody) : physicsBody(inPhysicsBody){}
		~PhysicsComponent();

		b2Body* physicsBody;
};

#endif /* PHYSICSCOMPONENT_H_ */
