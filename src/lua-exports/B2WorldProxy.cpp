#include <lua-exports/B2WorldProxy.h>
#include <iostream>
class B2WorldProxy::B2WorldProxyImpl{

public:
	B2WorldProxyImpl(b2World& box2dWorld) : m_box2dWorld(box2dWorld){

	}

	~B2WorldProxyImpl(){

	}


	b2World& m_box2dWorld;

	b2Body* createNewBody(b2BodyDef& bodyDef, b2PolygonShape& shape, b2FixtureDef& fixture){
		fixture.shape = &shape;
		bodyDef.angularDamping = 1;
		b2Body* body = m_box2dWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixture);
		return body;
	}


	b2Joint* createJoint(b2JointDef* joint) {
		b2Joint* d = m_box2dWorld.CreateJoint(joint);
		std::cout << "im here! c++: " << d->GetBodyA()->GetAngularDamping()  << std::endl;
		return d;
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
	m_impl->createJoint(&joint);

}
