#ifndef SRC_GAME_EDITOR_TILE_H_
#define SRC_GAME_EDITOR_TILE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Tile {
public:
	Tile(int gid, sf::IntRect rect);
	~Tile();

	int m_gid;
	sf::IntRect m_rect;
	std::vector<sf::Vector2f> m_coords;

	int getGid() const;
	const std::vector<sf::Vertex> getSelectedTexcoords() const;
	std::vector<sf::Vertex> getTexturedVertices();

};

#endif /* SRC_GAME_EDITOR_TILE_H_ */
