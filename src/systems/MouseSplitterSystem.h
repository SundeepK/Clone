#ifndef MOUSESPLITTERSYSTEM_H_
#define MOUSESPLITTERSYSTEM_H_

#include <anax/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <input-events/B2dSplitter.h>


class MouseSplitterSystem : public anax::System<MouseSplitterSystem>, public sf::Drawable{

public:
	MouseSplitterSystem(B2dSplitter& wb2dSplitter, sf::RenderWindow& renderWindow);
	~MouseSplitterSystem();

	void processMouseEventsForSplitter(std::vector<sf::Event>& events);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	class MouseSplitterSystemImpl;
	std::unique_ptr<MouseSplitterSystemImpl> m_impl;


};

#endif /* MOUSESPLITTERSYSTEM_H_ */
