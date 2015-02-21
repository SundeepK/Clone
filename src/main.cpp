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
#include <SFGUI/Widgets.hpp>
#include <game-editor/TilePanel.h>
#include <game-editor/MapPanel.h>
#include <game-editor/ObjectCreatorController.h>
#include <game-objects/GameEntityCreator.h>
#include <game-objects/Boulder.h>
#include <SFGUIDebugDraw.h>
#include <game-editor/MapPanelController.h>
#include <game-editor/LayerController.h>
#include <game-objects/Rope.h>
#include <game-editor/ScrollableCanvas.h>
#include <systems/DrawStaticAABBSystem.h>
#include <game-editor/GameEditor.h>

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

class MainGame {
	public:
		void run();
};

void MainGame::run()
{


	sf::ContextSettings settings;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow mainRenderWindow(sf::VideoMode(desktop.width,desktop.height,32), "Clone", sf::Style::Default, settings);
	mainRenderWindow.setKeyRepeatEnabled(true);
	mainRenderWindow.setFramerateLimit(60);

    mainRenderWindow.setActive(true);
	unsigned int spaceReservedForControls = desktop.width / 5;
    sf::Vector2f mapSizeInPixels(desktop.width - spaceReservedForControls, desktop.height - 100);


	sf::Image m_image;
	sf::Texture m_texture;

	m_image.loadFromFile("maps/diffuse.png");
	m_texture.loadFromImage(m_image);

	sf::Vector2i tileSize(32, 32);

	GameEditor gameEditor(mainRenderWindow, mapSizeInPixels, m_texture, tileSize);
    mainRenderWindow.resetGLStates();

	while (mainRenderWindow.isOpen()) {
		gameEditor.update();
	}
}

int main() {
	MainGame game;
	game.run();

	return EXIT_SUCCESS;
}
