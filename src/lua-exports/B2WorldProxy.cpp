#include <lua-exports/B2WorldProxy.h>
#include <iostream>
#include <UUIDGenerator.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
class B2WorldProxy::B2WorldProxyImpl{

public:
	B2WorldProxyImpl(b2World& box2dWorld) : m_box2dWorld(box2dWorld){

	}

	~B2WorldProxyImpl(){

	}

	b2Joint* rope;
	b2World& m_box2dWorld;
	b2RopeJointDef ropeDef;

	b2Body* createNewBody(b2BodyDef& bodyDef, b2PolygonShape& shape, b2FixtureDef& fixture){
		fixture.shape = &shape;
		b2Body* body = m_box2dWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixture);
		body->SetUserData(new std::string(UUIDGenerator::createUuid())); //TODO Manage this better, just here to get things working
		return body;
	}

	b2Body* createNewBody(b2BodyDef& bodyDef, b2EdgeShape& shape, b2FixtureDef& fixture){
		fixture.shape = &shape;
		b2Body* body = m_box2dWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixture);
		body->SetUserData(new std::string(UUIDGenerator::createUuid())); //TODO Manage this better, just here to get things working
		return body;
	}


	b2Joint* createJoint(b2RevoluteJointDef& joint) {
		b2Joint* d = m_box2dWorld.CreateJoint(&joint);
		return d;
	}

	b2PrismaticJoint* createJoint(b2PrismaticJointDef& joint) {
		return static_cast<b2PrismaticJoint*>(m_box2dWorld.CreateJoint(&joint));
	}


	b2Joint* ropeJoint(b2RopeJointDef& joint) {

		ropeDef.localAnchorA = joint.localAnchorA;

		ropeDef.localAnchorB.SetZero();

		float32 extraLength = 0.01f;
		ropeDef.maxLength = joint.maxLength;
		ropeDef.bodyB = joint.bodyB;

		ropeDef.bodyA = joint.bodyA;

		rope = m_box2dWorld.CreateJoint(&ropeDef);

		return NULL;
	}

	std::string UuidOf(b2Body* body) {
		void* userData = body->GetUserData();
		if(userData){
			std::string* uuid = static_cast<std::string*>(userData);
			std::string s = *uuid;
			return s;
		}else{
			std::string uuid = UUIDGenerator::createUuid();
			body->SetUserData(new std::string(uuid)); //TODO Manage this better, just here to get things working
			return uuid;
		}
	}

	b2Fixture* addFixture(b2Body* body, b2PolygonShape& shape, b2FixtureDef& fixture) {
	  fixture.shape = & shape;
	  return body->CreateFixture(&fixture);
	}

	b2Body* createBodyFromMapObject(tmx::MapObject& mapObject, b2BodyType bodyType){
		return tmx::BodyCreator::Add(mapObject, m_box2dWorld, bodyType);
	}

};


B2WorldProxy::B2WorldProxy(b2World& box2dWorld) :  m_impl(new B2WorldProxyImpl(box2dWorld)){
}

B2WorldProxy::~B2WorldProxy() {
}

b2Body* B2WorldProxy::createNewBody(b2BodyDef& bodyDef, b2PolygonShape& shape, b2FixtureDef& fixture) {
	return m_impl->createNewBody(bodyDef, shape, fixture);
}

void B2WorldProxy::createJoint(b2RevoluteJointDef& joint) {
	m_impl->createJoint(joint);

}

void B2WorldProxy::ropeJoint(b2RopeJointDef& joint) {
	m_impl->ropeJoint(joint);
}

std::string B2WorldProxy::UuidOf(b2Body* body) {
	return m_impl->UuidOf(body);
}

b2Fixture* B2WorldProxy::addFixture(b2Body* body, b2PolygonShape& shape, b2FixtureDef& fixture) {
	return m_impl->addFixture(body, shape, fixture);
}

b2PrismaticJoint* B2WorldProxy::createPrismaticJoint(b2PrismaticJointDef& joint) {
	return m_impl->createJoint(joint);
}

b2Body* B2WorldProxy::createEdgeNewBody(b2BodyDef& bodyDef, b2EdgeShape& shape,
		b2FixtureDef& fixture) {
	return m_impl->createNewBody(bodyDef, shape, fixture);
}

b2Body* B2WorldProxy::createBodyFromMapObject(tmx::MapObject& mapObject,
		b2BodyType bodyType) {
	return m_impl->createBodyFromMapObject(mapObject, bodyType);
}
