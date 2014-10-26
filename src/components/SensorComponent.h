#ifndef SENSORCOMPONENT_H_
#define SENSORCOMPONENT_H_

#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

class SensorComponent  : public anax::Component<SensorComponent> {

	public:
		std::string tag;
		b2Fixture* sensors;
		int currentTotalContacts = 0;

};




#endif /* SENSORCOMPONENT_H_ */
