#include <game-editor/GameEditor.h>
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


class GameEditor::GameEditorImpl{

public:

	sfg::SFGUI m_sfgui;
	sfg::Desktop m_sfguiDesktop;
	sfg::Canvas::Ptr m_textureCanvas;

	sfg::Window::Ptr m_mapWindow;
	sfg::Scrollbar::Ptr m_scrollbarY;
	sfg::Scrollbar::Ptr m_scrollbarX;
	sfg::Table::Ptr m_table;
	sfg::Box::Ptr m_rightPanel;
	sfg::Box::Ptr m_mainBox;

	TilePanel m_tilePanel;
	ObjectCreatorController m_objectController;
	LayerController m_layerController;
	MapData m_mapData;
	ScrollableCanvas m_scrollableCanvas;
	MapPanelController m_mapPanelController;
	DrawStaticAABBSystem m_gameObjectAABBDrawSystem;
	SFGUIDebugDraw m_debugDrawer;

	sf::RenderWindow& m_mainRenderWindow;


    b2World m_b2world;

	anax::World m_anaxWorld;

	unsigned int spaceReservedForControls;

	sf::IntRect objectBounds;
	sf::RectangleShape objectBoundsRect;

	GameEditorImpl(sf::RenderWindow& mainRenderWindow, sf::Vector2f mapSizeInPixels, sf::Texture& texture) : m_tilePanel(texture, 32, 32), m_mainRenderWindow(mainRenderWindow),  m_b2world(b2Vec2(0, 18.0f)),
			m_layerController(m_anaxWorld, m_b2world), m_objectController(m_anaxWorld, m_b2world),
			m_mapData(sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels)), m_scrollableCanvas(m_mapData),
			m_mapPanelController(m_scrollableCanvas, std::unique_ptr<MapPanel>(new MapPanel (texture, sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels)))),
			m_debugDrawer(m_scrollableCanvas.getCanvas()){


		spaceReservedForControls = mainRenderWindow.getSize().x / 5;

		m_textureCanvas = sfg::Canvas::Create();

	    //box2d stuff
		//	m_b2world.SetAutoClearForces(false);
		m_b2world.SetAllowSleeping(true);
		m_b2world.SetContinuousPhysics(false);

		m_b2world.SetDebugDraw(&m_debugDrawer);
		m_debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);

		m_mapWindow = sfg::Window::Create(sfg::Window::RESIZE);

		m_mapWindow->SetRequisition(mapSizeInPixels);
		m_mapWindow->SetPosition(sf::Vector2f(0,0));

		m_textureCanvas->SetRequisition(sf::Vector2f((spaceReservedForControls),  texture.getSize().y));
		m_table = sfg::Table::Create();

		m_rightPanel =  sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_rightPanel->SetSpacing(10);

		m_mainBox = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

		m_scrollableCanvas.attachTo(m_mainBox);
		m_mainBox->Pack(m_rightPanel);
		//m_table->Attach( m_rightPanel, sf::Rect<sf::Uint32>(  2, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL );

		m_layerController.attachTo(m_rightPanel);
		m_objectController.addEntityCreator("boulder", std::unique_ptr<GameEntityCreator>(new Boulder()));
		m_objectController.addEntityCreator("rope", std::unique_ptr<GameEntityCreator>(new Rope()));
		m_objectController.attachTo(m_rightPanel);
		m_rightPanel->Pack(m_textureCanvas, true, false);


		m_layerController.addLayer("Entities", LayerType::OBJECTS);

	    m_mapWindow->Add(m_mainBox);

	    m_sfguiDesktop.Add(m_mapWindow);

		objectBoundsRect.setFillColor(sf::Color::Transparent);
		objectBoundsRect.setOutlineThickness(2.0f);
		objectBoundsRect.setOutlineColor(sf::Color::Red);
		m_anaxWorld.addSystem(m_gameObjectAABBDrawSystem);


	}

	~GameEditorImpl(){

	}

	void update(){
			sf::Event event;
			auto currentLayerOptional = m_layerController.getCurrentlySelectedLayer();
			std::vector<sf::Event> events;
			auto remnderWindowMousePos = sf::Mouse::getPosition(m_mainRenderWindow);
			auto canvasMousePosition = m_scrollableCanvas.getCanvasMousePositionFrom(remnderWindowMousePos);
			bool isInBoundsAndSliderNotInUse = m_scrollableCanvas.isInBoundsAndSlidersNotInUse(remnderWindowMousePos);

			while (m_mainRenderWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					m_mainRenderWindow.close();
				} else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						sf::Vector2f absolutePosition = m_textureCanvas->GetAbsolutePosition();

						sf::Vector2i position(event.mouseButton.x, event.mouseButton.y);
						sf::Vector2i mousePos = position - sf::Vector2i(absolutePosition.x, absolutePosition.y);
						m_tilePanel.selectTileAt(mousePos);

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

								auto mapObject = m_objectController.createGameObjectAt(objectBounds);
								m_layerController.addMapObjectToCurrentLayer(mapObject);
							}
						}
					}
				}
				m_sfguiDesktop.HandleEvent(event);
				events.push_back(event);
			}

			if (currentLayerOptional) {
					Layer currentLayer = currentLayerOptional.get();
					if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							objectBounds.height = canvasMousePosition.y - objectBounds.top;
							objectBounds.width = canvasMousePosition.x - objectBounds.left;
					}
			}

			m_scrollableCanvas.updateCanvas(events);
			m_layerController.update(canvasMousePosition, events);

			//should always have a selected layer, but just in case
			if(currentLayerOptional){
				Layer currentLayer = currentLayerOptional.get();
				if(currentLayer.getLayerType() == LayerType::TILE){
					m_mapPanelController.addTile(remnderWindowMousePos, m_tilePanel.getCurrentlySelectedTile());
				}
			}else{
				std::cerr << "No currently selected layer found" << std::endl;
			}


			m_sfguiDesktop.Update(1.0f / 60.0f);

			m_mainRenderWindow.clear();

			m_b2world.Step(1.f/60.f, 8, 3);
			m_anaxWorld.refresh();
			m_gameObjectAABBDrawSystem.updateAABBs();

			m_textureCanvas->Bind();
			m_textureCanvas->Clear(sf::Color(50, 50, 50));
			m_textureCanvas->Draw(m_tilePanel);
			m_textureCanvas->Display();
			m_textureCanvas->Unbind();

			m_scrollableCanvas.beginDraw();
			m_b2world.DrawDebugData();
			m_scrollableCanvas.draw(m_mapPanelController);
			objectBoundsRect.setPosition(sf::Vector2f(objectBounds.left, objectBounds.top));
			objectBoundsRect.setSize(sf::Vector2f(objectBounds.width, objectBounds.height));
			m_scrollableCanvas.draw(objectBoundsRect);
			m_scrollableCanvas.draw(m_gameObjectAABBDrawSystem);
			m_scrollableCanvas.endDraw();

			m_mainRenderWindow.setActive(true);
			m_sfgui.Display(m_mainRenderWindow);
			m_mainRenderWindow.display();

	}


};


GameEditor::GameEditor(sf::RenderWindow& mainRenderWindow, sf::Vector2f mapSizeInPixels, sf::Texture& texture) : m_impl(new GameEditorImpl(mainRenderWindow, mapSizeInPixels, texture)){
}

GameEditor::~GameEditor() {
}

void GameEditor::update() {
	m_impl->update();
}
