#include <systems/BreakableJointSystem.h>
#include <components/BreakableJointComponent.h>
#include <components/PhysicsComponent.h>
#include <vector>
#include <iostream>
#include <game-objects/GameObjectTag.h>

class BreakableJointSystem::BreakableJointSystemImpl {

public:

	std::unique_ptr<b2World> m_box2dWorld;

	BreakableJointSystemImpl(b2World& b2World) :  m_box2dWorld(&b2World) {}
	~BreakableJointSystemImpl() {}


	void update(std::vector<anax::Entity>& entities, float inverseDt) {
		for (auto entity : entities) {
			auto& physicsComp = entity.getComponent<PhysicsComponent>();
			b2JointEdge* jointEdge = physicsComp.physicsBody->GetJointList();
			if(entity.getComponent<BreakableJointComponent>().isBreakable){
				int count = 0;
				while (jointEdge) {
					count++;
					b2Vec2 reactionforce = jointEdge->joint->GetReactionForce(inverseDt);
//					std::cout << "count val: " << count << " force: " << reactionforce.LengthSquared() << std::endl;
					if (!std::isnan(reactionforce.LengthSquared()) && isinff(reactionforce.LengthSquared()) == 0 && reactionforce.LengthSquared() > 70) {
						m_box2dWorld->DestroyJoint(jointEdge->joint);
						//entity.removeComponent<BreakableJointComponent>();
					}
					jointEdge = jointEdge->next;
				}
			}
		}
	}

	void BeginContact(std::vector<anax::Entity>& entities, b2Contact* contact) {
		auto fixtureA = contact->GetFixtureA();
		auto fixtureB = contact->GetFixtureB();

		auto filterDataA = fixtureA->GetFilterData();
		auto filterDataB = fixtureB->GetFilterData();

		if( ((filterDataA.categoryBits & GameObjectTag::ROPE_SEGMENT) == GameObjectTag::ROPE_SEGMENT && (filterDataB.categoryBits & GameObjectTag::BOULDER) == GameObjectTag::BOULDER)
				|| ((filterDataB.categoryBits & GameObjectTag::ROPE_SEGMENT) == GameObjectTag::ROPE_SEGMENT && (filterDataA.categoryBits & GameObjectTag::BOULDER) == GameObjectTag::BOULDER)){

			if((filterDataA.categoryBits & GameObjectTag::ROPE_SEGMENT) == GameObjectTag::ROPE_SEGMENT){
				setAsBreakable(entities, fixtureA->GetBody());
			}else if((filterDataB.categoryBits & GameObjectTag::ROPE_SEGMENT )== GameObjectTag::ROPE_SEGMENT){
				setAsBreakable(entities, fixtureB->GetBody());
			}

		}
	}

	void setAsBreakable(std::vector<anax::Entity>& entities, b2Body* body){
		for (auto entity : entities) {
			if(entity.getComponent<PhysicsComponent>().physicsBody == body){
				entity.getComponent<BreakableJointComponent>().isBreakable = true;
				break;
			}
		}
	}

	void EndContact(std::vector<anax::Entity>& entities, b2Contact* contact) {

	}

};

BreakableJointSystem::BreakableJointSystem(b2World& b2World) :
		Base(anax::ComponentFilter().requires<PhysicsComponent,BreakableJointComponent>()), m_impl(new BreakableJointSystemImpl(b2World)) {

}

BreakableJointSystem::~BreakableJointSystem() {
}

void BreakableJointSystem::BeginContact(b2Contact* contact) {
	auto entities = getEntities();
	m_impl->BeginContact(entities, contact);
}

void BreakableJointSystem::EndContact(b2Contact* contact) {
	auto entities = getEntities();
	m_impl->EndContact(entities, contact);
}

void BreakableJointSystem::update(float inverseDt) {
	auto entities = getEntities();
	m_impl->update(entities, inverseDt);
}
