#ifndef TEXTURECOMPONENT_H_
#define TEXTURECOMPONENT_H_

#include <SFML/Graphics.hpp>
#include <anax/Component.hpp>

class TextureRectComponent  : public anax::Component<TextureRectComponent> {

	public:

		sf::Texture texture;
	    sf::RectangleShape rect;
};

#endif /* TEXTURECOMPONENT_H_ */
