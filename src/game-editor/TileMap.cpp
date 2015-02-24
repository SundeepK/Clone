#include <game-editor/TileMap.h>

TileMap::TileMap(sf::Vector2i mapSizeInTiles, sf::Vector2i tileDimensions) : m_mapSizeInTiles(mapSizeInTiles), m_tileDimensions(tileDimensions)  {
	sf::Color grey(100, 100, 100);
	for(int row = 0; row < mapSizeInTiles.x  ; row++ ){
		for(int column = 0, x = row; column < mapSizeInTiles.y ; column++, x++){
			sf::IntRect rect(row * tileDimensions.x, column * tileDimensions.y, tileDimensions.x, tileDimensions.y);
			Tile tile((row  ) + (column * mapSizeInTiles.x) + 1, rect);
			m_tiles.push_back(tile);
			auto texCoords = tile.getTexturedVertices();
			m_tileVertices.push_back(texCoords[0]);
			m_tileVertices.push_back(texCoords[1]);
			m_tileVertices.push_back(texCoords[2]);
			m_tileVertices.push_back(texCoords[3]);
			texCoords[0].color = grey;
			texCoords[1].color = grey;
			texCoords[2].color = grey;
			texCoords[3].color = grey;
			m_vertices.push_back(texCoords[0]);
			m_vertices.push_back(texCoords[1]);
			m_vertices.push_back(texCoords[2]);
			m_vertices.push_back(texCoords[3]);
		}
	}
}

TileMap::~TileMap() {
}

boost::optional<Tile> TileMap::getTile(sf::Vector2i mousePos) {
	for (Tile tile : m_tiles) {
		if (tile.m_rect.contains(mousePos)) {
			return boost::optional<Tile>(tile);
		}
	}
	return boost::optional<Tile>();
}

void TileMap::draw(sf::RenderTarget& rt, sf::RenderStates states, bool shouldDrawTexture) const {
	for(unsigned i = 0; i < m_vertices.size() ; i+=4 ){
		rt.draw(&m_vertices[i], 4, sf::LinesStrip);
	}

	if(states.texture && shouldDrawTexture){
		rt.draw(&m_tileVertices[0], static_cast<unsigned int>(m_tileVertices.size()), sf::Quads, states);
	}
}

boost::optional<Tile> TileMap::getTile(int idOfTile) const{
	if(idOfTile < 0 || idOfTile >  m_tiles.size()){
		return boost::optional<Tile>();
	}

	auto foundItr = std::find_if(m_tiles.begin(), m_tiles.end(), [idOfTile](const Tile& tile) { return tile.getGid() == idOfTile;} );

	if(foundItr != m_tiles.end()){
		Tile tile(foundItr->getGid(), foundItr->m_rect);
		return boost::optional<Tile>(tile);
	}else{
		return boost::optional<Tile>();
	}
}

sf::Vector2i TileMap::getMapSizeInTiles()  {
	return m_mapSizeInTiles;
}

sf::Vector2i TileMap::getTileDimensions()  {
	return m_tileDimensions;
}
