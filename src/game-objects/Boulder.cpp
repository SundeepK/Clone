#include <game-objects/Boulder.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <game-objects/GameObjectTag.h>
#include <iostream>
#include <utilities/StringUtils.h>

class Boulder::BoulderImpl {

public:

	BoulderImpl() {
	}
	~BoulderImpl() {
	}

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		b2FixtureDef f;
		f.density = 1.f;
		f.restitution = 0.0f;
		f.filter.categoryBits = GameObjectTag::BOULDER;
		bodyDef.position = tmx::SfToBoxVec(mapObject.GetPosition());
		tmx::MapObjectShape shapeType = mapObject.GetShapeType();
		sf::Uint16 pointCount = mapObject.PolyPoints().size();

		//make a circle
		b2CircleShape c;
		auto width = mapObject.GetPropertyString("width");
		if(!width.empty()){
			c.m_radius = (std::stof(width) / 2.f);
		}else{
			c.m_radius = tmx::SfToBoxFloat(mapObject.GetAABB().width / 2.f);
		}
		f.shape = &c;

		b2Body* body = box2dWorld.CreateBody(&bodyDef);
		body->CreateFixture(&f);
	}

};

Boulder::Boulder() :
		m_impl(new BoulderImpl()) {
}

Boulder::~Boulder() {
}

void Boulder::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}

Boulder::Boulder(Boulder&& other) {
}

Boulder::Boulder(Boulder& other) {
}

std::vector<std::string> Boulder::getProperties() {
	return { "width" };
}
