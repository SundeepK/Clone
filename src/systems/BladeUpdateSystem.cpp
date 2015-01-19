#include <systems/BladeUpdateSystem.h>
#include <components/BladeComponent.h>
#include <components/PhysicsComponent.h>
#include <utilities/CollisionUtils.h>
#include <game-objects/GameObjectTag.h>
#include <iostream>

class BladeUpdateSystem::BladeUpdateSystemImpl{

public:
	BladeUpdateSystemImpl(b2World& b2World): m_box2dWorld(&b2World) {}
	~BladeUpdateSystemImpl(){}

	std::unique_ptr<b2World> m_box2dWorld;

	void update(std::vector<anax::Entity>& entities){
		for (anax::Entity entity : entities) {
			if (entity.isValid() && entity.hasComponent<BladeComponent>()) {
				auto& bladeComp = entity.getComponent<BladeComponent>();
				auto& physcisComp = entity.getComponent<PhysicsComponent>();
				b2Body* body = physcisComp.physicsBody;

				b2Vec2 linearVelocity = body->GetLinearVelocity();
				if ( linearVelocity.y >= bladeComp.minLinearVelocity.y && linearVelocity.x >= bladeComp.minLinearVelocity.x &&
						linearVelocity.x <= bladeComp.maxLinearVelocity.x && linearVelocity.y <= bladeComp.maxLinearVelocity.y) {
					body->ApplyLinearImpulse(bladeComp.bladeLinearVelocity, body->GetWorldCenter(), true);
				}
			}
		}
	}

	void BeginContact(std::vector<anax::Entity>& entities, b2Contact* contact) {
		auto fixtureA = contact->GetFixtureA();
		auto fixtureB = contact->GetFixtureB();

		for(anax::Entity entity : entities){
			auto& physcisComp = entity.getComponent<PhysicsComponent>();
			if((fixtureA == physcisComp.physicsBody->GetFixtureList() || fixtureB == physcisComp.physicsBody->GetFixtureList())
				&& 	!CollisionUtils::isColliding(contact, GameObjectTag::BLADE, GameObjectTag::NINJA_SENSE)	){
				physcisComp.physicsBody->SetLinearVelocity(b2Vec2_zero);
				physcisComp.isDead = true;
				entity.removeComponent<BladeComponent>();
				entity.deactivate();
			}
		}
	}

	void EndContact(b2Contact* contact) {

	}

};

BladeUpdateSystem::BladeUpdateSystem(b2World& b2World) : Base(anax::ComponentFilter().requires<PhysicsComponent,BladeComponent>()), m_impl(new BladeUpdateSystemImpl(b2World)){
}

BladeUpdateSystem::~BladeUpdateSystem() {
}

void BladeUpdateSystem::update() {
	auto entities = getEntities();
	m_impl->update(entities);
}

void BladeUpdateSystem::BeginContact(b2Contact* contact) {
   auto entities = getEntities();
   m_impl->BeginContact(entities, contact);
}

void BladeUpdateSystem::EndContact(b2Contact* contact) {
	   m_impl->EndContact(contact);

}
