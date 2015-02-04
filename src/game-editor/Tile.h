#ifndef SRC_GAME_EDITOR_TILE_H_
#define SRC_GAME_EDITOR_TILE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Tile {
public:

	struct TileHasher
	{
	  std::size_t operator()(const Tile& tile) const
	  {
	    using std::size_t;
	    using std::hash;
	    using std::string;

	    int left = tile.m_rect.left;
	    int top = tile.m_rect.top;
	    int width = tile.m_rect.width;
	    int height = tile.m_rect.height;

	    return ((hash<int>()(tile.m_gid)
	             ^ (hash<int>()(left) << 1)) >> 1
	    		 ^ (hash<int>()(top) << 1) >> 1
	    		 ^ (hash<int>()(width) << 1) >> 1
	    		 ^ (hash<int>()(height) << 1) >> 1);
	  }
	};

	Tile();
	Tile(int gid, sf::IntRect rect);
	~Tile();
	Tile(const Tile& tile);

	int m_gid;
	sf::IntRect m_rect;
	std::vector<sf::Vector2f> m_coords;
	bool operator <(const Tile& rhs) const;
	bool operator==(const Tile &other) const;

	int getGid() const;
	const std::vector<sf::Vertex> getSelectedTexcoords() const;
	std::vector<sf::Vertex> getTexturedVertices();
	std::vector<sf::Vertex> getTexturedVerticesWithPosition(sf::IntRect rect);

};

#endif /* SRC_GAME_EDITOR_TILE_H_ */
