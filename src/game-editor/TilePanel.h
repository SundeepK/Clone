#ifndef SRC_GAME_EDITOR_TILEPANEL_H_
#define SRC_GAME_EDITOR_TILEPANEL_H_

#include <anax/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>

class TilePanel : public sf::Drawable {
public:
	TilePanel(std::string imageFilePath);
	~TilePanel();

	bool update(sf::Vector2i mousePos);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    class TilePanelImpl;
    std::unique_ptr<TilePanelImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_TILEPANEL_H_ */
