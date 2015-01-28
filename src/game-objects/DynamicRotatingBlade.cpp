#include <game-objects/DynamicRotatingBlade.h>
#include <tmx/tmx2box2d.h>
#include <iostream>

class DynamicRotatingBlade::DynamicRotatingBladeImpl{
public:
	DynamicRotatingBladeImpl(){}
	~DynamicRotatingBladeImpl(){}

	b2Body* createJoint(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.position = position;

		b2CircleShape shape;
		shape.m_radius = 0.5f;
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.restitution = 0.1f;
		fd.friction = 1.0f;
		fd.density = 0.0f;
		b2Body* connector  = box2dWorld.CreateBody(&bd);
		connector->CreateFixture(&fd);
		return connector;
	}


	b2Body* createBladeConnector(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = position;
		b2PolygonShape shape;
		shape.SetAsBox(5.0f, 0.5f);
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.restitution = 0.1f;
		fd.friction = 1.0f;
		fd.density = 1.0f;
		b2Body* connector  = box2dWorld.CreateBody(&bd);
		connector->CreateFixture(&fd);
		return connector;
	}

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		b2RevoluteJointDef jd;
		jd.enableMotor = true;
		jd.motorSpeed = 2.0f;
		jd.maxMotorTorque = 1.0f;
		std::cout << "in DynamicRotatingBlade" << std::endl;
		b2Vec2 anchor(tmx::SfToBoxVec(mapObject.GetPosition()));
		anchor.x = anchor.x -2.0f;
		b2Body* joint = createJoint(tmx::SfToBoxVec(mapObject.GetPosition()), box2dWorld);
		b2Body* pivot = createBladeConnector(anchor, box2dWorld);

		jd.Initialize(joint, pivot, tmx::SfToBoxVec(mapObject.GetPosition()));
		box2dWorld.CreateJoint(&jd);
	}

};

DynamicRotatingBlade::DynamicRotatingBlade() : m_impl(new DynamicRotatingBladeImpl()){
}

DynamicRotatingBlade::~DynamicRotatingBlade() {


}

void DynamicRotatingBlade::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}
