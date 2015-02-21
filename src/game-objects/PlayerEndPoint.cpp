#include <game-objects/PlayerEndPoint.h>
#include <components/Sensors.h>
#include <components/PhysicsComponent.h>
#include <components/EndPointTagComponent.h>
#include <components/EndPointCollisionTagComponent.h>
#include <components/SensorComponent.h>
#include <B2BoxBuilder.h>

PlayerEndPoint::PlayerEndPoint() {
}

PlayerEndPoint::~PlayerEndPoint() {
}

void PlayerEndPoint::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	auto endPoint = anaxWorld.createEntity();
	auto& sensorsComp = endPoint.addComponent<Sensor>();

	auto& physComp = endPoint.addComponent<PhysicsComponent>();
	auto& endPointComp = endPoint.addComponent<EndPointCollisionTagComponent>();
	auto& endPointTagComp = endPoint.addComponent<EndPointTagComponent>();

	B2BoxBuilder builder(mapObject.GetAABB().height, mapObject.GetAABB().width);
	builder
	.bodyType(b2_staticBody)
	.setPosition(b2Vec2(mapObject.GetPosition().x, mapObject.GetPosition().y))
	.fixedRotation(true)
	.setSensor(true)
	.setRestitution(0.0f)
	.setDensity(1.0f);

	b2Body* endPointBody = builder.build(box2dWorld);

	physComp.physicsBody = endPointBody;

	SensorComponent endPointFixture;
	endPointFixture.sensors = endPointBody->GetFixtureList();
	endPointFixture.tag = "EndPointSensor";
	sensorsComp.sensors.insert(std::pair<std::string, SensorComponent>(endPointFixture.tag, endPointFixture));
	endPoint.activate();
}

GameObjectProperty PlayerEndPoint::getProperties() {
	GameObjectProperty object;
	object.properties = {};
	object.objectShapeType = tmx::MapObjectShape::Rectangle;
	return object;
}
