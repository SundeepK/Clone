#include "B2dSplitter.h"
#include <TextureMapper.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <vector>
#include <set>
#include <algorithm>
#include <opengl/TextureLoader.h>
#include <components/SplitDirectionComponent.h>
#include <components/IgnoreCollisionComponent.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <components/NinjaDataComponent.h>
#include <game-objects/GameObjectTag.h>

struct RemoveValidSplitEntities : public std::unary_function<std::pair<anax::Entity, anax::Entity>&, bool>
{
    bool operator()(std::pair<anax::Entity, anax::Entity>& entityPair) const
    {
		auto firstSplitEntity = entityPair.first;
		auto secondSplitEntity = entityPair.second;

		b2Body* firstBody = firstSplitEntity.getComponent<PhysicsComponent>().physicsBody;
		b2Body* secondBody = secondSplitEntity.getComponent<PhysicsComponent>().physicsBody;

        b2PolygonShape* firtshape =((b2PolygonShape*)firstBody->GetFixtureList()->GetShape());
        b2PolygonShape* secshape =((b2PolygonShape*)secondBody->GetFixtureList()->GetShape());

		if (firtshape->GetVertex(0).x > 0 && firtshape->GetVertex(0).y > 0 && secshape->GetVertex(0).x > 0 && secshape->GetVertex(0).y > 0) {
    		return true;
    	}else{
    		return false;
    	}

    }
};

	struct SplitLine{
	b2Vec2 startPoint;
	b2Vec2 endPoint;
	int count = 0;
	};

class B2dSplitter::B2dSplitterImpl{

public:

	enum class SplitBody{
			FIRST_BODY,
			SECOND_BODY,
			NOT_SURE
	};


	B2dSplitterImpl(b2World& box2dWorld, anax::World& anaxWorld) :  m_world(&box2dWorld), m_anaxWorld(&anaxWorld), m_textureMapper(Box2DConstants::WORLD_SCALE){
	}

	~B2dSplitterImpl(){
	}

	sf::Clock m_clock;
	Splitter m_splitter;
    std::unique_ptr<anax::World> m_anaxWorld;
    TextureMapper m_textureMapper;
    TextureLoader m_textureLoader;

	std::set<anax::Entity, CompareEntities> m_entitiesToKill;
	std::vector<std::pair<anax::Entity, anax::Entity>> m_splitEntityPairs;
	std::set<b2Body*> m_bodiesToKill;
    std::unique_ptr<b2World> m_world;
    std::vector<SplitLine> m_splitLines;

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
	    auto& ninjaData = objectEntity.addComponent<NinjaDataComponent>();
	    ninjaData.isNinjaSenseApplied = true;
	    ninjaData.lastTimeNinjaSenseApplied = m_clock.getElapsedTime();

	    auto& ignoreCollisionFilter = objectEntity.addComponent<IgnoreCollisionComponent>();

	    ignoreCollisionFilter.reason = IgnoreCollisionReason::NEW_SPLIT_BODY;
	    ignoreCollisionFilter.timeIgnoreCollisionAdded = m_clock.getElapsedTime();

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
		b2Fixture* fixture = oldBodyToSplit->GetFixtureList();

		if(!((fixture->GetFilterData().categoryBits & GameObjectTag::DEATH_BRINGER_OBJECT ) == GameObjectTag::DEATH_BRINGER_OBJECT)){
			newSplitB2bodyBuilder.setcategoryBits(fixture->GetFilterData().categoryBits);
		}

