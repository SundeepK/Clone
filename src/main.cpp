#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>


#include "B2DWorld.h"
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
	b2World b2world(b2Vec2(0, 9.8f));

	 tmx::MapLoader m_mapLoader("maps/");
     m_mapLoader.Load("test-b2d.tmx");
//			for (const auto& l : m_mapLoader.GetLayers()) {
//				if (l.name == "Static") {
//					for (const auto& object : l.objects) {
//						b2Body* bo = tmx::BodyCreator::Add(object, b2world, b2_staticBody);
//					}
//				}
//
//			}

    Game game(mainRenderWindow, b2world,  m_mapLoader);
    game.loadMap(m_mapLoader);
    game.init();




    sf::Clock clock;
    while (mainRenderWindow.isOpen())
    {
       game.update(clock.restart().asMilliseconds());
       game.render();
       mainRenderWindow.display();
      // mainRenderWindow.clear();
    }
}


