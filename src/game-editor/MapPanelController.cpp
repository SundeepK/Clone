#include <game-editor/MapPanelController.h>
#include <iostream>

class MapPanelController::MapPanelControllerImpl{

public:
	std::unique_ptr<MapPanel> m_mapPanel;
	sfg::Canvas::Ptr m_canvas;
	sfg::Scrollbar::Ptr m_xScrollbar;
	sfg::Scrollbar::Ptr m_yScrollbar;
	sfg::Adjustment::Ptr m_yAdjustment;
	sfg::Adjustment::Ptr m_xAdjustment;
	bool isUsingSlider = false;
	sf::Vector2i m_viewDeltaFromSlider;
	sf::Vector2i m_prevSliderValue;
	sf::Vector2f m_center;
	sf::IntRect m_bounds;
	sf::RectangleShape m_rectangle;
	const int POSITION_OFFSET = 6;
	const int PADDING = 12;

	MapPanelControllerImpl(sfg::Canvas::Ptr canvas, sfg::Scrollbar::Ptr xScrollbar, sfg::Scrollbar::Ptr yScrollbar, std::unique_ptr<MapPanel> mapPanel) :
		m_mapPanel(std::move(mapPanel)), m_canvas(canvas), m_xScrollbar(xScrollbar), m_yScrollbar(yScrollbar){

		m_yScrollbar->SetRequisition( sf::Vector2f( 0.f, 80.f ) );
		m_yAdjustment = m_yScrollbar->GetAdjustment();

		m_xScrollbar->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
		m_xAdjustment = m_xScrollbar->GetAdjustment();
		sf::Vector2i mapSizeInTiles = m_mapPanel->getMapSizeInTiles();
		sf::Vector2i tileSize = m_mapPanel->getTileSize();

		m_bounds.left = POSITION_OFFSET;
		m_bounds.top = POSITION_OFFSET;
		m_bounds.width = m_mapPanel->getMapSizeInPixels().x - PADDING;
		m_bounds.height = m_mapPanel->getMapSizeInPixels().y - PADDING;

		m_rectangle.setFillColor(sf::Color::Transparent);
		m_rectangle.setOutlineColor(sf::Color::Red);
		m_rectangle.setOutlineThickness(2.f);
		m_rectangle.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
		m_rectangle.setSize(sf::Vector2f(m_bounds.width, m_bounds.height));

		m_xAdjustment->SetLower(0 );
		m_xAdjustment->SetUpper( (mapSizeInTiles.x * tileSize.x ) - (m_mapPanel->getMapSizeInPixels().x / 2));
		m_xAdjustment->SetMinorStep( 10.f );
		m_xAdjustment->SetMajorStep( 20 );
		m_xAdjustment->SetPageSize( 10 );

		m_yAdjustment->SetLower( 0 );
		m_yAdjustment->SetUpper( (mapSizeInTiles.y * tileSize.y ) - (m_mapPanel->getMapSizeInPixels().y / 2) );
		m_yAdjustment->SetMinorStep( 10.f );
		m_yAdjustment->SetMajorStep( 20 );
		m_yAdjustment->SetPageSize( 10 );

		m_xScrollbar->GetSignal( sfg::Scrollbar::OnMouseLeftPress).Connect( std::bind( &MapPanelControllerImpl::sliderPressed, this ) );
		m_yScrollbar->GetSignal( sfg::Scrollbar::OnMouseLeftPress).Connect( std::bind( &MapPanelControllerImpl::sliderPressed, this ) );

		m_xAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect([this]() {
			this->sliderAdjusted();
			m_center = sf::Vector2f(( m_mapPanel->getMapSizeInPixels().x /2 ) + m_xAdjustment->GetValue(), m_mapPanel->getView().getCenter().y);
		});

		m_yAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect([this]() {
			this->sliderAdjusted();
			m_center = sf::Vector2f( m_mapPanel->getView().getCenter().x, ( m_mapPanel->getMapSizeInPixels().y /2 ) + m_yAdjustment->GetValue());
		});

	}

	~MapPanelControllerImpl(){}

	void handleEvents(std::vector<sf::Event>& events){
		for (auto event : events) {
			if (event.type == sf::Event::MouseButtonReleased) {
				if (isUsingSlider && event.mouseButton.button == sf::Mouse::Left) {
					isUsingSlider = false;
				}
			}
		}
	}

	void addTile(sf::Vector2i mousePos, Tile tile) {
		if (!isUsingSlider && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f absolutePositionForMapCanvas = m_canvas->GetAbsolutePosition();
			sf::Vector2i tileMapPos = mousePos - sf::Vector2i(absolutePositionForMapCanvas.x, absolutePositionForMapCanvas.y);
				sf::Vector2i positionWithScrollbarDelta = tileMapPos + m_prevSliderValue;
			if(isInBounds(positionWithScrollbarDelta)){
				m_mapPanel->addTile(positionWithScrollbarDelta, tile);
			}
		}
	}


	void sliderAdjusted() {
		m_viewDeltaFromSlider = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue()) - m_prevSliderValue;
		m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());
		auto boundsPosition = sf::Vector2f(m_prevSliderValue) + sf::Vector2f(POSITION_OFFSET, POSITION_OFFSET);
		m_bounds.left = boundsPosition.x;
		m_bounds.top = boundsPosition.y;
	}

	void sliderPressed() {
		isUsingSlider = true;
	}

	void draw(){
		m_canvas->Draw(*m_mapPanel);
		m_rectangle.setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
		m_canvas->Draw(m_rectangle);
	}

	void updateCanvasView(){
		if(isUsingSlider ){
			m_mapPanel->updateCenterMapView(m_center);
		}
	}

	sf::Vector2i getSliderOffset(){
		return m_prevSliderValue;
	}

	bool isSliderInUse(){
		return isUsingSlider;
	}

	bool isInBounds(sf::Vector2i mousePos){
		return m_bounds.contains(mousePos);
	}

};


MapPanelController::~MapPanelController() {
}

MapPanelController::MapPanelController(sfg::Canvas::Ptr canvas, sfg::Scrollbar::Ptr xScrollbar, sfg::Scrollbar::Ptr yScrollbar, std::unique_ptr<MapPanel> mapPanel) :
		m_impl(new MapPanelControllerImpl(canvas, xScrollbar, yScrollbar, std::move(mapPanel))){
}

void MapPanelController::addTile(sf::Vector2i mousePos, Tile tile)  {
	m_impl->addTile(mousePos, tile);
}

bool MapPanelController::isSliderInUse() {
	return m_impl->isSliderInUse();
}

bool MapPanelController::isInBounds(sf::Vector2i mousePos) {
	return m_impl->isInBounds(mousePos);
}

void MapPanelController::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
}

void MapPanelController::draw(){
	m_impl->draw();
}

void MapPanelController::updateCanvasView() {
	m_impl->updateCanvasView();
}

sf::Vector2i MapPanelController::getSliderOffset() {
	return m_impl->getSliderOffset();
}

void MapPanelController::handleEvents(std::vector<sf::Event>& events) {
	m_impl->handleEvents(events);
}
