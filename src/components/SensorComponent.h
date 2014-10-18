#ifndef SENSORCOMPONENT_H_
#define SENSORCOMPONENT_H_

#include <Box2D/Box2D.h>
#include <anax/Component.hpp>
#include <vector>

class SensorComponent  : public anax::Component<SensorComponent> {

	public:
		b2Fixture* sensors;
		int currentTotalContacts;

};




#endif /* SENSORCOMPONENT_H_ */
