#ifndef TEXCOORDS_H_
#define TEXCOORDS_H_

#include <Box2D/Dynamics/b2Body.h>
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>
#include <SFML/OpenGL.hpp>

class Texcoords : public anax::Component<Texcoords>{
	//TODO use a cache of sf::Image objects and reuse them, maybe map <imageLocation, sf::image>
	public:
	    std::vector<b2Vec2> textCoords;
        sf::Image image;
		GLuint texture;
};



#endif /* TEXCOORDS_H_ */
