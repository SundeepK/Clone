#include <game-objects/BladeShooter.h>
#include <SFML/System.hpp>
#include <components/BladeShooterComponent.h>
#include <components/PhysicsComponent.h>
#include <game-objects/GameObjectTag.h>
#include <components/Direction.h>
#include <map>

class BladeShooter::BladeShooterImpl{

public:
	BladeShooterImpl(){}
	~BladeShooterImpl(){}

	std::map<Direction, b2Vec2> DIR_TO_BLADE_VELOCITY = {
			{Direction::RIGHT, b2Vec2(8.0f, 0)},
			{Direction::LEFT, b2Vec2(-8.0f, 0)},
			{Direction::TOP, b2Vec2(0.0f, -8.0f)},
			{Direction::DOWN, b2Vec2(0.0f, 8.0f)},
			{Direction::NONE, b2Vec2(0.0f, 0)}
	};


	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World* anaxWorld) {
		anax::Entity entity = anaxWorld->createEntity();
		auto& physicsComp = entity.addComponent<PhysicsComponent>();
		auto& bladeShooterComp = entity.addComponent<BladeShooterComponent>();

		sf::FloatRect shapeAABB = mapObject.GetAABB();

		b2Vec2 mapOBjectShape = tmx::SfToBoxVec(sf::Vector2f(shapeAABB.width / 2, shapeAABB.height / 2));
		b2Filter filter;
		filter.categoryBits = GameObjectTag::BLADE_SHOOTER;
		b2Body* bladeShooter = tmx::BodyCreator::Add(mapObject, box2dWorld, b2_staticBody);
		bladeShooter->GetFixtureList()->SetFilterData(filter);

		physicsComp.physicsBody = bladeShooter;
		bladeShooterComp.bladeSize = mapOBjectShape;
		//TODO make configurable
		bladeShooterComp.delayBetweenBladeShots = sf::seconds(2);
		bladeShooterComp.bladeLinerVelocty = DIR_TO_BLADE_VELOCITY[DirectionMap::parseDirection(mapObject.GetPropertyString("ShootDir"))];
		entity.activate();
	}


};


BladeShooter::BladeShooter() : m_impl(new BladeShooterImpl()) {

}

BladeShooter::~BladeShooter() {
}

void BladeShooter::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, &anaxWorld);
}

GameObjectProperty BladeShooter::getProperties() {
	GameObjectProperty object;
	object.properties = { {"ShootDir",  "right"} };
	object.objectShapeType = tmx::MapObjectShape::Rectangle;
	return object;
}
