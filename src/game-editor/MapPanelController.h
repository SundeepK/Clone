#ifndef SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_
#define SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <game-editor/MapPanel.h>
#include <game-editor/ScrollableCanvas.h>

class MapPanelController : public sf::Drawable{
public:
	MapPanelController(ScrollableCanvas& canvas, std::unique_ptr<MapPanel> mapPanel);
	~MapPanelController();

	void addTile(sf::Vector2i mousePos, Tile tile);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class MapPanelControllerImpl;
	std::unique_ptr<MapPanelControllerImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_MAPPANELCONTROLLER_H_ */
