#include <game-editor/ScrollableCanvas.h>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class ScrollableCanvas::ScrollableCanvasImpl{

public:
	sfg::Scrollbar::Ptr m_xScrollbar;
	sfg::Scrollbar::Ptr m_yScrollbar;
	sfg::Adjustment::Ptr m_yAdjustment;
	sfg::Adjustment::Ptr m_xAdjustment;
	sfg::Canvas::Ptr m_mapCanvas;
	sfg::Table::Ptr m_table;
	MapData m_mapData;
	sf::IntRect m_bounds;
	sf::RectangleShape m_rectangle;
	const int POSITION_OFFSET = 6;
	const int PADDING = 12;
	sf::View m_view;
	sf::Vector2f m_center;
	sf::Vector2i m_prevSliderValue;
	bool m_isUsingSlider = false;



	ScrollableCanvasImpl(MapData mapData) : m_mapData(mapData),
		m_view(sf::Vector2f(m_mapData.getMapSizeInPixels().x / 2, m_mapData.getMapSizeInPixels().y / 2) , sf::Vector2f(m_mapData.getMapSizeInPixels())) {

		m_mapCanvas = sfg::Canvas::Create();
		m_mapCanvas->SetRequisition(sf::Vector2f(mapData.getMapSizeInPixels()));
		m_table = sfg::Table::Create();

		m_yScrollbar = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );
		m_xScrollbar = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::HORIZONTAL );

		m_yScrollbar->SetRequisition(sf::Vector2f(0.f, 80.f));
		m_yAdjustment = m_yScrollbar->GetAdjustment();

		m_xScrollbar->SetRequisition(sf::Vector2f(80.f, 0.f));
		m_xAdjustment = m_xScrollbar->GetAdjustment();
		auto mapSizeInTiles = m_mapData.getMapSizeInTiles();
		auto tileSize = m_mapData.getTileSize();
		auto mapSizeInPixels = m_mapData.getMapSizeInPixels();

		m_bounds.left = POSITION_OFFSET;
		m_bounds.top = POSITION_OFFSET;
		m_bounds.width = mapSizeInPixels.x - PADDING;
		m_bounds.height = mapSizeInPixels.y - PADDING;

		m_rectangle.setFillColor(sf::Color::Transparent);
		m_rectangle.setOutlineColor(sf::Color::Red);
		m_rectangle.setOutlineThickness(2.f);
		m_rectangle.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
		m_rectangle.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));

		m_xAdjustment->SetLower(0);
		m_xAdjustment->SetUpper((mapSizeInTiles.x * tileSize.x) - (mapSizeInPixels.x / 2));
		m_xAdjustment->SetMinorStep(10.f);
		m_xAdjustment->SetMajorStep(20);
		m_xAdjustment->SetPageSize(10);

		m_yAdjustment->SetLower(0);
		m_yAdjustment->SetUpper((mapSizeInTiles.y * tileSize.y) - (mapSizeInPixels.y / 2));
		m_yAdjustment->SetMinorStep(10.f);
		m_yAdjustment->SetMajorStep(20);
		m_yAdjustment->SetPageSize(10);

		m_xScrollbar->GetSignal(sfg::Scrollbar::OnMouseLeftPress).Connect(std::bind(&ScrollableCanvasImpl::sliderPressed, this));
		m_yScrollbar->GetSignal(sfg::Scrollbar::OnMouseLeftPress).Connect(std::bind(&ScrollableCanvasImpl::sliderPressed, this));

		std::cout << "m_center center x:" << m_center.x << " y: " << m_center.y << std::endl;


		m_xAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect([this, mapSizeInPixels]() {
			this->sliderAdjusted();
			m_center = sf::Vector2f(( mapSizeInPixels.x /2 ) + m_xAdjustment->GetValue(), m_view.getCenter().y);
		});

		m_yAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect([this, mapSizeInPixels]() {
			this->sliderAdjusted();
			m_center = sf::Vector2f( m_view.getCenter().x, ( mapSizeInPixels.y /2 ) + m_yAdjustment->GetValue());
		});

		m_table->Attach( m_mapCanvas, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL | sfg::Table::EXPAND );
		m_table->Attach( m_yScrollbar, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), 0, sfg::Table::FILL);
		m_table->Attach( m_xScrollbar, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL, 0  );

	}

	~ScrollableCanvasImpl(){

	}

	void update(std::vector<sf::Event>& events){
		for (auto event : events) {
			if (event.type == sf::Event::MouseButtonReleased) {
				if (m_isUsingSlider && event.mouseButton.button == sf::Mouse::Left) {
					m_isUsingSlider = false;
				}
			}
		}

		updateCanvasView();
		m_rectangle.setPosition(m_bounds.left, m_bounds.top);
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.setView(m_view);
		rt.draw(m_rectangle);
	}

	void sliderAdjusted() {
		m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());
		auto boundsPosition = sf::Vector2f(m_prevSliderValue) + sf::Vector2f(POSITION_OFFSET, POSITION_OFFSET);
		m_bounds.left = boundsPosition.x;
		m_bounds.top = boundsPosition.y;
	}

	void sliderPressed() {
		m_isUsingSlider = true;
	}

	void updateCanvasView(){
		if(m_isUsingSlider){
			std::cout << "setting center x:" << m_center.x << " y: " << m_center.y << std::endl;
			m_view.setCenter(m_center);
		}
	}

	bool isInBounds(sf::Vector2i renderWindowMousePos){
		auto canvasPos = getCanvasMousePositionFrom(renderWindowMousePos);
		return m_bounds.contains(canvasPos);
	}

	sf::Vector2i getCanvasMousePositionFrom(sf::Vector2i mousePos){
		auto absolutePositionForMapCanvas = m_mapCanvas->GetAbsolutePosition();
		auto tileMapPos = mousePos - sf::Vector2i(absolutePositionForMapCanvas.x, absolutePositionForMapCanvas.y);
		sf::Vector2i positionWithScrollbarDelta = tileMapPos + m_prevSliderValue;
		return positionWithScrollbarDelta;
	}

	void attachTo(sfg::Box::Ptr box) {
		box->Pack(m_table, true);
	}

	sfg::Canvas::Ptr getCanvas() {
		return m_mapCanvas;
	}

	void beginDraw() {
		m_mapCanvas->Bind();
		m_mapCanvas->Clear(sf::Color(50, 50, 50));
	}

	void draw(const sf::Drawable& drawable) {
		m_mapCanvas->Draw(drawable);
	}

	void endDraw() {
		m_mapCanvas->Display();
		m_mapCanvas->Unbind();
	}

};


