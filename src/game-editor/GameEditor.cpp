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

	sfg::Window::Ptr m_mapWindow;
	sfg::Box::Ptr m_rightPanel;
	sfg::Box::Ptr m_mainBox;

	TilePanel m_tilePanel;
	sf::RenderWindow& m_mainRenderWindow;
    b2World m_b2world;
	LayerController m_layerController;
	ObjectCreatorController m_objectController;
	MapData m_mapData;
	ScrollableCanvas m_scrollableCanvas;
	MapPanelController m_mapPanelController;
	SFGUIDebugDraw m_debugDrawer;
	DrawStaticAABBSystem m_gameObjectAABBDrawSystem;
	anax::World m_anaxWorld;

	unsigned int spaceReservedForControls;

	sf::IntRect objectBounds;
	sf::RectangleShape objectBoundsRect;

	GameEditorImpl(sf::RenderWindow& mainRenderWindow, sf::Vector2f mapSizeInPixels, sf::Texture& texture) : m_tilePanel(texture, sf::Vector2i(mapSizeInPixels.x / 5,mapSizeInPixels.y), sf::Vector2i(32, 32)),
			m_mainRenderWindow(mainRenderWindow),  m_b2world(b2Vec2(0, 18.0f)), m_layerController(m_anaxWorld, m_b2world), m_objectController(m_anaxWorld, m_b2world),
			m_mapData(sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels)), m_scrollableCanvas(m_mapData),
			m_mapPanelController(m_scrollableCanvas, std::unique_ptr<MapPanel>(new MapPanel (texture, sf::Vector2i(70, 70), sf::Vector2i(32, 32), sf::Vector2i(mapSizeInPixels)))),
			m_debugDrawer(m_scrollableCanvas.getCanvas()){


		spaceReservedForControls = mainRenderWindow.getSize().x / 5;

		m_mainBox = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );
		m_rightPanel =  sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
		m_mapWindow = sfg::Window::Create(sfg::Window::RESIZE);


		m_b2world.SetAllowSleeping(true);
		m_b2world.SetContinuousPhysics(false);

		m_b2world.SetDebugDraw(&m_debugDrawer);
		m_debugDrawer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);


		m_mapWindow->SetRequisition(mapSizeInPixels);
		m_mapWindow->SetPosition(sf::Vector2f(0,0));

		m_rightPanel->SetSpacing(10);

		m_scrollableCanvas.attachTo(m_mainBox);
		m_mainBox->Pack(m_rightPanel);

		m_layerController.attachTo(m_rightPanel);
		m_objectController.addEntityCreator("boulder", std::unique_ptr<GameEntityCreator>(new Boulder()));
		m_objectController.addEntityCreator("rope", std::unique_ptr<GameEntityCreator>(new Rope()));
		m_objectController.attachTo(m_rightPanel);
		m_tilePanel.attachTo(m_rightPanel);

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

	void handleObjectCreation(sf::Event& event, sf::Vector2i canvasMousePos, Layer& currentLayer, bool isInBoundsAndSliderNotInUse) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = m_tilePanel.getCanvasMousePositionFrom(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				m_tilePanel.selectTileAt(mousePos);
				if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse) {
					objectBounds.top = canvasMousePos.y;
					objectBounds.left = canvasMousePos.x;
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse) {
					objectBounds.height = canvasMousePos.y - objectBounds.top;
					objectBounds.width = canvasMousePos.x - objectBounds.left;
					auto mapObject = m_objectController.createGameObjectAt(objectBounds);
					m_layerController.addMapObjectToCurrentLayer(mapObject);
				}
			}
		}
	}

	void updateObjectaabb(Layer& currentLayer, sf::Vector2i canvasMousePosition, bool isInBoundsAndSliderNotInUse){
		if (currentLayer.getLayerType() == LayerType::OBJECTS && isInBoundsAndSliderNotInUse && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					objectBounds.height = canvasMousePosition.y - objectBounds.top;
					objectBounds.width = canvasMousePosition.x - objectBounds.left;
			}
	}

	void handleAddingTile(Layer& currentLayer){
		if(currentLayer.getLayerType() == LayerType::TILE){
				auto remnderWindowMousePos = sf::Mouse::getPosition(m_mainRenderWindow);
				m_mapPanelController.addTile(remnderWindowMousePos, m_tilePanel.getCurrentlySelectedTile());
			}
	}

	void update(){
			sf::Event event;
			auto currentLayerOptional = m_layerController.getCurrentlySelectedLayer();
			Layer currentLayer = currentLayerOptional.get();
			std::vector<sf::Event> events;
			auto remnderWindowMousePos = sf::Mouse::getPosition(m_mainRenderWindow);
			auto canvasMousePosition = m_scrollableCanvas.getCanvasMousePositionFrom(remnderWindowMousePos);
			bool isInBoundsAndSliderNotInUse = m_scrollableCanvas.isInBoundsAndSlidersNotInUse(remnderWindowMousePos);

			while (m_mainRenderWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					m_mainRenderWindow.close();
				}

				handleObjectCreation(event, canvasMousePosition, currentLayer, isInBoundsAndSliderNotInUse);

				m_sfguiDesktop.HandleEvent(event);
				events.push_back(event);
			}

			updateObjectaabb(currentLayer, canvasMousePosition, isInBoundsAndSliderNotInUse);

			m_scrollableCanvas.updateCanvas(events);
			m_layerController.update(canvasMousePosition, events);

			//should always have a selected layer, but just in case
			handleAddingTile(currentLayer);

			m_sfguiDesktop.Update(1.0f / 60.0f);

			m_mainRenderWindow.clear();

			m_b2world.Step(1.f/60.f, 8, 3);
			m_anaxWorld.refresh();
			m_gameObjectAABBDrawSystem.updateAABBs();

			m_tilePanel.beginDraw();
			m_tilePanel.endDraw();

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
