#ifndef TEXCOORDS_H_
#define TEXCOORDS_H_

#include <Box2D/Dynamics/b2Body.h>
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>
#include <SFML/OpenGL.hpp>

class Texcoords : public anax::Component<Texcoords>{
	public:
	    std::vector<b2Vec2> textCoords;
        sf::Image image;
		GLuint texture = 0;
};



#endif /* TEXCOORDS_H_ */
