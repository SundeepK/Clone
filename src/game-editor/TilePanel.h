#ifndef SRC_GAME_EDITOR_TILEPANEL_H_
#define SRC_GAME_EDITOR_TILEPANEL_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>

class TilePanel : public sf::Drawable {
public:
	TilePanel(sf::Texture& texture, int tileWdith, int tileHeight);
	~TilePanel();

	std::vector<Tile>  update(sf::Vector2i mousePos);
	Tile getCurrentlySelectedTile();

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    class TilePanelImpl;
    std::unique_ptr<TilePanelImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_TILEPANEL_H_ */
