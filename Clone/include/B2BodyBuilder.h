#ifndef B2BODYBUILDER_H
#define B2BODYBUILDER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <memory.h>

class B2BodyBuilder
{
     public:
         B2BodyBuilder(b2Shape* shape);
         virtual ~B2BodyBuilder();
         B2BodyBuilder setPosition(b2Vec2 position);
         B2BodyBuilder bodyType(float x, float y);
         B2BodyBuilder bodyDef(b2BodyDef bodyDef);
         B2BodyBuilder setFriction(float friction);
         B2BodyBuilder setRestitution(float restitution);
         B2BodyBuilder setDensity(float density);
         B2BodyBuilder setSensor(bool isSensor);
         b2Body* build(b2World world);
    private:
         b2FixtureDef m_fixtureDef;
         std::unique_ptr<b2Shape>  m_b2Shape;


};
#endif // B2BODYBUILDER_H
