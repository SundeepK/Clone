#include "Bd2Splitter.h"

Bd2Splitter::Bd2Splitter(b2World& box2dWorld,  anax::World& anaxWorld) : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()), sliceLine(sf::Lines, 2), m_world(&box2dWorld), m_anaxWorld(&anaxWorld), m_textureMapper(Box2DConstants::WORLD_SCALE){
	m_splitter.registerBodySplitCallback(this);
}

Bd2Splitter::~Bd2Splitter() {
}

void Bd2Splitter::processMouseEventsForSplitter(sf::RenderWindow& App) {
    sf::Event event;
    while( App.pollEvent(event)) {

        if(event.type == sf::Event::Closed){
                    App.close();
        }

        if(isleftPressed) {
            sliceLine[1].position = (sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            sliceLine[1].color =     sf::Color::Red;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sliceLine[0].position = (sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                sliceLine[0].color =     sf::Color::Red;
                sliceLine[1].position = (sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                sliceLine[1].color =     sf::Color::Red;

                isleftPressed = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
            	m_splitter.clearIntersects();
                sliceLine[1].position = (sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                sliceLine[1].color =     sf::Color::Red;
                isleftPressed = false;
                if( !(sliceLine[0].position == sliceLine[1].position)) {
                	Vec startLine ( sliceLine[0].position);
                	Vec endLine = sliceLine[1].position;
                	b2Vec2 s =  startLine.pixToM().toB2v();
                	b2Vec2 e = endLine.pixToM().toB2v();
                	m_world->RayCast(&m_splitter,s, e);
                	m_world->RayCast(&m_splitter,e, s);
                }

            }
        }
    }

}

void Bd2Splitter::onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies,b2Body* body) {
	auto entities = getEntities();
	 // if(body->GetMass() < 0.1f) return;

	        for(auto builder : splitBodies) {

	        	Texcoords oldTexCoords;
	        	for (auto entity : entities) {
	        		auto& physicsComp = entity.getComponent<PhysicsComponent>();
	        		if(physicsComp.physicsBody == body){
	        			oldTexCoords = entity.getComponent<Texcoords>();

	        			if(std::find_if(m_bodiesToDelete.begin(), m_bodiesToDelete.end(), [&body](const b2Body* bodyToCompare){ return bodyToCompare == body; }) == m_bodiesToDelete.end() ){
	        				m_bodiesToDelete.push_back(body);
	        			}

	        			if(std::find_if(m_entitiesToDelete.begin(), m_entitiesToDelete.end(), [&entity](const anax::Entity entityToCompare){ return entityToCompare == entity; }) == m_entitiesToDelete.end()){
		        	        m_entitiesToDelete.push_back(entity);
	        			}


	    	            b2Body* newB = builder.build(*m_world);
	    				auto objectEntity = m_anaxWorld->createEntity();
	    			    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
	    			    auto& physComp = objectEntity.addComponent<PhysicsComponent>();

	    			    physComp.physicsBody = newB;

	    	            std::vector<b2Vec2> newBOdyTexCoords =  m_textureMapper.mapSplitBody(newB, body,oldTexCoords.textCoords);
	    	            texCoordsComp.textCoords = newBOdyTexCoords;
	    	            texCoordsComp.image = oldTexCoords.image;
	    	            objectEntity.activate();

	        			break;
	        		}
	        	}
	        }

	        //m_world->DestroyBody(body);
//        	for (auto entity : entities) {
//        		auto& physicsComp = entity.getComponent<PhysicsComponent>();
//        		if(physicsComp.physicsBody == body){
//        			entity.deactivate();
//        			break;
//        		}
//        	}
}

void Bd2Splitter::deleteEntities() {

	for(b2Body * body : m_bodiesToDelete){
		m_world->DestroyBody(body);
	}

	for (auto entity : m_entitiesToDelete) {
		//entity.removeAllComponents();
		entity.kill();
	}

	m_bodiesToDelete.clear();
	m_entitiesToDelete.clear();


}

void Bd2Splitter::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.draw(sliceLine);
}
