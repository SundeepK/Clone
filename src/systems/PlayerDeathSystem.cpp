#include <systems/PlayerDeathSystem.h>
#include <components/PlayerTagComponent.h>
#include <components/PlayerDeadComponent.h>
#include <components/PhysicsComponent.h>
#include <tmx/tmx2box2d.h>
#include <iostream>
#include <anax/World.hpp>

class PlayerDeathSystem::PlayerDeathSystemImpl{
public:
	PlayerDeathSystemImpl(){}
	~PlayerDeathSystemImpl(){}

	void update(anax::World& world, std::vector<anax::Entity>& entities, sf::Vector2u mapSize) {
		for(anax::Entity entity : entities){
			auto& physicsComp = entity.getComponent<PhysicsComponent>();
			auto playerPosition = tmx::BoxToSfVec(physicsComp.physicsBody->GetPosition());
 			std::cout << "x pos" << playerPosition.x << " y pos" << playerPosition.y << std::endl;
 			if((playerPosition.x <  -200 || playerPosition.x > mapSize.x + 100 || playerPosition.y > mapSize.y +100) && !entity.hasComponent<PlayerDeadComponent>()){
 				auto entity = world.createEntity();
 				entity.addComponent<PlayerDeadComponent>();
 				entity.activate();
			}
		}
	}

};

PlayerDeathSystem::PlayerDeathSystem() : Base(anax::ComponentFilter().requires<PlayerTagComponent>()), m_impl(new PlayerDeathSystemImpl()) {
}

PlayerDeathSystem::~PlayerDeathSystem() {
}

void PlayerDeathSystem::update(sf::Vector2u mapSize) {
	auto entities = getEntities();
	m_impl->update(getWorld(), entities, mapSize);
}
