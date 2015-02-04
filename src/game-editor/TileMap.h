#ifndef SRC_GAME_EDITOR_TILEGENERATOR_H_
#define SRC_GAME_EDITOR_TILEGENERATOR_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <game-editor/Tile.h>

class TileMap : public sf::Drawable{
public:
	TileMap(sf::Vector2i mapSizeInTiles, sf::Vector2i tileDimensions);
	~TileMap();

	std::vector<Tile> getTile(sf::Vector2i mousePos);
	std::vector<sf::Vertex> getVerticies();
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

private:


	std::vector<Tile> m_tiles;
	std::vector<sf::Vertex> m_vertices;

};


#endif /* SRC_GAME_EDITOR_TILEGENERATOR_H_ */
