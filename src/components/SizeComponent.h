#ifndef SRC_COMPONENTS_SIZECOMPONENT_H_
#define SRC_COMPONENTS_SIZECOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>

class SizeComponent: public anax::Component<SizeComponent> {

public:
	sf::Vector2i size;
};




#endif /* SRC_COMPONENTS_SIZECOMPONENT_H_ */
