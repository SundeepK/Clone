#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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
	//App.setVerticalSyncEnabled(true);
    Game game(mainRenderWindow);
    game.init();

    while (mainRenderWindow.isOpen())
    {
       game.update(1.0f/60.0f);
       game.render();
       mainRenderWindow.display();
       mainRenderWindow.clear();
    }
}


