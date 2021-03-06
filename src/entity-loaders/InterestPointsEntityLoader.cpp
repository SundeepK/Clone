#include "InterestPointsEntityLoader.h"

#include <entity-loaders/InterestPointsEntityLoader.h>
#include <components/PhysicsComponent.h>
#include <components/EndPointCollisionTagComponent.h>
#include <components/EndPointTagComponent.h>

class InterestPointsEntityLoader::InterestPointsEntityLoaderImpl{

public:

	InterestPointsEntityLoaderImpl(){
	}

	~InterestPointsEntityLoaderImpl(){

	}

	void loadEntity(anax::World& anaxWorld, b2World& box2dWorld,
			std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* luaState){

		tmx::MapObject endPointMapObject = loadedMapData["PlayerEndPoint"];

		auto endPoint = anaxWorld.createEntity();
		auto& sensorsComp = endPoint.addComponent<Sensor>();

		auto& physComp = endPoint.addComponent<PhysicsComponent>();
		auto& endPointComp = endPoint.addComponent<EndPointCollisionTagComponent>();
		auto& endPointTagComp = endPoint.addComponent<EndPointTagComponent>();

		B2BoxBuilder builder(endPointMapObject.GetAABB().height, endPointMapObject.GetAABB().width);
		builder
		.bodyType(b2_staticBody)
		.setPosition(b2Vec2(endPointMapObject.GetPosition().x, endPointMapObject.GetPosition().y))
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

};

InterestPointsEntityLoader::InterestPointsEntityLoader() : m_impl(new InterestPointsEntityLoaderImpl()) {
}

InterestPointsEntityLoader::~InterestPointsEntityLoader() {
}

void InterestPointsEntityLoader::loadEntity(anax::World& anaxWorld, b2World& box2dWorld,
		std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* luaState) {
	m_impl->loadEntity(anaxWorld, box2dWorld, loadedMapData, luaState);
}
