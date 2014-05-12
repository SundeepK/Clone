#ifndef B2BODYBUILDER_H
#define B2BODYBUILDER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include "Box2DConstants.h"
#include "B2Builder.h"
//#include <Box2D/Dynamics/b2World.h>
//#include <Box2D/Common/b2Math.h>
//#include <Box2D/Dynamics/b2Fixture.h>
//#include <Box2D/Collision/Shapes/b2PolygonShape.h>
//#include <Box2D/Collision/Shapes/b2CircleShape.h>


#include <memory.h>

class B2BodyBuilder : public B2Builder
{
public:

    B2BodyBuilder&  setPosition(b2Vec2 position);
    B2BodyBuilder&  setShape(b2Shape* shape);
    B2BodyBuilder&  bodyType(b2BodyType bodyType);
    B2BodyBuilder&  setFriction(float friction);
    B2BodyBuilder&  setRestitution(float restitution);
    B2BodyBuilder&  setDensity(float density);
    B2BodyBuilder&  setSensor(bool isSensor);
    b2Body* build(b2World& world);
private:

    b2BodyDef m_bodyDef;
    b2FixtureDef m_fixtureDef;
    std::unique_ptr<b2Shape>  m_b2Shape;


};
#endif // B2BODYBUILDER_H
