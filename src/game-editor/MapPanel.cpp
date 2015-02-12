#include <game-editor/MapPanel.h>
#include <game-editor/TileMap.h>
#include <iostream>
#include <unordered_map>
#include <TemplateHasher.h>

class MapPanel::MapPanelImpl{
public:

	std::unique_ptr<sf::Texture> m_texture;
	std::unordered_map<Tile, Tile, Tile::TileHasher> m_mapTileToTextureTile;
	sf::View m_view;
	TileMap m_tileMap;
	sf::Vector2i m_mapSizeInPixels;

	MapPanelImpl(sf::Texture& texture, sf::Vector2i mapSizeInTiles, sf::Vector2i tileSize, sf::Vector2i resolution) : m_texture(&texture),
				m_view(sf::Vector2f(resolution.x / 2,resolution.y / 2) , sf::Vector2f(resolution)), m_tileMap(mapSizeInTiles, sf::Vector2i(tileSize.x, tileSize.y)), m_mapSizeInPixels(resolution){
	}

	~MapPanelImpl(){}

	void addTile(sf::Vector2i mousePos, Tile tileToDraw) {
		auto tileFound = m_tileMap.getTile(mousePos);
		if (tileFound) {
			Tile tile = tileFound.get();
			auto tileItr = m_mapTileToTextureTile.find(tile);
			if (tileItr != m_mapTileToTextureTile.end()) {
				m_mapTileToTextureTile[tile] = tileToDraw;
			} else {
				m_mapTileToTextureTile.insert(std::make_pair(tile, tileToDraw));
			}

		}
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.setView(m_view);
		states.texture = m_texture.get();
		m_tileMap.draw(rt, states);
		for(auto mapItr=m_mapTileToTextureTile.begin(); mapItr!=m_mapTileToTextureTile.end(); ++mapItr) {
			auto mapTile = mapItr->first;
			auto textureTile = mapItr->second;
			auto vertexArray =textureTile.getTexturedVerticesWithPosition(mapTile.m_rect);
			rt.draw(&vertexArray[0], 4, sf::Quads, states);
		}
	}

	void updateMapView(sf::Vector2f sliderOffset) {
		m_view.move(sliderOffset);
	}

	void updateCenterMapView(sf::Vector2f center) {
		m_view.setCenter(center);
	}

	sf::View getView() {
		return m_view;
	}

	sf::Vector2i getMapSizeInPixels(){
		return m_mapSizeInPixels;
	}


};

MapPanel::MapPanel(sf::Texture& texture, sf::Vector2i mapSizeInTiles, sf::Vector2i tileSize, sf::Vector2i resolution) :
		m_impl(new MapPanelImpl(texture, mapSizeInTiles, tileSize, resolution)) {
}

MapPanel::~MapPanel() {
}

void MapPanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

void MapPanel::addTile(sf::Vector2i mousePos, Tile tileToDraw) {
	m_impl->addTile(mousePos, tileToDraw);
}

void MapPanel::updateMapView(sf::Vector2f sliderOffset) {
	m_impl->updateMapView(sliderOffset);
}

void MapPanel::updateCenterMapView(sf::Vector2f center) {
	m_impl->updateCenterMapView(center);
}

sf::View MapPanel::getView() {
	return m_impl->getView();
}

sf::Vector2i MapPanel::getMapSizeInTiles() {
	return m_impl->m_tileMap.getMapSizeInTiles();
}

sf::Vector2i MapPanel::getTileSize() {
	return m_impl->m_tileMap.getTileDimensions();
}

sf::Vector2i MapPanel::getMapSizeInPixels() {
	return m_impl->getMapSizeInPixels();
}
