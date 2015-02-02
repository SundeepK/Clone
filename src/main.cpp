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
#include <SFGUI/SFGUI.hpp>
#include <game-editor/TilePanel.h>


//int main()
//{
//    sf::ContextSettings settings;
////    settings.depthBits = 24;
////    settings.stencilBits = 8;
////    settings.antialiasingLevel = 4;
////    settings.majorVersion = 3;
////    settings.minorVersion = 0;
//    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
//    sf::RenderWindow mainRenderWindow(sf::VideoMode(desktop.width,desktop.height,32), "Clone",sf::Style::Default, settings);
//	mainRenderWindow.setKeyRepeatEnabled(true);
//	mainRenderWindow.setFramerateLimit(60);
//	//mainRenderWindow.setVerticalSyncEnabled(true);
//
//	b2World b2world(b2Vec2(0, 18.0f));
//	//	b2world.SetAutoClearForces(false);
//	b2world.SetAllowSleeping(true);
//	b2world.SetContinuousPhysics(false);
//
//	SFMLB2dDebugDraw m_debugDrawer(mainRenderWindow);
//    b2world.SetDebugDraw(&m_debugDrawer);
//	m_debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit );
//
//    Game game(b2world, mainRenderWindow);
//    game.init();
//
//    mainRenderWindow.setActive(true);
//
//    sf::Clock clock;
//    while (mainRenderWindow.isOpen())
//    {
//       float dt = clock.restart().asMilliseconds();
//       game.update(dt);
//       game.render();
//    }
//}

int main()
{


	sf::ContextSettings settings;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow mainRenderWindow(sf::VideoMode(desktop.width,desktop.height,32), "Clone",sf::Style::Default, settings);
	mainRenderWindow.setKeyRepeatEnabled(true);
	mainRenderWindow.setFramerateLimit(60);

    mainRenderWindow.setActive(true);

	sfg::SFGUI sfgui;
	sfg::Desktop sfguiDesktop;
	auto textureCanvas = sfg::Canvas::Create();

	auto sfmlWindow = sfg::Window::Create(sfg::Window::TITLEBAR |  sfg::Window::RESIZE);
	sfmlWindow->SetPosition(sf::Vector2f(50,50));
	unsigned int spaceReservedForControls = desktop.width / 5;
	textureCanvas->SetRequisition(sf::Vector2f((spaceReservedForControls), 200.0f));
    sfmlWindow->Add(textureCanvas);
    sfguiDesktop.Add(sfmlWindow);
	mainRenderWindow.resetGLStates();

	TilePanel tilePanel("maps/diffuse.png");

	sf::Clock clock;
	while (mainRenderWindow.isOpen()) {
		sf::Event event;
		float dt = clock.restart().asMilliseconds();

		while (mainRenderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mainRenderWindow.close();
			}
			sfguiDesktop.HandleEvent(event);
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2f absolutePosition = textureCanvas->GetAbsolutePosition();
			sf::Vector2f absolutePositionwindow = sfmlWindow->GetAbsolutePosition();

			std::cout << "canvas x: " << absolutePosition.x << " y:" << absolutePosition.y << std::endl;
			std::cout << "mouse x: " << sf::Mouse::getPosition().x << " y:" << sf::Mouse::getPosition().y << std::endl;
			sf::Vector2i position = sf::Mouse::getPosition();
			position.y -= 24;
			sf::Vector2i mousePos = position - sf::Vector2i(absolutePosition.x, absolutePosition.y);
			if(tilePanel.update(mousePos)){
				textureCanvas->Invalidate();
				textureCanvas->RequestResize();
				sfmlWindow->Invalidate();
				sfmlWindow->RequestResize();
			}
		}


		sfguiDesktop.Update(1.0f / 60.0f);

		mainRenderWindow.clear();

		textureCanvas->Bind();
		textureCanvas->Clear(sf::Color(50, 50, 50));
		textureCanvas->Draw(tilePanel);
		textureCanvas->Display();
		textureCanvas->Unbind();

		mainRenderWindow.setActive(true);
		sfgui.Display(mainRenderWindow);
		mainRenderWindow.display();
	}
}


