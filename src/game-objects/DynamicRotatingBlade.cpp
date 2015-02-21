#include <game-objects/DynamicRotatingBlade.h>
#include <tmx/tmx2box2d.h>
#include <iostream>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>

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


	b2Body* createBladeRod(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position = position;
		b2PolygonShape shape;
		shape.SetAsBox(5.0f, 0.2f);
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.restitution = 0.1f;
		fd.friction = 1.0f;
		fd.density = 1.0f;
		b2Body* connector  = box2dWorld.CreateBody(&bd);
		connector->CreateFixture(&fd);
		return connector;
	}

	b2Fixture* createBlade(b2Body* bodyToAttachTo){
	    b2PolygonShape bladeShape;
	    b2FixtureDef bladeFixtureDef;
	    bladeFixtureDef.shape = &bladeShape;

	    bladeFixtureDef.density = 0.3;
	    bladeFixtureDef.restitution = 0.0f;
	    bladeFixtureDef.friction = 10.0f;
//	    bladeFixtureDef.filter.categoryBits = playerBitMask ;
	    bladeShape.SetAsBox(2.0f, 2.0f, b2Vec2(-7.0f,0), 0);
	    return bodyToAttachTo->CreateFixture(&bladeFixtureDef);
	}


	b2Body* blade(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.type = b2_dynamicBody;

		b2PolygonShape shape;
		shape.SetAsBox(2.0f, 2.0f);
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.restitution = 0.1f;
		fd.friction = 1.0f;
		fd.density = 1.0f;
		b2Body* connector  = box2dWorld.CreateBody(&bd);
		connector->CreateFixture(&fd);
		return connector;
	}


	void addEntity(b2Body* body, anax::World& anaxWorld){
		auto objectEntity = anaxWorld.createEntity();
		auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
		auto& physComp = objectEntity.addComponent<PhysicsComponent>();
		auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();
		physComp.physicsBody = body;
		objectEntity.activate();
	}

	float getValue(std::string valueToParse, float defaultValue){
		if(!valueToParse.empty()) return std::stof(valueToParse);
		return defaultValue;
	}

	b2RevoluteJointDef getRevoluteJointForRotatingBlade(tmx::MapObject mapObject){
		b2RevoluteJointDef jointDef;
		jointDef.enableMotor = true;
		jointDef.motorSpeed = getValue(mapObject.GetPropertyString("motorSpeed"), 2.0f);
		jointDef.maxMotorTorque = getValue(mapObject.GetPropertyString("maxMotorTorque"), 1.0f);
		return jointDef;
	}

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {

		b2WeldJointDef jdblade;
		b2RevoluteJointDef jd = getRevoluteJointForRotatingBlade(mapObject);

		b2Vec2 position = tmx::SfToBoxVec(mapObject.GetPosition());
		b2Vec2 anchor(position);
		anchor.x = anchor.x -4.0f;

		b2Body* joint = createJoint(position, box2dWorld);
		b2Body* rod = createBladeRod(anchor, box2dWorld);
		b2Body* blad = blade(position, box2dWorld);

		addEntity(rod, anaxWorld);
		addEntity(blad, anaxWorld);

		jd.Initialize(joint, rod, tmx::SfToBoxVec(mapObject.GetPosition()));

		jdblade.bodyA = rod;
		jdblade.bodyB = blad;
		jdblade.collideConnected = false;
		jdblade.localAnchorA = b2Vec2(-7.0f, 0.0f);

		box2dWorld.CreateJoint(&jd);
		box2dWorld.CreateJoint(&jdblade);

	}

};

DynamicRotatingBlade::DynamicRotatingBlade() : m_impl(new DynamicRotatingBladeImpl()){
}

DynamicRotatingBlade::~DynamicRotatingBlade() {


}

void DynamicRotatingBlade::createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}

GameObjectProperty DynamicRotatingBlade::getProperties() {
	GameObjectProperty object;
	object.properties = {};
	object.hasShape = false;
	return object;
}
