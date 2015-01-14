#include <systems/BladeUpdateSystem.h>
#include <components/BladeComponent.h>
#include <components/PhysicsComponent.h>

class BladeUpdateSystem::BladeUpdateSystemImpl{

public:
	BladeUpdateSystemImpl(){}
	~BladeUpdateSystemImpl(){}

	void update(std::vector<anax::Entity>& entities){
		for(anax::Entity entity : entities){
			auto& bladeComp = entity.getComponent<BladeComponent>();
			auto& physcisComp = entity.getComponent<PhysicsComponent>();
			b2Body* body = physcisComp.physicsBody;
			b2Vec2 linearVelocity = body->GetLinearVelocity();
			if (linearVelocity.x <= bladeComp.maxLinearVelocity.x && linearVelocity.y <= bladeComp.maxLinearVelocity.y) {
				body->ApplyLinearImpulse(bladeComp.bladeLinearVelocity, body->GetWorldCenter(), true);
			}
		}
	}

};

BladeUpdateSystem::BladeUpdateSystem() : Base(anax::ComponentFilter().requires<PhysicsComponent,BladeComponent>()), m_impl(new BladeUpdateSystemImpl()){
}

BladeUpdateSystem::~BladeUpdateSystem() {
}

void BladeUpdateSystem::update() {
	auto entities = getEntities();
	m_impl->update(entities);
}
