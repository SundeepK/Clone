#include "Bd2Splitter.h"

Bd2Splitter::Bd2Splitter(b2World& box2dWorld,  anax::World& anaxWorld) : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()), m_sliceLine(sf::Lines, 2), m_world(&box2dWorld), m_anaxWorld(&anaxWorld), m_textureMapper(Box2DConstants::WORLD_SCALE){
	m_splitter.registerBodySplitCallback(this);
}

Bd2Splitter::~Bd2Splitter() {
}


void Bd2Splitter::deleteEntities() {
	for(b2Body * body : m_bodiesToKill){
		m_world->DestroyBody(body);
	}

	for (auto entity : m_entitiesToKill) {
		entity.kill();
	}

	m_bodiesToKill.clear();
	m_entitiesToKill.clear();
}

void Bd2Splitter::processLeftMousePressed(const sf::Event& event){
    if(isleftPressed) {
          m_sliceLine[1].position = (sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
          m_sliceLine[1].color =     sf::Color::Red;
      }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
        	sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            m_sliceLine[0].position = (mousePos);
            m_sliceLine[0].color =     sf::Color::Red;
            m_sliceLine[1].position = (mousePos);
            m_sliceLine[1].color =     sf::Color::Red;
            isleftPressed = true;
        }
    }
}

void Bd2Splitter::processLeftMouseReleased(const sf::Event& event){
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
        	m_splitter.clearIntersects();
        	sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
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


void Bd2Splitter::performRayCastForSplitter(){
	Vec startLine = m_sliceLine[0].position;
	Vec endLine = m_sliceLine[1].position;
	b2Vec2 s =  startLine.pixToM().toB2v();
	b2Vec2 e = endLine.pixToM().toB2v();
	m_world->RayCast(&m_splitter,s, e);
	m_world->RayCast(&m_splitter,e, s);
}


void Bd2Splitter::performBox2dSplit(const sf::Event& event){
    processLeftMousePressed(event);
    processLeftMouseReleased(event);
}

void Bd2Splitter::processMouseEventsForSplitter(sf::RenderWindow& App) {
    sf::Event event;
    while( App.pollEvent(event)) {
        if(event.type == sf::Event::Closed){
                    App.close();
        }
        performBox2dSplit(event);
    }
}

void  Bd2Splitter::createNewSplitBodies(B2BoxBuilder& builder,b2Body* body, anax::Entity& entity){
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

  //  m_textureLoader.loadAsOpenglTexture(texCoordsComp);

	glGenTextures(1, &texCoordsComp.texture);
	glBindTexture(GL_TEXTURE_2D, texCoordsComp.texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texCoordsComp.image.getSize().x,
			texCoordsComp.image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,
			texCoordsComp.image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);

    objectEntity.activate();
}

void Bd2Splitter::onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies,b2Body* body) {
	auto entities = getEntities();
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



void Bd2Splitter::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
	rt.draw(m_sliceLine);
}