		//TODO set to 1 once reliably can find area of shape to prevent too small object from ebing split
		newSplitB2bodyBuilder.setDensity(0.1f);
		newSplitB2bodyBuilder.setFriction(0.0f);
		b2Body* newSplitBody = newSplitB2bodyBuilder.build(*m_world);
		entitiesToFill.push_back(createSplitBodyEntityFromOldTexCoords(newSplitBody, oldBodyToSplit, entity));
	}

	void debug( std::pair<anax::Entity, anax::Entity> entityPair){
		auto firstSplitEntity = entityPair.first;
			auto secondSplitEntity = entityPair.second;

			auto& firstSplitDir = firstSplitEntity.getComponent<SplitDirectionComponent>();
			auto& secondSplitDir = secondSplitEntity.getComponent<SplitDirectionComponent>();

				b2Body* firstBody = firstSplitEntity.getComponent<PhysicsComponent>().physicsBody;
				b2Body* secondBody = secondSplitEntity.getComponent<PhysicsComponent>().physicsBody;

				float b = firstBody->GetPosition().x;
				std::cout << "local first: " << b  << std::endl;
				std::cout << "local sec: " << secondBody->GetWorldCenter().x  << std::endl;
	}

	void refreshEntityBodyTypes(){

		for(auto entitypair: m_splitEntityPairs){
			setBodyTypes(entitypair);
		}

		m_splitEntityPairs.erase(std::remove_if(m_splitEntityPairs.begin(), m_splitEntityPairs.end(), RemoveValidSplitEntities()),
				m_splitEntityPairs.end());

	//	m_splitEntityPairs.clear();
	}

	bool shouldSetFirstBodyAsDynamic(const b2PolygonShape* firtShape, const b2PolygonShape* secondShape, const Direction& splitDirection){
		bool shouldSetFirstBodyAsDynamic = false;
		if (splitDirection == Direction::RIGHT || splitDirection == Direction::LEFT) {
			if (splitDirection == Direction::RIGHT) {
				if (firtShape->GetVertex(0).x > secondShape->GetVertex(0).x) {
					shouldSetFirstBodyAsDynamic = true;
				}
			} else {
				if (firtShape->GetVertex(0).x < secondShape->GetVertex(0).x) {
					shouldSetFirstBodyAsDynamic = true;
				}
			}
		} else if (splitDirection == Direction::TOP || splitDirection == Direction::DOWN) {
			if (splitDirection == Direction::DOWN) {
				if (firtShape->GetVertex(0).y > secondShape->GetVertex(0).y) {
					shouldSetFirstBodyAsDynamic = true;
				}
			} else {
				if (firtShape->GetVertex(0).y < secondShape->GetVertex(0).y) {
					shouldSetFirstBodyAsDynamic = true;
				}
			}
		}
		return shouldSetFirstBodyAsDynamic;
	}

	SplitBody decideBodyToSetAsDynamic(const b2Body* firstBody, const b2Body* secondBody, const Direction& splitDirection){
        b2PolygonShape* firtshape =((b2PolygonShape*)firstBody->GetFixtureList()->GetShape());
        b2PolygonShape* secshape =((b2PolygonShape*)secondBody->GetFixtureList()->GetShape());
		if (firtshape->GetVertex(0).x > 0 && firtshape->GetVertex(0).y > 0 && secshape->GetVertex(0).x > 0 && secshape->GetVertex(0).y > 0) {
			if(shouldSetFirstBodyAsDynamic(firtshape, secshape,  splitDirection)){
				return SplitBody::FIRST_BODY;
			}else{
				return SplitBody::SECOND_BODY;
			}
		}else{
			return SplitBody::NOT_SURE;
		}
	}

	void setBodyTypes( std::pair<anax::Entity, anax::Entity> entityPair){
		auto firstSplitEntity = entityPair.first;
		auto secondSplitEntity = entityPair.second;

		auto& firstSplitDir = firstSplitEntity.getComponent<SplitDirectionComponent>();
		auto& secondSplitDir = secondSplitEntity.getComponent<SplitDirectionComponent>();

    	assert (
    		"Split direction are not the same as split body" &&
    		firstSplitDir.splitDirection == secondSplitDir.splitDirection
    	);

		b2Body* firstBody = firstSplitEntity.getComponent<PhysicsComponent>().physicsBody;
		b2Body* secondBody = secondSplitEntity.getComponent<PhysicsComponent>().physicsBody;

		if (firstSplitDir.splitDirection == Direction::NONE) {
			firstBody->SetType(b2_dynamicBody);
			secondBody->SetType(b2_dynamicBody);

//			firstBody->ApplyForceToCenter(b2Vec2(10, 10), true);
//			firstBody->SetGravityScale(0.2f);
//			firstBody->SetLinearDamping(10.0f);
//
//			secondBody->ApplyForceToCenter(b2Vec2(10, 10), true);
//			secondBody->SetGravityScale(0.2f);
//			secondBody->SetLinearDamping(10.0f);

		} else {
			SplitBody bodyToSetAsDynamic = decideBodyToSetAsDynamic(firstBody, secondBody, firstSplitDir.splitDirection);
			if (bodyToSetAsDynamic == SplitBody::FIRST_BODY) {
				firstBody->SetType(b2_dynamicBody);
//				firstBody->ApplyForceToCenter(b2Vec2(10, 10), true);
//				firstBody->SetGravityScale(0.2f);
//				firstBody->SetLinearDamping(10.0f);


			} else if (bodyToSetAsDynamic == SplitBody::SECOND_BODY) {
				secondBody->SetType(b2_dynamicBody);
//				secondBody->ApplyForceToCenter(b2Vec2(10, 10), true);
//				secondBody->SetGravityScale(0.2f);
//				secondBody->SetLinearDamping(10.0f);


			}
		}

	}

	void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies,b2Body* body, std::vector<anax::Entity>& entities) {
//		if (body->GetMass() < 0.1f && body->GetType() != b2_staticBody) return;
		//TODO use area of shape to prevent too small objects being split
		std::vector<anax::Entity> newlyCreatedEntities;
		for (auto builder : splitBodies) {
			for (auto entity : entities) {
				if (entity.getComponent<PhysicsComponent>().physicsBody == body) {
					createNewSplitBody(builder, body, entity, newlyCreatedEntities);
					break;
				}
			}
		}
		if(splitBodies.size() == 2 && newlyCreatedEntities.size() == 2 && body->GetType() == b2_staticBody){
			m_splitEntityPairs.push_back(std::pair<anax::Entity, anax::Entity>(newlyCreatedEntities[0], newlyCreatedEntities[1]));
		}
	//	setBodyTypes(newlyCreatedEntities);

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

	if(m_impl->m_splitLines.size() >=1 && m_impl->m_splitLines.back().count >= 1){
		m_impl->m_splitLines.pop_back();
	}

	m_impl->onb2BodySplit(splitBodies, body, entities);
}

