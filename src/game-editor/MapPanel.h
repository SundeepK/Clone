#ifndef SRC_GAME_EDITOR_MAPPANEL_H_
#define SRC_GAME_EDITOR_MAPPANEL_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>

class MapPanel : public sf::Drawable{
public:
	MapPanel(sf::Texture& m_texture, sf::Vector2f mapSizeInTiles, int tileWidth, int tileHeight);
	~MapPanel();

	bool addTile(sf::Vector2i mousePos, Tile tileToDraw);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class MapPanelImpl;
	std::unique_ptr<MapPanelImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_MAPPANEL_H_ */
