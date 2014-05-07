#ifndef B2DWORLD_H
#define B2DWORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include "B2BodyBuilder.h"

class B2DWorld
{
    public:
        B2DWorld();
        virtual ~B2DWorld();
        b2Body* createB2Body(B2BodyBuilder builder);
    protected:
    private:
};

#endif // B2DWORLD_H
