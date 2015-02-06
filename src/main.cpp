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
#include <SFGUI/Widgets.hpp>

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
		void sliderPressed();
		void sliderReleased();
		void sliderAdjusted();

		void run();

	private:

		// Create our adjustment smart pointer.
		sfg::Adjustment::Ptr m_yAdjustment;
		sfg::Adjustment::Ptr m_xAdjustment;

		bool isUsingSlider = false;
		bool shouldScrollMap = false;
		sf::Vector2i m_viewDeltaFromSlider;
		sf::Vector2i m_prevSliderValue;
		sf::Vector2f m_center;
};



void MainGame::sliderPressed() {
	std::cout << "pressed" <<std::endl;

	isUsingSlider = true;
}

void MainGame::sliderReleased() {
	std::cout << "released" <<std::endl;

	isUsingSlider = false;
}

void MainGame::sliderAdjusted() {

	shouldScrollMap = true;
	m_viewDeltaFromSlider = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue()) - m_prevSliderValue;
	std::cout << "m_viewDeltaFromSlider x:" << m_viewDeltaFromSlider.x << " y:" <<m_viewDeltaFromSlider.y << std::endl;

	m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());
}


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
	MapPanel mapPanel(texture, sf::Vector2i(70, 70), 32, 32, sf::Vector2i(mapSizeInPixels));



	sfg::SFGUI sfgui;
	sfg::Desktop sfguiDesktop;
	auto textureCanvas = sfg::Canvas::Create();
	auto mapCanvas = sfg::Canvas::Create();

	auto sfmlWindow = sfg::Window::Create(sfg::Window::TITLEBAR |  sfg::Window::RESIZE);
	auto mapWindow = sfg::Window::Create(sfg::Window::RESIZE);

	auto boxScrollY = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );
	auto boxScrollX = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

	auto scrollbarY = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );
	auto scrollbarX = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::HORIZONTAL );

	scrollbarY->SetRequisition( sf::Vector2f( 0.f, 80.f ) );
	m_yAdjustment = scrollbarY->GetAdjustment();
//	scrollbarY->GetSignal( sfg::Scrollbar::OnMouseLeftRelease).Connect( std::bind( &MainGame::sliderReleased, this ) );
//	m_yAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &MainGame::sliderAdjusted, this ) );


//	m_yAdjustment->SetLower( 0.0f );
//	m_yAdjustment->SetUpper( (70 * 32) - desktop.width );
//	m_yAdjustment->SetMinorStep( 10.f );
//	m_yAdjustment->SetMajorStep( 20.f );

	scrollbarX->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
	m_xAdjustment = scrollbarX->GetAdjustment();
//	scrollbarX->GetSignal( sfg::Scrollbar::OnMouseLeftRelease).Connect( std::bind( &MainGame::sliderReleased, this ) );
//	m_xAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &MainGame::sliderAdjusted, this ) );


