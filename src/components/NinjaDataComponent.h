#ifndef SRC_COMPONENTS_NINJADATACOMPONENT_H_
#define SRC_COMPONENTS_NINJADATACOMPONENT_H_

#include <anax/Component.hpp>
#include <Box2D/Box2D.h>
#include <SFML/System.hpp>

class NinjaDataComponent  : public anax::Component<NinjaDataComponent> {

public:

	bool isNinjaSenseApplied = false;
	sf::Time lastTimeNinjaSenseApplied;

};



#endif /* SRC_COMPONENTS_NINJADATACOMPONENT_H_ */
