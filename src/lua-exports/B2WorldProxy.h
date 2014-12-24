#ifndef B2WORLDPROXY_H_
#define B2WORLDPROXY_H_

#include <Box2D/Box2D.h>
#include <memory.h>

class B2WorldProxy {

public:
	B2WorldProxy(b2World& box2dWorld);
	~B2WorldProxy();
	b2Body* createNewBody(b2BodyDef& bodyDef, b2PolygonShape& shape, b2FixtureDef& fixture);
	void createJoint(b2RevoluteJointDef& joint);
	void ropeJoint(b2RopeJointDef& joint);
	std::string UuidOf(b2Body* body);
	b2Fixture* addFixture(b2Body* body, b2PolygonShape& shape, b2FixtureDef& fixture);
	b2PrismaticJoint* createPrismaticJoint(b2PrismaticJointDef& joint);
	b2Body* createEdgeNewBody(b2BodyDef& bodyDef, b2EdgeShape& shape, b2FixtureDef& fixture);


private:
	class B2WorldProxyImpl;
	std::auto_ptr<B2WorldProxyImpl> m_impl;

};

#endif /* B2WORLDPROXY_H_ */
