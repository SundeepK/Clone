#ifndef SRC_COMPONENTS_BLADE_H_
#define SRC_COMPONENTS_BLADE_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>

class BladeComponent : public anax::Component<BladeComponent>{

public:

	b2Vec2 bladeLinearVelocity;
	b2Vec2 maxLinearVelocity = b2Vec2(20.0f, 20.0f);

};




#endif /* SRC_COMPONENTS_BLADE_H_ */
