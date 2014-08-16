#ifndef TEXTURECOMPONENT_H_
#define TEXTURECOMPONENT_H_

#include <SFML/Graphics.hpp>

class TextureRectComponent  : public anax::Component<TextureRectComponent> {

	public:
		TextureRectComponent();
		~TextureRectComponent();

		sf::Texture texture;
	    sf::RectangleShape rect;
};



#endif /* TEXTURECOMPONENT_H_ */