void B2dSplitter::split(b2Vec2 startPoint, b2Vec2 endPoint) {
	SplitLine splitLine;
	splitLine.startPoint = startPoint;
	splitLine.endPoint = endPoint;
	//m_impl->m_splitLines.push_back(splitLine);
	m_impl->m_world->RayCast(&m_impl->m_splitter,startPoint, endPoint);
	m_impl->m_world->RayCast(&m_impl->m_splitter,endPoint, startPoint);
	//m_impl->m_splitLines.back().count++;
}

void B2dSplitter::clearIntersects() {
	m_impl->m_splitter.clearIntersects();
}

void B2dSplitter::deleteEntities() {
	m_impl->deleteEntities();
}

void B2dSplitter::refreshEntityBodyTypes() {
	for(SplitLine& splitLine : m_impl->m_splitLines){
		m_impl->m_world->RayCast(&m_impl->m_splitter,splitLine.startPoint, splitLine.endPoint);
		m_impl->m_world->RayCast(&m_impl->m_splitter,splitLine.endPoint, splitLine.startPoint);
		splitLine.count++;
	}

	m_impl->m_splitLines.erase(
	    std::remove_if(
	    		m_impl->m_splitLines.begin(),
				m_impl->m_splitLines.end(),
	        [&](SplitLine& splitLine){return  splitLine.count >= 2;}),
			m_impl->m_splitLines.end());

	m_impl->refreshEntityBodyTypes();
}

