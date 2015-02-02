#include <game-editor/TilePanel.h>
#include <iostream>

class TilePanel::TilePanelImpl{
public:
	class Tile{
	public:
		int m_gid;
		sf::IntRect m_rect;
		std::vector<sf::Vector2f> m_coords;

		Tile(int gid, sf::IntRect rect): m_gid(gid), m_rect(rect) {
			m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)));
			m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top)));
			m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left + rect.width), static_cast<float>(rect.top + rect.height)));
			m_coords.push_back(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top + rect.height)));
		}

		~Tile(){}


		int getGid() const {
			return m_gid;
		}

		std::vector<sf::Vertex> getTexcoords(){
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

			std::vector<sf::Vertex> texcoords = {v0, v1, v2, v3};
			return texcoords;
		}

	};


	sf::Image m_image;
	sf::Texture m_texture;
	sf::Sprite sprite;
	const int  WIDTH = 32;
	const int  HEIGHT = 32;
	std::vector<Tile> m_tiles;
	std::vector<sf::Vertex> m_vertices;
	std::vector<sf::Vertex> m_tileLinesVertices;

	TilePanelImpl(std::string imageFilePath)  {
		m_image.loadFromFile(imageFilePath);
		m_texture.loadFromImage(m_image);
		sprite.setTexture( m_texture );

		sf::Vector2u resolution = m_image.getSize();

		int imageWidthInTiles = resolution.x / WIDTH;
		int imageHeightInTiles = resolution.y / HEIGHT;

		int gid = 0;
		for(int row = 0; row < imageWidthInTiles  ; row++ ){
			for(int column = 0, x = row; column < imageHeightInTiles  ; column++, x++){
				sf::IntRect rect(row * WIDTH, column * HEIGHT, WIDTH, HEIGHT);
				Tile tile((row  ) + (column * 10) + 1, rect);


				m_tiles.push_back(tile);
				auto texCoords = tile.getTexcoords();
				m_vertices.push_back(texCoords[0]);
				m_vertices.push_back(texCoords[1]);
				m_vertices.push_back(texCoords[2]);
				m_vertices.push_back(texCoords[3]);

				texCoords[0].color = sf::Color::White;
				texCoords[1].color = sf::Color::White;
				texCoords[2].color = sf::Color::White;
				texCoords[3].color = sf::Color::White;

				m_tileLinesVertices.push_back(texCoords[0]);
				m_tileLinesVertices.push_back(texCoords[1]);
				m_tileLinesVertices.push_back(texCoords[2]);
				m_tileLinesVertices.push_back(texCoords[3]);			}
		}

	}

	~TilePanelImpl(){}

	void update(sf::Vector2i mousePos){
		for(Tile tile : m_tiles){
			if(tile.m_rect.contains(mousePos)){
				std::cout << "im slected: " << tile.getGid() << std::endl;
				break;
			}
		}

	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		states.texture = &m_texture;
		rt.draw(&m_vertices[0], static_cast<unsigned int>(m_vertices.size()), sf::Quads, states);

		rt.draw(&m_vertices[0], static_cast<unsigned int>(m_vertices.size()), sf::LinesStrip);
	//	rt.draw(sprite, states);
	}

};


TilePanel::TilePanel(std::string imageFilePath) : m_impl(new TilePanelImpl(imageFilePath)) {
}

TilePanel::~TilePanel() {
}

void TilePanel::update(sf::Vector2i mousePos) {
	m_impl->update(mousePos);
}

void TilePanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}
