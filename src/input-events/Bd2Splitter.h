#ifndef MOUSEEVENTPROCESSOR_H_
#define MOUSEEVENTPROCESSOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <splitter/Splitter.h>
#include <splitter/TextureMapper.h>
#include <Box2D/Box2D.h>
#include <memory.h>
#include <anax/anax.hpp>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <vector>
#include <algorithm>

class Bd2Splitter : public B2BodySplitCallback,  public anax::System<Bd2Splitter>, public sf::Drawable{
public:
	Bd2Splitter(b2World& box2dWorld, anax::World& anaxWorld);
	virtual ~Bd2Splitter();

	void processMouseEventsForSplitter(sf::RenderWindow& App);
    void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body);
    void deleteEntities();

private:
    bool isleftPressed = false;
    sf::VertexArray sliceLine;
    Splitter m_splitter;
    std::unique_ptr<b2World> m_world;
    std::unique_ptr<anax::World> m_anaxWorld;
    TextureMapper m_textureMapper;
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	std::vector<b2Body*> m_bodiesToDelete;
	std::vector<anax::Entity> m_entitiesToDelete;
};

#endif /* MOUSEEVENTPROCESSOR_H_ */
