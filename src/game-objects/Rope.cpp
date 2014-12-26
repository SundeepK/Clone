#include <game-objects/Rope.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <iostream>
#include <game-objects/GameObjectTag.h>

class Rope::RopeImpl {

public:
	RopeImpl(b2World& world, anax::World& anaxWorld) :  m_world(world),  m_anaxWorld(anaxWorld), m_rope(NULL) {
	}

	~RopeImpl() {
	}

	b2World& m_world;
	anax::World& m_anaxWorld;
	b2RopeJointDef m_ropeDef;
	b2Joint* m_rope;

	b2Body* createRope() {
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			bd.type = b2_staticBody;
			bd.position = b2Vec2(20.0f, 40.0f);
			b2PolygonShape shape;
			shape.SetAsBox(2.0f, 0.5f);
			b2FixtureDef fd;
			fd.shape = &shape;
			ground = m_world.CreateBody(&bd);
			ground->CreateFixture(&fd);
		}
		b2Body* prevBody = ground;
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.1f, 0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			fd.friction = 0.2f;
			fd.filter.categoryBits = 0x0001;
			fd.filter.maskBits =  0xff - 0x0003;

			b2RevoluteJointDef jd;
			jd.collideConnected = false;

			const int32 N = 50;
			const float32 x = 20.0f;
			m_ropeDef.localAnchorA.Set(0.0f, x);

			for (int32 yVal = 40; yVal < N; ++yVal) {
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(x,  yVal);
				if (yVal == N - 1) {
					shape.SetAsBox(1.5f, 1.5f);
					fd.density = 1.0f;
					fd.filter.categoryBits = GameObjectTag::ROPE_BOX;
					fd.filter.maskBits = GameObjectTag::DYNAMIC_OBJECT;
					bd.position.Set(x,   yVal);
//					bd.linearDamping = 2.0f;
//					bd.angularDamping = 10.0f;
					//bd.fixedRotation = true;
				}

				b2Body* body = m_world.CreateBody(&bd);

				body->CreateFixture(&fd);
				std::cout << "rope: "   <<  fd.filter.maskBits <<std::endl;

				auto objectEntity = m_anaxWorld.createEntity();
				auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
				auto& physComp = objectEntity.addComponent<PhysicsComponent>();
				auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();

				b2Vec2 anchor(x, float32(yVal) - 0.5f);
				jd.Initialize(prevBody, body, anchor);
				m_world.CreateJoint(&jd);

				physComp.physicsBody = body;

				objectEntity.activate();
				prevBody = body;
			}

			m_ropeDef.localAnchorB.SetZero();

			float32 extraLength = 0.01f;
			m_ropeDef.maxLength = N - 1.0f + extraLength;
			m_ropeDef.bodyB = prevBody;
		}

		{
			m_ropeDef.bodyA = ground;
			m_rope = m_world.CreateJoint(&m_ropeDef);
		}
		return prevBody;
	}

};

Rope::Rope(b2World& box2dWorld, anax::World& anaxWorld) :
		m_impl(new RopeImpl(box2dWorld, anaxWorld)) {

}

Rope::~Rope() {
}

b2Body* Rope::createRope() {
	return m_impl->createRope();
}
