#ifndef MOUSEEVENTPROCESSOR_H_
#define MOUSEEVENTPROCESSOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <splitter/Splitter.h>
#include <anax/anax.hpp>
#include <Box2D/Box2D.h>
#include <memory.h>


struct CompareEntities
{
    bool operator() (const anax::Entity& lhs, const anax::Entity& rhs) const{
        return lhs.getId() < rhs.getId();
    }
};

class B2dSplitter : public B2BodySplitCallback,  public anax::System<B2dSplitter>, public sf::Drawable{
public:
	B2dSplitter(b2World& box2dWorld, anax::World& anaxWorld);
	~B2dSplitter();

	void processMouseEventsForSplitter(sf::RenderWindow& App, sf::Vector2f cameraPos);
    void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body);

private:

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    class B2dSplitterImpl;
    std::unique_ptr<B2dSplitterImpl> m_impl;

};

#endif /* MOUSEEVENTPROCESSOR_H_ */
