#include "B2dSplitter.h"
#include <splitter/TextureMapper.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <vector>
#include <set>
#include <algorithm>
#include <opengl/TextureLoader.h>

class B2dSplitter::B2dSplitterImpl{

public:

	B2dSplitterImpl(b2World& box2dWorld,  anax::World& anaxWorld) : m_sliceLine(sf::Lines, 2), m_world(&box2dWorld), m_anaxWorld(&anaxWorld), m_textureMapper(Box2DConstants::WORLD_SCALE){
	}

	~B2dSplitterImpl(){
	}

    bool isleftPressed = false;
    sf::VertexArray m_sliceLine;
    Splitter m_splitter;
    std::unique_ptr<b2World> m_world;
    std::unique_ptr<anax::World> m_anaxWorld;
    TextureMapper m_textureMapper;
    TextureLoader m_textureLoader;

	std::set<anax::Entity, CompareEntities> m_entitiesToKill;
	std::set<b2Body*> m_bodiesToKill;

	void deleteEntities() {
		for(b2Body * body : m_bodiesToKill){
			m_world->DestroyBody(body);
		}

		for (auto entity : m_entitiesToKill) {
			entity.kill();
		}

		m_bodiesToKill.clear();
		m_entitiesToKill.clear();
	}

	void processLeftMousePressed(const sf::Event& event,  sf::Vector2f cameraPos){
	    if(isleftPressed) {
	          m_sliceLine[1].position = (sf::Vector2f(event.mouseMove.x + cameraPos.x, event.mouseMove.y + cameraPos.y));
	          m_sliceLine[1].color =     sf::Color::Red;
	      }

	    if (event.type == sf::Event::MouseButtonPressed) {
	        if (event.mouseButton.button == sf::Mouse::Left) {
	        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y +cameraPos.y);
	            m_sliceLine[0].position = (mousePos);
	            m_sliceLine[0].color =     sf::Color::Red;
	            m_sliceLine[1].position = (mousePos);
	            m_sliceLine[1].color =     sf::Color::Red;
	            isleftPressed = true;
	        }
	    }
	}

	void processLeftMouseReleased(const sf::Event& event,  sf::Vector2f cameraPos){
	    if (event.type == sf::Event::MouseButtonReleased) {
	        if (event.mouseButton.button == sf::Mouse::Left) {
	        	m_splitter.clearIntersects();
	        	sf::Vector2f mousePos(event.mouseButton.x + cameraPos.x, event.mouseButton.y + cameraPos.y);
	            m_sliceLine[1].position = (mousePos);
	            m_sliceLine[1].color =     sf::Color::Red;
	            isleftPressed = false;
	            if( !(m_sliceLine[0].position == m_sliceLine[1].position)) {
	            	performRayCastForSplitter();
	            }
	            deleteEntities();
	        }
	    }
	}


	void performRayCastForSplitter(){
		Vec startLine = m_sliceLine[0].position;
		Vec endLine = m_sliceLine[1].position;
		b2Vec2 s =  startLine.pixToM().toB2v();
		b2Vec2 e = endLine.pixToM().toB2v();
		m_world->RayCast(&m_splitter,s, e);
		m_world->RayCast(&m_splitter,e, s);
	}


	void performBox2dSplit(const sf::Event& event,  sf::Vector2f cameraPos){
	    processLeftMousePressed(event, cameraPos);
	    processLeftMouseReleased(event, cameraPos);
	}

	void processMouseEventsForSplitter(sf::RenderWindow& App, sf::Vector2f cameraPos) {
	    sf::Event event;
	    while( App.pollEvent(event)) {
	        if(event.type == sf::Event::Closed){
	                    App.close();
	        }
	        sf::Vector2f gg(App.getViewport(App.getView()).left, App.getViewport(App.getView()).top);
	        performBox2dSplit(event,cameraPos);
	    }
	}

	void  createNewSplitBodies(B2BoxBuilder& builder,b2Body* body, anax::Entity& entity){
		Texcoords oldTexCoords = entity.getComponent<Texcoords>();
		m_bodiesToKill.insert(body);
		m_entitiesToKill.insert(entity);

	    b2Body* newSplitBody = builder.build(*m_world);
		auto objectEntity = m_anaxWorld->createEntity();
	    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
	    auto& physComp = objectEntity.addComponent<PhysicsComponent>();

	    physComp.physicsBody = newSplitBody;

	    texCoordsComp.textCoords = m_textureMapper.mapSplitBody(newSplitBody, body,oldTexCoords.textCoords);
	    texCoordsComp.image = oldTexCoords.image;

	    texCoordsComp.texture = TextureLoader::loadAsOpenglTexture(texCoordsComp.texture, texCoordsComp.image);

	    objectEntity.activate();
	}

	void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies,b2Body* body, std::vector<anax::Entity> entities) {
		if (body->GetMass() < 0.1f) return;
		for (auto builder : splitBodies) {
			for (auto entity : entities) {
				if (entity.getComponent<PhysicsComponent>().physicsBody == body) {
					createNewSplitBodies(builder, body, entity);
					break;
				}
			}
		}
	}

	void draw(sf::RenderTarget& rt, sf::RenderStates states) const {
		rt.draw(m_sliceLine);
	}

};

B2dSplitter::B2dSplitter(b2World& box2dWorld,  anax::World& anaxWorld) : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()),
		m_impl(new B2dSplitterImpl(box2dWorld, anaxWorld)){
	m_impl->m_splitter.registerBodySplitCallback(this);
}

B2dSplitter::~B2dSplitter() {
}

void B2dSplitter::processMouseEventsForSplitter(sf::RenderWindow& App, sf::Vector2f cameraPos) {
	m_impl->processMouseEventsForSplitter(App, cameraPos);
}

void B2dSplitter::onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body) {
	auto entities = getEntities();
	m_impl->onb2BodySplit(splitBodies, body, entities);
}

void B2dSplitter::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	m_impl->draw(rt, states);
}
