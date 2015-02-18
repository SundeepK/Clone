#ifndef SRC_GAME_EDITOR_SCROLLABLECANVAS_H_
#define SRC_GAME_EDITOR_SCROLLABLECANVAS_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <memory>

struct MapData{

public:
	MapData(sf::Vector2i mapSizeInTiles, sf::Vector2i tileSize, sf::Vector2i mapSizeInPixels) :
		m_mapSizeInTiles(mapSizeInTiles), m_tileSize(tileSize), m_mapSizeInPixels(mapSizeInPixels) {
	}

	sf::Vector2i getMapSizeInPixels() const {
		return m_mapSizeInPixels;
	}

	sf::Vector2i getMapSizeInTiles() const {
		return m_mapSizeInTiles;
	}

	sf::Vector2i getTileSize() const {
		return m_tileSize;
	}

private:
	sf::Vector2i m_mapSizeInTiles;
	sf::Vector2i m_tileSize;
	sf::Vector2i m_mapSizeInPixels;
};

class ScrollableCanvas : public sf::Drawable  {
public:
	ScrollableCanvas(MapData mapData);
	~ScrollableCanvas();

	sf::Vector2i getCanvasMousePositionFrom(sf::Vector2i renderWindowMousePos);
	bool isInCanvasBounds(sf::Vector2i renderWindowMousePos);
	bool isInBoundsAndSlidersNotInUse(sf::Vector2i renderWindowMousePos);
	void updateCanvas(std::vector<sf::Event>& events);
	void draw();
	void attachTo(sfg::Box::Ptr box);
	sfg::Canvas::Ptr getCanvas();

	void beginDraw();
	void draw(const sf::Drawable& drawable);
	void endDraw();


private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class ScrollableCanvasImpl;
	std::unique_ptr<ScrollableCanvasImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_SCROLLABLECANVAS_H_ */
