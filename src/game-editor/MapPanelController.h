#ifndef SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_
#define SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <game-editor/MapPanel.h>


class MapPanelController :  public sf::Drawable {
public:
	MapPanelController(sfg::Canvas::Ptr canvas, sfg::Scrollbar::Ptr xScrollbar, sfg::Scrollbar::Ptr yScrollbar, std::unique_ptr<MapPanel> mapPanel);
	~MapPanelController();

	void addTile(std::vector<sf::Event>& events, sf::Vector2i mousePos, Tile tile);
	void draw();
	void updateCanvasView();
	sf::Vector2i getSliderOffset();
private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;


	class MapPanelControllerImpl;
	std::unique_ptr<MapPanelControllerImpl> m_impl;
};

#endif /* SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_ */
