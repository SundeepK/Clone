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
#include <set>
#include <algorithm>
#include <opengl/TextureLoader.h>

struct CompareEntities
{
    bool operator() (const anax::Entity& lhs, const anax::Entity& rhs) const{
        return lhs.getId() < rhs.getId();
    }
};

class Bd2Splitter : public B2BodySplitCallback,  public anax::System<Bd2Splitter>, public sf::Drawable{
public:
	Bd2Splitter(b2World& box2dWorld, anax::World& anaxWorld);
	virtual ~Bd2Splitter();

	void processMouseEventsForSplitter(sf::RenderWindow& App, sf::Vector2f cameraPos);
    void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body);

private:

    void createNewSplitBodies(B2BoxBuilder& builder,b2Body* body, anax::Entity& entity);
    void performBox2dSplit(const sf::Event& event,  sf::Vector2f cameraPos);
    void performRayCastForSplitter();
    void processLeftMousePressed(const sf::Event& event,  sf::Vector2f cameraPos);
    void processLeftMouseReleased(const sf::Event& event,  sf::Vector2f cameraPos);
    void deleteEntities();
	void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

    bool isleftPressed = false;
    sf::VertexArray m_sliceLine;
    Splitter m_splitter;
    std::unique_ptr<b2World> m_world;
    std::unique_ptr<anax::World> m_anaxWorld;
    TextureMapper m_textureMapper;
    TextureLoader m_textureLoader;

	std::set<anax::Entity, CompareEntities> m_entitiesToKill;
	std::set<b2Body*> m_bodiesToKill;

};

#endif /* MOUSEEVENTPROCESSOR_H_ */
