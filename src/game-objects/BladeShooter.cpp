#include <game-objects/BladeShooter.h>
#include <SFML/System.hpp>
#include <components/BladeShooterComponent.h>
#include <components/PhysicsComponent.h>

class BladeShooter::BladeShooterImpl{

public:
	BladeShooterImpl(){}
	~BladeShooterImpl(){}

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		 anax::Entity entity = anaxWorld.createEntity();
		 auto& physicsComp = entity.addComponent<PhysicsComponent>();
		 auto& bladeShooterComp = entity.addComponent<BladeShooterComponent>();
		 b2Body* body = tmx::BodyCreator::Add(mapObject, box2dWorld, b2_staticBody);
		 physicsComp.physicsBody = body;
		 sf::FloatRect aabb = mapObject.GetAABB();
		 bladeShooterComp.bladeSize = tmx::SfToBoxVec(sf::Vector2f(aabb.width/2, aabb.height/2));
		 //TODO make configurable
		 bladeShooterComp.delayBetweenBladeShots = sf::seconds(2);
		 bladeShooterComp.bladeLinerVelocty = b2Vec2(10.0f, 0.0f);
		 entity.activate();
	}


};


BladeShooter::BladeShooter() : m_impl(new BladeShooterImpl()) {

}

BladeShooter::~BladeShooter() {
}

void BladeShooter::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}