//	m_xAdjustment->SetLower( 0 );
//	m_xAdjustment->SetUpper( (70 * 32) - desktop.width );
//	m_xAdjustment->SetMinorStep( 10.f );
//	m_xAdjustment->SetMajorStep( 20.f );

	sfmlWindow->SetPosition(sf::Vector2f(desktop.width - spaceReservedForControls + 10,100.0f));
	mapWindow->SetPosition(sf::Vector2f(0,0));
	mapCanvas->SetRequisition(mapSizeInPixels);

	auto table = sfg::Table::Create();

	table->Attach( mapCanvas, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
	table->Attach( scrollbarY, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), 0, sfg::Table::FILL);
	table->Attach( scrollbarX, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL, 0  );
	table->Attach( textureCanvas, sf::Rect<sf::Uint32>( 2, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );

//
//	m_xAdjustment->SetLower( mapSizeInPixels.x / 2 );
//	m_xAdjustment->SetUpper( (70 * 32) - (mapSizeInPixels.x /2 ) );
//	m_xAdjustment->SetMinorStep( 10.f );
//	m_xAdjustment->SetMajorStep( mapSizeInPixels.x );
//	m_xAdjustment->SetPageSize( mapSizeInPixels.x );
//
//	m_yAdjustment->SetLower( mapSizeInPixels.y );
//	m_yAdjustment->SetUpper( (70 * 32) - (mapSizeInPixels.y / 2) );
//	m_yAdjustment->SetMinorStep( 10.f );
//	m_yAdjustment->SetMajorStep( mapSizeInPixels.y );
//	m_yAdjustment->SetPageSize( mapSizeInPixels.y );

	m_xAdjustment->SetLower(0 );
	m_xAdjustment->SetUpper( (70 * 32) - (mapSizeInPixels.x /2 ) );
	m_xAdjustment->SetMinorStep( 10.f );
	m_xAdjustment->SetMajorStep( 20 );
	m_xAdjustment->SetPageSize( 10 );

	m_yAdjustment->SetLower( 0 );
	m_yAdjustment->SetUpper( (70 * 32) - (mapSizeInPixels.y / 2) );
	m_yAdjustment->SetMinorStep( 10.f );
	m_yAdjustment->SetMajorStep( 20 );
	m_yAdjustment->SetPageSize( 10 );


	scrollbarX->GetSignal( sfg::Scrollbar::OnMouseLeftPress).Connect( std::bind( &MainGame::sliderPressed, this ) );
	scrollbarY->GetSignal( sfg::Scrollbar::OnMouseLeftPress).Connect( std::bind( &MainGame::sliderPressed, this ) );

//		m_xAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &MainGame::sliderAdjusted, this ) );
//		m_yAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &MainGame::sliderAdjusted, this ) );

//
	m_xAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( [this, &desktop, &mapSizeInPixels, &mapPanel]() {

		shouldScrollMap = true;
		m_viewDeltaFromSlider = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue()) - m_prevSliderValue;

		m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());
		const float y = mapPanel.getView().getCenter().y;
		std::cout << "y " << y << std::endl;

		m_center = sf::Vector2f((mapSizeInPixels.x /2 ) + m_xAdjustment->GetValue(),  y );
		} );

	m_yAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( [this, &desktop, &mapSizeInPixels, &mapPanel]() {

		shouldScrollMap = true;
		m_viewDeltaFromSlider = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue()) - m_prevSliderValue;
		std::cout << "m_viewDeltaFromSlider x:" << m_viewDeltaFromSlider.x << " y:" <<m_viewDeltaFromSlider.y << std::endl;

		m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());

		m_center = sf::Vector2f(mapPanel.getView().getCenter().x, (mapSizeInPixels.y /2 ) +  m_yAdjustment->GetValue());


		} );


	textureCanvas->SetRequisition(sf::Vector2f((spaceReservedForControls), 200.0f));
  //  sfmlWindow->Add(textureCanvas);
    mapWindow->Add(table);

 //   sfguiDesktop.Add(sfmlWindow);
    sfguiDesktop.Add(mapWindow);
	mainRenderWindow.resetGLStates();






	sf::Clock clock;
	while (mainRenderWindow.isOpen()) {
		sf::Event event;
		float dt = clock.restart().asMilliseconds();

		while (mainRenderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mainRenderWindow.close();
			}else if (event.type == sf::Event::MouseButtonPressed ) {
		        if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f absolutePosition = textureCanvas->GetAbsolutePosition();

		        	sf::Vector2i position(event.mouseButton.x, event.mouseButton.y );
					sf::Vector2i mousePos = position - sf::Vector2i(absolutePosition.x, absolutePosition.y);
					tilePanel.selectTileAt(mousePos);

		        }
		    }else if (event.type == sf::Event::MouseButtonReleased ) {
		        if ( isUsingSlider && event.mouseButton.button == sf::Mouse::Left) {
		        		isUsingSlider = false;
		        }
		    }
			sfguiDesktop.HandleEvent(event);
		}

		if (!isUsingSlider && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(mainRenderWindow);
			sf::Vector2f absolutePositionForMapCanvas = mapCanvas->GetAbsolutePosition();
			sf::Vector2i tileMapPos = mousePos - sf::Vector2i(absolutePositionForMapCanvas.x, absolutePositionForMapCanvas.y);
			sf::Vector2i positionWithScrollbarDelta = tileMapPos + m_prevSliderValue;
//			std::cout << "tileMapPos x:" << tileMapPos.x << " y:" <<tileMapPos.y << std::endl;
//			std::cout << "positionWithScrollbarDelta x:" << positionWithScrollbarDelta.x << " y:" <<positionWithScrollbarDelta.y << std::endl;
//			std::cout << "m_prevSliderValue x:" << m_prevSliderValue.x << " y:" <<m_prevSliderValue.y << std::endl;

			mapPanel.addTile(positionWithScrollbarDelta, tilePanel.getCurrentlySelectedTile());
		}

		sfguiDesktop.Update(1.0f / 60.0f);

		mainRenderWindow.clear();

		if(isUsingSlider ){
			//std::cout << "m_viewDeltaFromSlider x:" << m_viewDeltaFromSlider.x << " y:" <<m_viewDeltaFromSlider.y << std::endl;
			//mapPanel.updateMapView(sf::Vector2f(m_prevSliderValue.x, m_prevSliderValue.y));
			mapPanel.updateCenterMapView(m_center);
		}

		textureCanvas->Bind();
		textureCanvas->Clear(sf::Color(50, 50, 50));
		textureCanvas->Draw(tilePanel);
		textureCanvas->Display();
		textureCanvas->Unbind();



		mapCanvas->Bind();
		mapCanvas->Clear(sf::Color(50, 50, 50));
	//	mapCanvas->SetView(view);
		mapCanvas->Draw(mapPanel);
		mapCanvas->Display();
		mapCanvas->Unbind();

		mainRenderWindow.setActive(true);
		sfgui.Display(mainRenderWindow);
		mainRenderWindow.display();
		shouldScrollMap = false;
	}
}

int main() {
	MainGame game;
	game.run();

	return EXIT_SUCCESS;
}
