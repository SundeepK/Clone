#ifndef SRC_COMPONENTS_TIMESTEPCOMPONENT_H_
#define SRC_COMPONENTS_TIMESTEPCOMPONENT_H_

#include <anax/Component.hpp>


class TimeStepComponent : public anax::Component<TimeStepComponent> {

public:

	float timeStep = 1.0f/ 60.0f;

};

#endif /* SRC_COMPONENTS_TIMESTEPCOMPONENT_H_ */