ScrollableCanvas::ScrollableCanvas(MapData mapData) :
	m_impl(new ScrollableCanvasImpl(mapData)){
}

ScrollableCanvas::~ScrollableCanvas() {
}

sf::Vector2i ScrollableCanvas::getCanvasMousePositionFrom(sf::Vector2i renderWindowMousePos) {
	return m_impl->getCanvasMousePositionFrom(renderWindowMousePos);
}

bool ScrollableCanvas::isInCanvasBounds(sf::Vector2i renderWindowMousePos) {
	return m_impl->isInBounds(renderWindowMousePos);
}

bool ScrollableCanvas::isInBoundsAndSlidersNotInUse(sf::Vector2i renderWindowMousePos) {
	return m_impl->isInBounds(renderWindowMousePos) && !m_impl->m_isUsingSlider;
}

void ScrollableCanvas::updateCanvas(std::vector<sf::Event>& events) {
	m_impl->update(events);
}


void ScrollableCanvas::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}

void ScrollableCanvas::attachTo(sfg::Box::Ptr box) {
	m_impl->attachTo(box);
}

sfg::Canvas::Ptr ScrollableCanvas::getCanvas() {
	return m_impl->getCanvas();
}

void ScrollableCanvas::beginDraw() {
	m_impl->beginDraw();
	m_impl->draw(*this);

}

void ScrollableCanvas::draw(const sf::Drawable& drawable) {
	m_impl->draw(drawable);
}

void ScrollableCanvas::endDraw() {
	m_impl->endDraw();
}
