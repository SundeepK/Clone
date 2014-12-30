#ifndef SRC_COMPONENTS_BREAKABLEJOINTCOMPONENT_H_
#define SRC_COMPONENTS_BREAKABLEJOINTCOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class BreakableJointComponent  : public anax::Component<BreakableJointComponent> {

public:
	// this is the first body registered in a series of connected bodies with joints
	b2Body* firstBodyWithJoint;
	bool isBreakable = false;
	float maxWeight;

};


#endif /* SRC_COMPONENTS_BREAKABLEJOINTCOMPONENT_H_ */
