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
#include <systems/PlayerControlsSystem.h>
#include <systems/PhysicsInterpolatorSystem.h>
#include <memory.h>

class B2DWorld
{
public:
    B2DWorld(b2World& b2world);
    virtual ~B2DWorld();
    void update(float dt, PhysicsInterpolatorSystem& physicsInterpolator,  PlayerControlsSystem& controlSystem);
    b2Body* createB2Body(B2Builder* builder);
    void setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer);
    void drawDebug();
    void step(float dt);
protected:
private:
    void assertAccumilation();

    void interpolateStates();
    void resetStates();
    void drawSquare(b2Vec2* points,b2Vec2 center,float angle);

    b2World m_world;
    float m_fixedTimestepAccumulator = 0.0f;
    float m_fixedTimestepAccumulatorRatio = 0.0f;

    const float FIXED_TIMESTEP = 1.0f / 60.0f;
    const int MAX_STEPS = 5;
    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;


    unsigned int t_accum=0,lt=0,ct=0;
    sf::Clock clock;

};

#endif // B2DWORLD_H
