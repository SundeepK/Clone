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
#include <memory>

class PhysicsTimeStepSystem
{
public:
    PhysicsTimeStepSystem(b2World& b2world);
    ~PhysicsTimeStepSystem();
    //check git history for move contructor if needed again

    void update(sf::RenderWindow& window, float dt, PhysicsInterpolatorSystem& physicsInterpolator,  PlayerControlsSystem& controlSystem);
    void setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer);
    void drawDebug();
    void step(float dt);

private:

    class PhysicsTimeStepSystemImpl;
    std::unique_ptr<PhysicsTimeStepSystemImpl> m_impl;

};

#endif // B2DWORLD_H
