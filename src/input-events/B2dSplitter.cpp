#include "B2dSplitter.h"
#include <splitter/TextureMapper.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <vector>
#include <set>
#include <algorithm>
#include <opengl/TextureLoader.h>
#include <components/SplitDirectionComponent.h>
#include <iostream>

class B2dSplitter::B2dSplitterImpl{

public:

	B2dSplitterImpl(b2World& box2dWorld, anax::World& anaxWorld) :  m_world(&box2dWorld), m_anaxWorld(&anaxWorld), m_textureMapper(Box2DConstants::WORLD_SCALE){
	}

	~B2dSplitterImpl(){
	}

	Splitter m_splitter;
    std::unique_ptr<anax::World> m_anaxWorld;
    TextureMapper m_textureMapper;
    TextureLoader m_textureLoader;

	std::set<anax::Entity, CompareEntities> m_entitiesToKill;
	std::set<b2Body*> m_bodiesToKill;
    std::unique_ptr<b2World> m_world;

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


	anax::Entity createSplitBodyEntityFromOldTexCoords(b2Body* newSplitBody, b2Body* body, anax::Entity oldEntityToSplit){
		auto& oldSplitDirection = oldEntityToSplit.getComponent<SplitDirectionComponent>();
		Texcoords oldBodyTexCoords = oldEntityToSplit.getComponent<Texcoords>();
		auto objectEntity = m_anaxWorld->createEntity();
	    auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
	    auto& physComp = objectEntity.addComponent<PhysicsComponent>();
	    auto& splitdirection = objectEntity.addComponent<SplitDirectionComponent>();

	    splitdirection.splitDirection = oldSplitDirection.splitDirection;
	    physComp.physicsBody = newSplitBody;

	    texCoordsComp.textCoords = m_textureMapper.mapSplitBody(newSplitBody, body,oldBodyTexCoords.textCoords);
	    texCoordsComp.image = oldBodyTexCoords.image;

	    texCoordsComp.texture = TextureLoader::loadAsOpenglTexture(texCoordsComp.texture, texCoordsComp.image);

	    objectEntity.activate();
	    return objectEntity;
	}

	void  createNewSplitBody(B2BoxBuilder& newSplitB2bodyBuilder,b2Body* oldBodyToSplit, anax::Entity& entity, std::vector<anax::Entity>& entitiesToFill){
		m_bodiesToKill.insert(oldBodyToSplit);
		m_entitiesToKill.insert(entity);
		b2Body* newSplitBody = newSplitB2bodyBuilder.build(*m_world);
		entitiesToFill.push_back(createSplitBodyEntityFromOldTexCoords(newSplitBody, oldBodyToSplit, entity));
	}

	void setBodyTypes( std::vector<anax::Entity>& entities){
		std::cout << "newlyCreatedEntities size: " << entities.size()  << std::endl;
    	assert (
    		"split bodies created is more than 2" &&
    		entities.size() < 3
    	);

		auto firstSplitEntity = entities[0];
		auto secondSplitEntity = entities[1];

		auto& firstSplitDir = firstSplitEntity.getComponent<SplitDirectionComponent>();
		auto& secondSplitDir = secondSplitEntity.getComponent<SplitDirectionComponent>();

    	assert (
    		"Split direction are not the same" &&
    		firstSplitDir.splitDirection == secondSplitDir.splitDirection
    	);

		if(firstSplitDir.splitDirection == SplitDirection::RIGHT){
			b2Body* firstBody = firstSplitEntity.getComponent<PhysicsComponent>().physicsBody;
			b2Body* secondBody = secondSplitEntity.getComponent<PhysicsComponent>().physicsBody;

			if(firstBody->GetLocalCenter().x > secondBody->GetLocalCenter().x){
				firstBody->SetType(b2_dynamicBody);
			}else{
				secondBody->SetType(b2_dynamicBody);
			}
		}
	}

	void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies,b2Body* body, std::vector<anax::Entity>& entities) {
		if (body->GetMass() < 0.1f && body->GetType() != b2_staticBody) return;
		std::vector<anax::Entity> newlyCreatedEntities;
		for (auto builder : splitBodies) {
			for (auto entity : entities) {
				if (entity.getComponent<PhysicsComponent>().physicsBody == body) {
					createNewSplitBody(builder, body, entity, newlyCreatedEntities);
					break;
				}
			}
		}
		setBodyTypes(newlyCreatedEntities);

	}

};

B2dSplitter::B2dSplitter(b2World& box2dWorld,  anax::World& anaxWorld) : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent, SplitDirectionComponent>()),
		m_impl(new B2dSplitterImpl(box2dWorld, anaxWorld)){
	m_impl->m_splitter.registerBodySplitCallback(this);
}

B2dSplitter::~B2dSplitter() {
}

void B2dSplitter::onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body) {
	auto entities = getEntities();
	m_impl->onb2BodySplit(splitBodies, body, entities);
}

void B2dSplitter::split(b2Vec2 startPoint, b2Vec2 endPoint) {
	m_impl->m_world->RayCast(&m_impl->m_splitter,startPoint, endPoint);
	m_impl->m_world->RayCast(&m_impl->m_splitter,endPoint, startPoint);
}

void B2dSplitter::clearIntersects() {
	m_impl->m_splitter.clearIntersects();
}

void B2dSplitter::deleteEntities() {
	m_impl->deleteEntities();
}

