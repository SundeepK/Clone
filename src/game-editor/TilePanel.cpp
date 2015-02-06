#include <game-editor/TilePanel.h>
#include <iostream>
#include <game-editor/TileMap.h>

class TilePanel::TilePanelImpl{
public:

	std::unique_ptr<sf::Texture> m_texture;
	int m_currentlySelectedTile;
	TileMap m_tileMap;

	TilePanelImpl(sf::Texture& m_texture, int tileWidth, int tileHeight) : m_texture(&m_texture), m_currentlySelectedTile(0),
			m_tileMap(sf::Vector2i(m_texture.getSize().x / tileWidth,  m_texture.getSize().y / tileHeight), sf::Vector2i(tileWidth, tileHeight)){

	}

	~TilePanelImpl(){}

	void selectTileAt(sf::Vector2i mousePos) {
		auto tile = m_tileMap.getTile(mousePos);
		if(tile){
			m_currentlySelectedTile = tile.get().m_gid;
		}
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		states.texture = m_texture.get();
		m_tileMap.draw(rt, states, true);

		auto tile = m_tileMap.getTile(m_currentlySelectedTile);
		if (tile) {
			std::vector<sf::Vertex> selectedTileVertexArray = tile.get().getSelectedTexcoords();
			rt.draw(&selectedTileVertexArray[0], 4, sf::Quads);
		}
	}

	Tile getCurrentlySelectedTile() {
		auto tileOption = m_tileMap.getTile(m_currentlySelectedTile);
		if(tileOption){
			Tile tile = tileOption.get();
			return tile;
		}
		return Tile();
	}


};


TilePanel::TilePanel(sf::Texture& texture, int tileWdith, int tileHeight) : m_impl(new TilePanelImpl(texture, tileWdith, tileHeight)) {
}

TilePanel::~TilePanel() {
}

void TilePanel::selectTileAt(sf::Vector2i mousePos) {
	 m_impl->selectTileAt(mousePos);
}

void TilePanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

Tile TilePanel::getCurrentlySelectedTile() {
	return m_impl->getCurrentlySelectedTile();
}
