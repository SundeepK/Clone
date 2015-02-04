#include <game-editor/TileMap.h>

TileMap::TileMap(sf::Vector2i mapSizeInTiles, sf::Vector2i tileDimensions) {
	for(int row = 0; row < mapSizeInTiles.x  ; row++ ){
		for(int column = 0, x = row; column < mapSizeInTiles.y ; column++, x++){
			sf::IntRect rect(row * tileDimensions.x, column * tileDimensions.y, tileDimensions.x, tileDimensions.y);
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
}

TileMap::~TileMap() {
}

std::vector<Tile> TileMap::getTile(sf::Vector2i mousePos) {
	for (sf::Uint32 i = 0; i < m_tiles.size(); i++) {
		Tile tile = m_tiles[i];
		if (tile.m_rect.contains(mousePos)) {
			return {tile};
		}
	}
	return {};
}

void TileMap::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	for(unsigned i = 0; i < m_vertices.size() ; i+=4 ){
		rt.draw(&m_vertices[i], 4, sf::LinesStrip);
	}
}
