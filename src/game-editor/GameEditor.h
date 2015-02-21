#ifndef SRC_GAME_EDITOR_GAMEEDITOR_H_
#define SRC_GAME_EDITOR_GAMEEDITOR_H_

#include <memory.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <vector>


class GameEditor {
public:
	GameEditor(sf::RenderWindow& mainRenderWindow, sf::Vector2f mapSizeInPixels, sf::Texture& texture, sf::Vector2i tileSize);
	~GameEditor();

	void update();

private:

	class GameEditorImpl;
	std::unique_ptr<GameEditorImpl> m_impl;

};

#endif /* SRC_GAME_EDITOR_GAMEEDITOR_H_ */
