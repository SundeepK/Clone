#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include "B2BoxBuilder.h"
#include <functional>
#include <iostream>
#include "ActionController.h"
#include <string>
#include <anax/World.hpp>
#include <Game.h>

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow mainRenderWindow(sf::VideoMode(1280,800,32), "Clone",sf::Style::Default, settings);
	mainRenderWindow.setKeyRepeatEnabled(true);
	mainRenderWindow.setFramerateLimit(60);
	//mainRenderWindow.setVerticalSyncEnabled(true);

	b2World b2world(b2Vec2(0, 18.0f));
	//	b2world.SetAutoClearForces(false);
	b2world.SetAllowSleeping(true);
	b2world.SetContinuousPhysics(false);

	SFMLB2dDebugDraw m_debugDrawer(mainRenderWindow);
    b2world.SetDebugDraw(&m_debugDrawer);
	m_debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);

    Game game(b2world, mainRenderWindow);
    game.init();

    sf::Clock clock;
    while (mainRenderWindow.isOpen())
    {
       float dt = clock.restart().asMilliseconds();
       game.update(dt);
       game.render();
       mainRenderWindow.display();
    }
}


