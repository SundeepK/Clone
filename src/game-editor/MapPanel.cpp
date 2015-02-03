#include <game-editor/MapPanel.h>
#include <iostream>

class MapPanel::MapPanelImpl{
public:

	std::unique_ptr<sf::Texture> m_texture;
	int  m_width = 32;
	int  m_height = 32;
	int m_currentlySelectedTile = 0;
	std::vector<Tile> m_tiles;
	std::vector<sf::Vertex> m_vertices;
	std::vector<Tile> m_texturedTiles;


	MapPanelImpl(sf::Texture& texture, sf::Vector2f mapSizeInTiles, int tileWidth, int tileHeight) : m_texture(&texture), m_width(tileWidth), m_height(tileHeight){

		for(int row = 0; row < mapSizeInTiles.x  ; row++ ){
			for(int column = 0, x = row; column < mapSizeInTiles.y ; column++, x++){
				sf::IntRect rect(row * m_width, column * m_height, m_width, m_height);
				Tile tile((row  ) + (column * mapSizeInTiles.x) + 1, rect);

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

	~MapPanelImpl(){}

	bool addTile(sf::Vector2i mousePos, Tile tileToDraw) {
		for (int i = 0; i < m_tiles.size(); i++) {
			Tile tile = m_tiles[i];
			if (tile.m_rect.contains(mousePos)) {
				std::cout << "im slected: " << tile.getGid() << " x " << tile.m_rect.left << " y: " << tile.m_rect.top << std::endl;
				tileToDraw.m_gid = i;
				m_texturedTiles.push_back(tileToDraw);
				m_currentlySelectedTile = i;
				return true;
			}
		}
		return false;
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		states.texture = m_texture.get();

		for(unsigned i = 0; i < m_vertices.size() ; i+=4 ){
			rt.draw(&m_vertices[i], 4, sf::LinesStrip);
		}

		for(Tile tile : m_texturedTiles){
			auto ti = m_tiles[tile.getGid()];
			auto vertexArray = tile.getTexturedVerticesWithPosition(ti.m_rect);
			rt.draw(&vertexArray[0], 4, sf::Quads, states);
		}

	}


};

MapPanel::MapPanel(sf::Texture& texture, sf::Vector2f mapSizeInTiles, int tileWidth, int tileHeight) : m_impl(new MapPanelImpl(texture, mapSizeInTiles, tileWidth, tileHeight)) {
}

MapPanel::~MapPanel() {
}

void MapPanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

bool MapPanel::addTile(sf::Vector2i mousePos, Tile tileToDraw) {
	return m_impl->addTile(mousePos, tileToDraw);
}
