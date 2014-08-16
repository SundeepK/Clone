#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include <Box2D/Dynamics/b2Body.h>

class PhysicsComponent  : public anax::Component<PhysicsComponent> {

	public:
		PhysicsComponent();
		~PhysicsComponent();

		b2Body* physicsBody;
};

#endif /* PHYSICSCOMPONENT_H_ */
