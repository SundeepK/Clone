#include <systems/PlayerDeathSystem.h>
#include <components/PlayerTagComponent.h>
#include <components/PlayerDeadComponent.h>
#include <components/PhysicsComponent.h>
#include <tmx/tmx2box2d.h>
#include <iostream>
#include <anax/World.hpp>
#include <game-objects/GameObjectTag.h>
#include <utilities/CollisionUtils.h>

class PlayerDeathSystem::PlayerDeathSystemImpl{
public:
	PlayerDeathSystemImpl(){}
	~PlayerDeathSystemImpl(){}

	void update(anax::World& world, std::vector<anax::Entity>& entities, sf::Vector2u mapSize) {
		for(anax::Entity entity : entities){
			auto& physicsComp = entity.getComponent<PhysicsComponent>();
			auto playerPosition = tmx::BoxToSfVec(physicsComp.physicsBody->GetPosition());
 			if((playerPosition.x <  -200 || playerPosition.x > mapSize.x + 100 || playerPosition.y > mapSize.y +100) && !entity.hasComponent<PlayerDeadComponent>()){
 				auto entity = world.createEntity();
 				entity.addComponent<PlayerDeadComponent>();
 				entity.activate();
			}
		}
	}

	void BeginContact(anax::World& world, b2Contact* contact) {

		for(anax::Entity entity : world.getEntities()){
			if(entity.hasComponent<PlayerDeadComponent>()){
				return;
			}
		}

		if(CollisionUtils::isColliding(contact, 0x0003, GameObjectTag::DEATH_BRINGER_OBJECT)){
 			std::cout << "should be dead" << std::endl;
			auto entity = world.createEntity();
			entity.addComponent<PlayerDeadComponent>();
			entity.activate();
		}
	}

	void EndContact(b2Contact* contact) {
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

void PlayerDeathSystem::BeginContact(b2Contact* contact) {
	m_impl->BeginContact(getWorld(), contact);
}

void PlayerDeathSystem::EndContact(b2Contact* contact) {
}
