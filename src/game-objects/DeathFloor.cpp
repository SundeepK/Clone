#include <game-objects/DeathFloor.h>
#include <components/PhysicsComponent.h>
#include <components/DeathBringerComponent.h>
#include <iostream>
#include <game-objects/GameObjectTag.h>

class DeathFloor::DeathFloorImpl{

public:
	DeathFloorImpl(){}
	~DeathFloorImpl(){}

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		anax::Entity entity = anaxWorld.createEntity();
		auto& physicsComp = entity.addComponent<PhysicsComponent>();
		auto& deathComp = entity.addComponent<DeathBringerComponent>();
		b2Body* deathFloorBody = tmx::BodyCreator::Add(mapObject, box2dWorld, b2_staticBody);

		b2Fixture* fixture = deathFloorBody->GetFixtureList();

		b2Filter filter;
		filter.categoryBits = GameObjectTag::DEATH_BRINGER_OBJECT;

		while(fixture){
 			std::cout << "setting filter" << std::endl;
			fixture->SetFilterData(filter);
			fixture = fixture->GetNext();
		}

		physicsComp.physicsBody = deathFloorBody;
		entity.activate();
	}

};

DeathFloor::DeathFloor() {
}

DeathFloor::~DeathFloor() {
}

void DeathFloor::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}
