#include "B2BodyBuilder.h"


B2BodyBuilder&  B2BodyBuilder::setShape(b2Shape* shape){
    m_b2Shape.reset(shape);
}


B2BodyBuilder& B2BodyBuilder::setPosition(b2Vec2 position){
    //divide by scale to convert to box2d scale
    m_bodyDef.position.Set( position.x, position.y );
    return *this;
}

B2BodyBuilder&  B2BodyBuilder::bodyType(b2BodyType bodyType){
    m_bodyDef.type = bodyType;
    return *this;
}

B2BodyBuilder&  B2BodyBuilder::setFriction(float friction){
    m_fixtureDef.friction = friction;
    return *this;
}


B2BodyBuilder&  B2BodyBuilder::setRestitution(float restitution){
    m_fixtureDef.restitution = restitution;
    return *this;
}

B2BodyBuilder&  B2BodyBuilder::setDensity(float density){
    m_fixtureDef.density =density;
    return *this;
}

B2BodyBuilder&  B2BodyBuilder::setSensor(bool isSensor){
    m_fixtureDef.isSensor = isSensor;
    return *this;
}

b2Body* B2BodyBuilder::build(b2World& world){
    m_fixtureDef.shape = (m_b2Shape.get());
    b2Body* body = world.CreateBody(&m_bodyDef);
    body->CreateFixture(&m_fixtureDef);
    return body;
}


