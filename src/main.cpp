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
    sf::RenderWindow mainRenderWindow(sf::VideoMode(desktop.width,desktop.height,32), "Clone", sf::Style::Default , settings);
	mainRenderWindow.setKeyRepeatEnabled(true);
	mainRenderWindow.setFramerateLimit(60);

    mainRenderWindow.setActive(true);
	unsigned int spaceReservedForControls = desktop.width / 5;
    sf::Vector2f mapSizeInPixels(desktop.width - spaceReservedForControls, desktop.height - 100);

	sf::Image image;
	image.loadFromFile("maps/diffuse.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	TilePanel tilePanel(texture, 32, 32);

	sfg::SFGUI sfgui;
	sfg::Desktop sfguiDesktop;

	auto textureCanvas = sfg::Canvas::Create();
	auto mapCanvas = sfg::Canvas::Create();

    //box2d stuff
    b2World b2world(b2Vec2(0, 18.0f));
	//	b2world.SetAutoClearForces(false);
	b2world.SetAllowSleeping(true);
	b2world.SetContinuousPhysics(false);

	SFGUIDebugDraw debugDrawer(mapCanvas);
	b2world.SetDebugDraw(&debugDrawer);
	debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);

	anax::World anaxWorld;

	ObjectCreatorController objectController(anaxWorld, b2world);


	auto mapWindow = sfg::Window::Create(sfg::Window::RESIZE);
	auto objectCreatorWindow = sfg::Window::Create(sfg::Window::RESIZE);

	auto scrollbarY = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );
	auto scrollbarX = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::HORIZONTAL );

	mapWindow->SetRequisition(mapSizeInPixels);
	mapWindow->SetPosition(sf::Vector2f(0,0));
	mapCanvas->SetRequisition(mapSizeInPixels);

	textureCanvas->SetRequisition(sf::Vector2f((spaceReservedForControls), image.getSize().y));
	auto table = sfg::Table::Create();

	auto rightPanel =  sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
	rightPanel->SetSpacing(10);

	table->Attach( mapCanvas, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
	table->Attach( scrollbarY, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), 0, sfg::Table::FILL);
	table->Attach( scrollbarX, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL, 0  );
	table->Attach( rightPanel, sf::Rect<sf::Uint32>(  2, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL );

	LayerController layerController(anaxWorld, b2world);
	layerController.attachTo(rightPanel);
	objectController.addEntityCreator("boulder", std::unique_ptr<GameEntityCreator>(new Boulder()));
	objectController.addEntityCreator("rope", std::unique_ptr<GameEntityCreator>(new Rope()));
	objectController.attachTo(rightPanel);
	rightPanel->Pack(textureCanvas, true, false);

	MapData mapData(sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels));
	ScrollableCanvas scrollableCanvas(mapCanvas, scrollbarX, scrollbarY, mapData);

	MapPanelController mapPanelController(scrollableCanvas,	std::unique_ptr<MapPanel>(new MapPanel (texture, sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels))));

	layerController.addLayer("Entities", LayerType::OBJECTS);

    mapWindow->Add(table);

    sfguiDesktop.Add(mapWindow);
	mainRenderWindow.resetGLStates();


	DrawStaticAABBSystem gameObjectAABBDrawSystem;
	anaxWorld.addSystem(gameObjectAABBDrawSystem);

	sf::Clock clock;
	sf::IntRect objectBounds;
	sf::RectangleShape objectBoundsRect;
	objectBoundsRect.setFillColor(sf::Color::Transparent);
	objectBoundsRect.setOutlineThickness(2.0f);
	objectBoundsRect.setOutlineColor(sf::Color::Red);
	while (mainRenderWindow.isOpen()) {
		sf::Event event;
		float dt = clock.restart().asMilliseconds();
		auto currentLayerOptional = layerController.getCurrentlySelectedLayer();
		std::vector<sf::Event> events;
		auto remnderWindowMousePos = sf::Mouse::getPosition(mainRenderWindow);
		auto canvasMousePosition = scrollableCanvas.getCanvasMousePositionFrom(remnderWindowMousePos);
		bool isInBoundsAndSliderNotInUse = scrollableCanvas.isInBoundsAndSlidersNotInUse(remnderWindowMousePos);

		while (mainRenderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mainRenderWindow.close();
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f absolutePosition = textureCanvas->GetAbsolutePosition();

					sf::Vector2i position(event.mouseButton.x, event.mouseButton.y);
					sf::Vector2i mousePos = position - sf::Vector2i(absolutePosition.x, absolutePosition.y);
					tilePanel.selectTileAt(mousePos);

					if (currentLayerOptional) {
						Layer currentLayer = currentLayerOptional.get();
						if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse) {
								objectBounds.top = canvasMousePosition.y;
								objectBounds.left = canvasMousePosition.x;
						}
					}
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (currentLayerOptional) {
						Layer currentLayer = currentLayerOptional.get();
						if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse) {
							objectBounds.height = canvasMousePosition.y - objectBounds.top;
							objectBounds.width = canvasMousePosition.x - objectBounds.left;

							auto mapObject = objectController.createGameObjectAt(objectBounds);
							layerController.addMapObjectToCurrentLayer(mapObject);
						}
					}
				}
			}
			sfguiDesktop.HandleEvent(event);
			events.push_back(event);
		}

		if (currentLayerOptional) {
				Layer currentLayer = currentLayerOptional.get();
				if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						objectBounds.height = canvasMousePosition.y - objectBounds.top;
						objectBounds.width = canvasMousePosition.x - objectBounds.left;
				}
		}

		scrollableCanvas.updateCanvas(events);
		layerController.update(canvasMousePosition, events);

		//should always have a selected layer, but just in case
		if(currentLayerOptional){
			Layer currentLayer = currentLayerOptional.get();
			if(currentLayer.getLayerType() == LayerType::TILE){
				mapPanelController.addTile(remnderWindowMousePos, tilePanel.getCurrentlySelectedTile());
			}
		}else{
			std::cerr << "No currently selected layer found" << std::endl;
		}


		sfguiDesktop.Update(1.0f / 60.0f);

		mainRenderWindow.clear();

		b2world.Step(1.f/60.f, 8, 3);
		anaxWorld.refresh();
		gameObjectAABBDrawSystem.updateAABBs();

		textureCanvas->Bind();
		textureCanvas->Clear(sf::Color(50, 50, 50));
		textureCanvas->Draw(tilePanel);
		textureCanvas->Display();
		textureCanvas->Unbind();

		mapCanvas->Bind();
		mapCanvas->Clear(sf::Color(50, 50, 50));
		b2world.DrawDebugData();
		mapCanvas->Draw(scrollableCanvas);
		mapCanvas->Draw(mapPanelController);
		objectBoundsRect.setPosition(sf::Vector2f(objectBounds.left, objectBounds.top));
		objectBoundsRect.setSize(sf::Vector2f(objectBounds.width, objectBounds.height));
		mapCanvas->Draw(objectBoundsRect);
		mapCanvas->Draw(gameObjectAABBDrawSystem);
		mapCanvas->Display();
		mapCanvas->Unbind();

		mainRenderWindow.setActive(true);
		sfgui.Display(mainRenderWindow);
		mainRenderWindow.display();
	}
}

int main() {
	MainGame game;
	game.run();

	return EXIT_SUCCESS;
}
