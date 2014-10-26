#ifndef SENSORS_H_
#define SENSORS_H_


#include <Box2D/Box2D.h>
#include <anax/Component.hpp>
#include <map>
#include <components/SensorComponent.h>

class Sensor  : public anax::Component<Sensor> {

	public:
		std::map<std::string, SensorComponent> sensors;

};


#endif /* SENSORS_H_ */
