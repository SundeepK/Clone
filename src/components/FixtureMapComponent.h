#ifndef FIXTUREMAPCOMPONENT_H_
#define FIXTUREMAPCOMPONENT_H_

#include <Box2D/Dynamics/b2Body.h>
#include <anax/Component.hpp>
#include <unordered_map>

class FixtureMapComponent  : public anax::Component<FixtureMapComponent> {

	public:
		std::unordered_map<std::string, b2Fixture*> fixtureMap;
};



#endif /* FIXTUREMAPCOMPONENT_H_ */
