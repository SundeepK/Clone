#ifndef SRC_COMPONENTS_IDCOMPONENT_H_
#define SRC_COMPONENTS_IDCOMPONENT_H_

#include <anax/Component.hpp>

class IDComponent: public anax::Component<IDComponent> {

public:
	std::string uuid;
};

#endif /* SRC_COMPONENTS_IDCOMPONENT_H_ */
