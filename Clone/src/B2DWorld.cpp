#include "B2DWorld.h"

B2DWorld::B2DWorld(float gravity) : m_world(b2Vec2(0.f, gravity))
{
}

B2DWorld::~B2DWorld()
{
}

b2Body* B2DWorld::createB2Body(B2BodyBuilder& builder){
    return builder.build(m_world);
}

