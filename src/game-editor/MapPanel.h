#ifndef SRC_GAME_EDITOR_MAPPANEL_H_
#define SRC_GAME_EDITOR_MAPPANEL_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>

class MapPanel : public sf::Drawable{
public:
	MapPanel(sf::Texture& m_texture, sf::Vector2i mapSizeInTiles, int tileWidth, int tileHeight, sf::Vector2i resolution);
	~MapPanel();

	void addTile(sf::Vector2i mousePos, Tile tileToDraw);
	void updateMapView(sf::Vector2f sliderOffset);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class MapPanelImpl;
	std::unique_ptr<MapPanelImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_MAPPANEL_H_ */
