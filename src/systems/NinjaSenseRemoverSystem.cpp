#include <systems/NinjaSenseRemoverSystem.h>
#include <vector>
#include <components/PhysicsComponent.h>
#include <Box2D/Box2D.h>
#include <components/NinjaDataComponent.h>
#include <SFML/System.hpp>
#include <iostream>

class NinjaSenseRemoverSystem::NinjaSenseRemoverSystemImpl{

public:

	sf::Clock m_clock;

	NinjaSenseRemoverSystemImpl(){}
	~NinjaSenseRemoverSystemImpl(){}

	void update(std::vector<anax::Entity>& entities) {
		for (anax::Entity entity : entities) {
			auto& ninjaSenseDataComp = entity.getComponent<NinjaDataComponent>();
			if (ninjaSenseDataComp.isNinjaSenseApplied) {
				auto& physicsComp = entity.getComponent<PhysicsComponent>();
				if ((m_clock.getElapsedTime() - ninjaSenseDataComp.lastTimeNinjaSenseApplied).asMilliseconds() > 1000) {
				std::cout << "in remover for one object" << entities.size() << std::endl;
					physicsComp.physicsBody->SetAngularDamping(1.0f);
					physicsComp.physicsBody->SetGravityScale(1.0f);
					physicsComp.physicsBody->SetLinearDamping(1.0f);
					physicsComp.physicsBody->SetLinearVelocity(b2Vec2(0, 7.0f));
					ninjaSenseDataComp.isNinjaSenseApplied = false;
				}
			}
		}

	}



};


NinjaSenseRemoverSystem::NinjaSenseRemoverSystem() : Base(anax::ComponentFilter().requires<NinjaDataComponent>()), m_impl(new NinjaSenseRemoverSystemImpl()) {

}

NinjaSenseRemoverSystem::~NinjaSenseRemoverSystem() {
}

void NinjaSenseRemoverSystem::update() {
    auto entities = getEntities();
	m_impl->update(entities);
}
