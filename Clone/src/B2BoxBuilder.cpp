#include "B2BoxBuilder.h"

B2BoxBuilder::B2BoxBuilder(float width, float height) : m_width(width/Box2DConstants::WORLD_SCALE), m_height(height/Box2DConstants::WORLD_SCALE)
{
    m_boxShape.SetAsBox(m_width/2,(m_height/2));
}

B2BoxBuilder::B2BoxBuilder()
{
}

B2BoxBuilder::~B2BoxBuilder()
{
}
B2BoxBuilder& B2BoxBuilder::setPosition(b2Vec2 position){
    //divide by scale to convert to box2d scale
    position.x = (position.x/Box2DConstants::WORLD_SCALE)+m_width/2.0f;
    position.y = (position.y/Box2DConstants::WORLD_SCALE)+m_height/2.0f;
    m_builder.setPosition(position);
    return *this;
}

B2BoxBuilder&  B2BoxBuilder::bodyType(b2BodyType bodyType){
    m_builder.bodyType(bodyType);
    return *this;
}

B2BoxBuilder&  B2BoxBuilder::setFriction(float friction){
    m_builder.setFriction(friction);
    return *this;
}


B2BoxBuilder&  B2BoxBuilder::setRestitution(float restitution){
    m_builder.setRestitution(restitution);
    return *this;
}

B2BoxBuilder&  B2BoxBuilder::setDensity(float density){
    m_builder.setDensity(density);
    return *this;
}

B2BoxBuilder&  B2BoxBuilder::setSensor(bool isSensor){
    m_builder.setSensor(isSensor);
    return *this;
}

b2Body* B2BoxBuilder::build(b2World& world){
    m_builder.setShape(&m_boxShape);
    return m_builder.build(world);
}
