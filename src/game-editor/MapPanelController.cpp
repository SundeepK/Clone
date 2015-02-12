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

	MapPanelControllerImpl(sfg::Canvas::Ptr canvas, sfg::Scrollbar::Ptr xScrollbar, sfg::Scrollbar::Ptr yScrollbar, std::unique_ptr<MapPanel> mapPanel) :
		m_mapPanel(std::move(mapPanel)), m_canvas(canvas), m_xScrollbar(xScrollbar), m_yScrollbar(yScrollbar){

		m_yScrollbar->SetRequisition( sf::Vector2f( 0.f, 80.f ) );
		m_yAdjustment = m_yScrollbar->GetAdjustment();

		m_xScrollbar->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
		m_xAdjustment = m_xScrollbar->GetAdjustment();
		sf::Vector2i mapSizeInTiles = m_mapPanel->getMapSizeInTiles();
		sf::Vector2i tileSize = m_mapPanel->getTileSize();


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

	void addTile(std::vector<sf::Event>& events, sf::Vector2i mousePos, Tile tile) {
		for (auto event : events) {
			if (event.type == sf::Event::MouseButtonReleased) {
				if (isUsingSlider && event.mouseButton.button == sf::Mouse::Left) {
					isUsingSlider = false;
				}
			}
		}

		if (!isUsingSlider && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2f absolutePositionForMapCanvas = m_canvas->GetAbsolutePosition();
			sf::Vector2i tileMapPos = mousePos - sf::Vector2i(absolutePositionForMapCanvas.x, absolutePositionForMapCanvas.y);
			sf::Vector2i positionWithScrollbarDelta = tileMapPos + m_prevSliderValue;
			m_mapPanel->addTile(positionWithScrollbarDelta, tile);
		}

		if(isUsingSlider ){
			m_mapPanel->updateCenterMapView(m_center);
		}
	}


	void sliderAdjusted() {
		m_viewDeltaFromSlider = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue()) - m_prevSliderValue;
		m_prevSliderValue = sf::Vector2i(m_xAdjustment->GetValue(), m_yAdjustment->GetValue());
	}

	void sliderPressed() {
		isUsingSlider = true;
	}

	void draw(){
		m_canvas->Draw(*m_mapPanel);
	}


};


MapPanelController::~MapPanelController() {
}

MapPanelController::MapPanelController(sfg::Canvas::Ptr canvas, sfg::Scrollbar::Ptr xScrollbar, sfg::Scrollbar::Ptr yScrollbar, std::unique_ptr<MapPanel> mapPanel) :
		m_impl(new MapPanelControllerImpl(canvas, xScrollbar, yScrollbar, std::move(mapPanel))){
}

void MapPanelController::addTile(std::vector<sf::Event>& events, sf::Vector2i mousePos, Tile tile)  {
	m_impl->addTile(events, mousePos, tile);
}

void MapPanelController::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
}

void MapPanelController::draw(){
	m_impl->draw();
}
