#include <game-objects/StaticObject.h>
#include <tmx/tmx2box2d.h>
#include <components/PhysicsComponent.h>
#include <components/IDComponent.h>


const std::unordered_map<std::string, b2BodyType> StaticObject::BODY_TYPE = {
		{"dynamic", b2_dynamicBody},
		{"static", b2_staticBody},
		{"", b2_staticBody}
};


StaticObject::StaticObject() {
}

StaticObject::~StaticObject() {
}

void StaticObject::createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	auto objectEntity = anaxWorld.createEntity();
	auto& idComponent = objectEntity.addComponent<IDComponent>();
	idComponent.uuid = mapObject.GetPropertyString("uuid");
	auto& physComp = objectEntity.addComponent<PhysicsComponent>();
	auto bodyType =  StaticObject::BODY_TYPE.find(mapObject.GetPropertyString("Body"));
	auto physicsBody = tmx::BodyCreator::Add(mapObject, box2dWorld, bodyType->second);
	physComp.physicsBody = physicsBody;
	objectEntity.activate();

}

GameObjectProperty StaticObject::getProperties() {
	GameObjectProperty object;
	object.properties = { {"Body", "static"} };
	object.objectShapeType = tmx::MapObjectShape::Rectangle;
	return object;
}
