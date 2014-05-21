#ifndef B2DWORLD_H
#define B2DWORLD_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include "B2Builder.h"
#include "Updateable.h"
#include <math.h>
#include "SFMLB2dDebugDraw.h"
#include "ActionController.h"
#include "Action.h"
#include <functional>
#include <iostream>

class B2DWorld : Updateable
{
public:
    B2DWorld(float gravity);
    virtual ~B2DWorld();
    void update(float dt);
    b2Body* createB2Body(B2Builder* builder);
    void setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer);
protected:
private:
    void assertAccumilation();
    void step(float dt);
    void interpolateStates();
    void resetStates();

    b2World m_world;
    float m_fixedTimestepAccumulator = 0;
    float m_fixedTimestepAccumulatorRatio = 0;

    const float FIXED_TIMESTEP = 1.f / 60.f;
    const int MAX_STEPS = 5;
    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;

};

#endif // B2DWORLD_H
