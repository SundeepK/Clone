#ifndef TEXCOORDS_H_
#define TEXCOORDS_H_

#include <Box2D/Dynamics/b2Body.h>
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>

class Texcoords : public anax::Component<Texcoords>{
	public:
	    std::vector<b2Vec2> textCoords;
        sf::Image image;
};



#endif /* TEXCOORDS_H_ */
