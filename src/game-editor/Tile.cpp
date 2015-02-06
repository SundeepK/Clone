#include <game-editor/Tile.h>

void Tile::initCoords(const sf::IntRect& rect) {
	m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)));
	m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top)));
	m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top + rect.height)));
	m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top + rect.height)));
}

Tile::Tile(int gid, sf::IntRect rect): m_gid(gid), m_rect(rect) {
	initCoords(m_rect);
}

Tile::~Tile() {
}

int Tile::getGid() const {
	return m_gid;
}

const std::vector<sf::Vertex> Tile::getSelectedTexcoords() const {
	sf::Vertex v0, v1, v2, v3;

	//applying half pixel trick avoids artifacting when scrolling
	v0.texCoords = m_coords[0] + sf::Vector2f(0.5f, 0.5f);
	v1.texCoords = m_coords[1] + sf::Vector2f(-0.5f, 0.5f);
	v2.texCoords = m_coords[2] + sf::Vector2f(-0.5f, -0.5f);
	v3.texCoords = m_coords[3] + sf::Vector2f(0.5f, -0.5f);

	v0.position = m_coords[0];
	v1.position = m_coords[1];
	v2.position = m_coords[2];
	v3.position = m_coords[3];

	sf::Color colour = sf::Color::Yellow;
	colour.a = 50;
	v0.color = colour;
	v1.color = colour;
	v2.color = colour;
	v3.color = colour;

	std::vector<sf::Vertex> texcoords = { v0, v1, v2, v3 };
	return texcoords;
}

std::vector<sf::Vertex> Tile::getTexturedVertices() {
	sf::Vertex v0, v1, v2, v3;

	//applying half pixel trick avoids artifacting when scrolling
	v0.texCoords = m_coords[0] + sf::Vector2f(0.5f, 0.5f);
	v1.texCoords = m_coords[1] + sf::Vector2f(-0.5f, 0.5f);
	v2.texCoords = m_coords[2] + sf::Vector2f(-0.5f, -0.5f);
	v3.texCoords = m_coords[3] + sf::Vector2f(0.5f, -0.5f);

	v0.position = m_coords[0];
	v1.position = m_coords[1];
	v2.position = m_coords[2];
	v3.position = m_coords[3];

	sf::Color colour = sf::Color(255u, 255u, 255u, 255u);

	v0.color = colour;
	v1.color = colour;
	v2.color = colour;
	v3.color = colour;

	std::vector<sf::Vertex> texcoords = { v0, v1, v2, v3 };
	return texcoords;
}

bool Tile::operator <(const Tile& rhs) const {
	return this->m_gid < rhs.m_gid;
}

bool Tile::operator ==(const Tile& other) const {
	return this->m_gid == other.m_gid;
}

Tile::Tile(const Tile& tile) {
	this->m_gid = tile.m_gid;
	this->m_rect = tile.m_rect;
	this->m_coords = tile.m_coords;
}

Tile::Tile() : m_gid(0), m_rect(0,0,0,0) {
	initCoords(m_rect);
}

std::vector<sf::Vertex> Tile::getTexturedVerticesWithPosition(sf::IntRect rect) {
	sf::Vertex v0, v1, v2, v3;

	//applying half pixel trick avoids artifacting when scrolling
	v0.texCoords = m_coords[0] + sf::Vector2f(0.5f, 0.5f);
	v1.texCoords = m_coords[1] + sf::Vector2f(-0.5f, 0.5f);
	v2.texCoords = m_coords[2] + sf::Vector2f(-0.5f, -0.5f);
	v3.texCoords = m_coords[3] + sf::Vector2f(0.5f, -0.5f);

	v0.position = sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top));
	v1.position = sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top));
	v2.position = sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top + rect.height));
	v3.position = sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top + rect.height));

	sf::Color colour = sf::Color(255u, 255u, 255u, 255u);

	v0.color = colour;
	v1.color = colour;
	v2.color = colour;
	v3.color = colour;

	std::vector<sf::Vertex> texcoords = { v0, v1, v2, v3 };
	return texcoords;
}

