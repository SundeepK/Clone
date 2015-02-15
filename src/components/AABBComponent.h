#ifndef SRC_COMPONENTS_AABBCOMPONENT_H_
#define SRC_COMPONENTS_AABBCOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>

class AABBComponent: public anax::Component<AABBComponent> {

public:
	sf::IntRect aabb;
};



#endif /* SRC_COMPONENTS_AABBCOMPONENT_H_ */
