#include <game-editor/MapPanelController.h>
#include <iostream>

class MapPanelController::MapPanelControllerImpl{

public:

	ScrollableCanvas& m_scrollableCanvas;
	std::unique_ptr<MapPanel> m_mapPanel;

	MapPanelControllerImpl(ScrollableCanvas& canvas, std::unique_ptr<MapPanel> mapPanel) : m_scrollableCanvas(canvas), m_mapPanel(std::move(mapPanel)){
	}

	~MapPanelControllerImpl(){}

	void addTile(sf::Vector2i renderViewMousePos, Tile tile) {
		if(m_scrollableCanvas.isInBoundsAndSlidersNotInUse(renderViewMousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			auto  positionWithScrollbarDelta = m_scrollableCanvas.getCanvasMousePositionFrom(renderViewMousePos);
			m_mapPanel->addTile(positionWithScrollbarDelta, tile);
		}
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(*m_mapPanel);
	}

};

MapPanelController::~MapPanelController() {
}

MapPanelController::MapPanelController(ScrollableCanvas& canvas, std::unique_ptr<MapPanel> mapPanel) : m_impl(new MapPanelControllerImpl(canvas, std::move(mapPanel))){
}

void MapPanelController::addTile(sf::Vector2i mousePos, Tile tile)  {
	m_impl->addTile(mousePos, tile);
}

void MapPanelController::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}
