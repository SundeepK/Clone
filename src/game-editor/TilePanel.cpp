#include <game-editor/TilePanel.h>
#include <iostream>

class TilePanel::TilePanelImpl{
public:

	std::unique_ptr<sf::Texture> m_texture;
	int  m_width = 32;
	int  m_height = 32;
	std::vector<Tile> m_tiles;
	std::vector<sf::Vertex> m_vertices;
	std::vector<sf::Vertex> m_tileLinesVertices;
	int m_currentlySelectedTile;

	TilePanelImpl(sf::Texture& m_texture, int tileWidth, int tileHeight) : m_texture(&m_texture), m_width(tileWidth), m_height(tileHeight), m_currentlySelectedTile(0)  {
		sf::Vector2u resolution = m_texture.getSize();

		int imageWidthInTiles = resolution.x / m_width;
		int imageHeightInTiles = resolution.y / m_height;

		for(int row = 0; row < imageWidthInTiles  ; row++ ){
			for(int column = 0, x = row; column < imageHeightInTiles  ; column++, x++){
				sf::IntRect rect(row * m_width, column * m_height, m_width, m_height);
				Tile tile((row  ) + (column * imageWidthInTiles) + 1, rect);


				m_tiles.push_back(tile);
				auto texCoords = tile.getTexturedVertices();
				m_vertices.push_back(texCoords[0]);
				m_vertices.push_back(texCoords[1]);
				m_vertices.push_back(texCoords[2]);
				m_vertices.push_back(texCoords[3]);

				texCoords[0].color = sf::Color::White;
				texCoords[1].color = sf::Color::White;
				texCoords[2].color = sf::Color::White;
				texCoords[3].color = sf::Color::White;

			}
		}

		m_currentlySelectedTile = 0;
	}

	~TilePanelImpl(){}

	std::vector<Tile> update(sf::Vector2i mousePos) {
		for (int i = 0; i < m_tiles.size(); i++) {
			Tile tile = m_tiles[i];
			if (tile.m_rect.contains(mousePos)) {
				std::cout << "im slected: " << tile.getGid() << " x " << tile.m_rect.left << " y: " << tile.m_rect.top << std::endl;
				m_currentlySelectedTile = i;
				std::vector<Tile> tiles = { tile };
				return tiles;
			}
		}
		std::vector<Tile> tiles = { };
		return tiles;
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		states.texture = m_texture.get();
		rt.draw(&m_vertices[0], static_cast<unsigned int>(m_vertices.size()), sf::Quads, states);

		for(unsigned i = 0; i < m_vertices.size() ; i+=4 ){
			rt.draw(&m_vertices[i], 4, sf::LinesStrip);
		}

		std::vector<sf::Vertex> selectedTileVertexArray = m_tiles[m_currentlySelectedTile].getSelectedTexcoords();

		rt.draw(&selectedTileVertexArray[0], 4, sf::Quads);


	//	rt.draw(sprite, states);
	}

	Tile getCurrentlySelectedTile() {
		return m_tiles[m_currentlySelectedTile];
	}


};


TilePanel::TilePanel(sf::Texture& texture, int tileWdith, int tileHeight) : m_impl(new TilePanelImpl(texture, tileWdith, tileHeight)) {
}

TilePanel::~TilePanel() {
}

std::vector<Tile>  TilePanel::update(sf::Vector2i mousePos) {
	return m_impl->update(mousePos);
}

void TilePanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

Tile TilePanel::getCurrentlySelectedTile() {
	return m_impl->getCurrentlySelectedTile();
}
