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
#include <game-editor/MapPanel.h>

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
	auto mapCanvas = sfg::Canvas::Create();

	auto sfmlWindow = sfg::Window::Create(sfg::Window::TITLEBAR |  sfg::Window::RESIZE);
	auto mapWindow = sfg::Window::Create(sfg::Window::TITLEBAR |  sfg::Window::RESIZE);

	sfmlWindow->SetPosition(sf::Vector2f(50,50));
	mapWindow->SetPosition(sf::Vector2f(100,90));

	unsigned int spaceReservedForControls = desktop.width / 5;
	textureCanvas->SetRequisition(sf::Vector2f((spaceReservedForControls), 200.0f));
	mapCanvas->SetRequisition(sf::Vector2f(800.0f, 200.0f));
    sfmlWindow->Add(textureCanvas);
    mapWindow->Add(mapCanvas);

    sfguiDesktop.Add(sfmlWindow);
    sfguiDesktop.Add(mapWindow);
	mainRenderWindow.resetGLStates();

	sf::Image image;
	image.loadFromFile("maps/diffuse.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	TilePanel tilePanel(texture, 32, 32);
	MapPanel mapPanel(texture, sf::Vector2f(50, 10), 32, 32);

	sf::Clock clock;
	while (mainRenderWindow.isOpen()) {
		sf::Event event;
		float dt = clock.restart().asMilliseconds();

		while (mainRenderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mainRenderWindow.close();
			}else if (event.type == sf::Event::MouseButtonPressed) {
		        if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f absolutePosition = textureCanvas->GetAbsolutePosition();

					std::cout << "canvas x: " << absolutePosition.x << " y:" << absolutePosition.y << std::endl;
					std::cout << "mouse x: " << sf::Mouse::getPosition().x << " y:" << sf::Mouse::getPosition().y << std::endl;
		        	sf::Vector2i position(event.mouseButton.x, event.mouseButton.y );
					sf::Vector2i mousePos = position - sf::Vector2i(absolutePosition.x, absolutePosition.y);
					auto tilesSelected = tilePanel.update(mousePos);

					sf::Vector2i pos(event.mouseButton.x, event.mouseButton.y);
					if(tilesSelected.size() <= 0){
						sf::Vector2f absolutePositionForMapCanvas = mapCanvas->GetAbsolutePosition();
						mapPanel.addTile(pos - sf::Vector2i(absolutePositionForMapCanvas.x, absolutePositionForMapCanvas.y), tilePanel.getCurrentlySelectedTile());
					}

		        }
		    }

			sfguiDesktop.HandleEvent(event);
		}

		sfguiDesktop.Update(1.0f / 60.0f);

		mainRenderWindow.clear();

		textureCanvas->Bind();
		textureCanvas->Clear(sf::Color(50, 50, 50));
		textureCanvas->Draw(tilePanel);
		textureCanvas->Display();
		textureCanvas->Unbind();


		mapCanvas->Bind();
		mapCanvas->Clear(sf::Color(50, 50, 50));
		mapCanvas->Draw(mapPanel);
		mapCanvas->Display();
		mapCanvas->Unbind();

		mainRenderWindow.setActive(true);
		sfgui.Display(mainRenderWindow);
		mainRenderWindow.display();
	}
}


