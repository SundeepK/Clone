#ifndef SRC_GAME_EDITOR_TILEPANEL_H_
#define SRC_GAME_EDITOR_TILEPANEL_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class TilePanel : public sf::Drawable {
public:
	TilePanel(sf::Texture& texture, sf::Vector2i tilePanelSize, sf::Vector2i tileSize);
	~TilePanel();

	void selectTileAt(sf::Vector2i mousePos);
	Tile getCurrentlySelectedTile();
	void attachTo(sfg::Box::Ptr box);
	void beginDraw();
	void draw(const sf::Drawable& drawable);
	void endDraw();
	sf::Vector2i getCanvasMousePositionFrom(sf::Vector2i renderWindowMousePos);


private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    class TilePanelImpl;
    std::unique_ptr<TilePanelImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_TILEPANEL_H_ */
