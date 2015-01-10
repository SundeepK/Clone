#include <systems/NinjaSenseEntityTagger.h>
#include <vector>
#include <components/NinjaSenseComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <components/PhysicsComponent.h>
#include <iostream>
#include <game-objects/GameObjectTag.h>
#include <components/NinjaDataComponent.h>

class NinjaSenseEntityTagger::NinjaSenseEntityTaggerImpl{

public:

	sf::Clock m_clock;

	NinjaSenseEntityTaggerImpl(){
	}

	~NinjaSenseEntityTaggerImpl() {
	}

	bool ReportFixture(b2Fixture* fixture, std::vector<anax::Entity>& entities) {
		for(anax::Entity entity: entities){
			auto& physicsComp = entity.getComponent<PhysicsComponent>();
			if(fixture->GetFilterData().categoryBits == GameObjectTag::SPLITTABLE_OBJECT && fixture->GetBody() == physicsComp.physicsBody ){

				if (fixture->GetBody() == physicsComp.physicsBody) {
					auto& ninjaSenseDataComp = entity.getComponent<NinjaDataComponent>();
					ninjaSenseDataComp.lastTimeNinjaSenseApplied = m_clock.getElapsedTime();
					ninjaSenseDataComp.isNinjaSenseApplied = true;
					b2Body* body = fixture->GetBody();
					b2Vec2 velocity = body->GetLinearVelocity();
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetGravityScale(0.0f);
					body->SetAngularDamping(60.0f);
					body->SetLinearDamping(100.0f);
				}


				 //	entity.addComponent<NinjaSenseComponent>();
			}
		}


		return true;
	}

};


NinjaSenseEntityTagger::NinjaSenseEntityTagger() : Base(anax::ComponentFilter().requires<Texcoords, NinjaDataComponent, PhysicsComponent>()), 	m_impl(new NinjaSenseEntityTaggerImpl()) {
}

NinjaSenseEntityTagger::~NinjaSenseEntityTagger() {
}

bool NinjaSenseEntityTagger::ReportFixture(b2Fixture* fixture) {
	auto entities = getEntities();
	return	m_impl->ReportFixture(fixture, entities);
}
