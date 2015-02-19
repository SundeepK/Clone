#include <game-editor/TilePanel.h>
#include <iostream>
#include <game-editor/TileMap.h>


class TilePanel::TilePanelImpl{
public:

	std::unique_ptr<sf::Texture> m_texture;
	int m_currentlySelectedTile;
	TileMap m_tileMap;
	sfg::Canvas::Ptr m_textureCanvas;


	TilePanelImpl(sf::Texture& texture, sf::Vector2i tilePanelSize, sf::Vector2i tileSize) : m_texture(&texture), m_currentlySelectedTile(0),
			m_tileMap(sf::Vector2i(texture.getSize().x / tileSize.x,  texture.getSize().y / tileSize.y), tileSize){

		m_textureCanvas = sfg::Canvas::Create();
		m_textureCanvas->SetRequisition(sf::Vector2f((tilePanelSize.x),  texture.getSize().y));


	}

	~TilePanelImpl(){}

	void selectTileAt(sf::Vector2i mousePos) {
		auto tile = m_tileMap.getTile(mousePos);
		if(tile){
			m_currentlySelectedTile = tile.get().m_gid;
		}
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		states.texture = m_texture.get();
		m_tileMap.draw(rt, states, true);

		auto tile = m_tileMap.getTile(m_currentlySelectedTile);
		if (tile) {
			std::vector<sf::Vertex> selectedTileVertexArray = tile.get().getSelectedTexcoords();
			rt.draw(&selectedTileVertexArray[0], 4, sf::Quads);
		}
	}

	Tile getCurrentlySelectedTile() {
		auto tileOption = m_tileMap.getTile(m_currentlySelectedTile);
		if(tileOption){
			Tile tile = tileOption.get();
			return tile;
		}
		return Tile();
	}

	void attachTo(sfg::Box::Ptr box){
		box->Pack(m_textureCanvas, true, false);
	}

	void beginDraw() {
		m_textureCanvas->Bind();
		m_textureCanvas->Clear(sf::Color(50, 50, 50));
	}

	void draw(const sf::Drawable& drawable) {
		m_textureCanvas->Draw(drawable);
	}

	void endDraw() {
		m_textureCanvas->Display();
		m_textureCanvas->Unbind();
	}

	sf::Vector2i getCanvasMousePositionFrom(sf::Vector2i renderWindowMousePos) {
		auto absolutePosition = m_textureCanvas->GetAbsolutePosition();
		sf::Vector2i mousePos = renderWindowMousePos - sf::Vector2i(absolutePosition.x, absolutePosition.y);
		return mousePos;
	}



};


TilePanel::TilePanel(sf::Texture& texture, sf::Vector2i tilePanelSize, sf::Vector2i tileSize) : m_impl(new TilePanelImpl(texture, tilePanelSize, tileSize)) {
}

TilePanel::~TilePanel() {
}

void TilePanel::selectTileAt(sf::Vector2i mousePos) {
	 m_impl->selectTileAt(mousePos);
}

void TilePanel::beginDraw() {
	m_impl->beginDraw();
	m_impl->draw(*this);
}

void TilePanel::draw(const sf::Drawable& drawable) {
	m_impl->draw(drawable);
}

void TilePanel::endDraw() {
	m_impl->endDraw();
}

void TilePanel::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

Tile TilePanel::getCurrentlySelectedTile() {
	return m_impl->getCurrentlySelectedTile();
}


void TilePanel::attachTo(sfg::Box::Ptr box){
	m_impl->attachTo(box);
}

sf::Vector2i TilePanel::getCanvasMousePositionFrom(sf::Vector2i renderWindowMousePos) {
	return m_impl->getCanvasMousePositionFrom(renderWindowMousePos);
}
