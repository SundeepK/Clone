#include <entity-loaders/InterestPointsEntityLoader.h>
#include <components/PhysicsComponent.h>

class InterestPointsEntityLoader::InterestPointsEntityLoaderImpl{

public:
	InterestPointsEntityLoaderImpl(){
	}

	~InterestPointsEntityLoaderImpl(){

	}

	void loadEntity(anax::World& anaxWorld, b2World& box2dWorld,
			std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* myLuaState){

		tmx::MapObject endPointMapObject = loadedMapData["PlayerEndPoint"];

		auto endPoint = anaxWorld.createEntity();
		auto& sensorsComp = endPoint.addComponent<Sensor>();

		auto& physComp = endPoint.addComponent<PhysicsComponent>();

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
		endPointFixture.tag = "EndPointFixture";
		sensorsComp.sensors.insert(std::pair<std::string, SensorComponent>(endPointFixture.tag, endPointFixture));

	}

};


void InterestPointsEntityLoader::loadEntity(anax::World& anaxWorld, b2World& box2dWorld,
		std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* myLuaState) {

}
