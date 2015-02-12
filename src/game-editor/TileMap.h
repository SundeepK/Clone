#ifndef SRC_GAME_EDITOR_TILEGENERATOR_H_
#define SRC_GAME_EDITOR_TILEGENERATOR_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>
#include <boost/optional.hpp>


class TileMap{
public:
	TileMap(sf::Vector2i mapSizeInTiles, sf::Vector2i tileDimensions);
	~TileMap();

	boost::optional<Tile> getTile(sf::Vector2i mousePos);
	std::vector<sf::Vertex> getVerticies();
    void draw(sf::RenderTarget& rt, sf::RenderStates states, bool shouldDrawTexture = false) const;
    boost::optional<Tile> getTile(int idOfTile) const;
	sf::Vector2i getMapSizeInTiles();
	sf::Vector2i getTileDimensions();

private:

	std::vector<Tile> m_tiles;
	std::vector<sf::Vertex> m_vertices;
	sf::Vector2i m_mapSizeInTiles;
	sf::Vector2i m_tileDimensions;

};


#endif /* SRC_GAME_EDITOR_TILEGENERATOR_H_ */
