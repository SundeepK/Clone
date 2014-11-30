#include <game-objects/Rope.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>

class Rope::RopeImpl {

public:
	RopeImpl() {
	}

	~RopeImpl() {
	}

	b2RopeJointDef m_ropeDef;
	b2Joint* m_rope;

	void createRope(b2World& m_world, anax::World& anaxWorld) {
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world.CreateBody(&bd);
			bd.position = b2Vec2(40.0f, 10.0f);
			b2EdgeShape shape;
			shape.Set(b2Vec2(40.0f, 10.0f), b2Vec2(80.0f, 10.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.125f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 20.0f;
			fd.friction = 0.2f;
			fd.filter.categoryBits = 0x0001;
			fd.filter.maskBits =  ~0x0003;

			b2RevoluteJointDef jd;
			jd.collideConnected = false;

			const int32 N = 30;
			const float32 y = 5.0f;
			m_ropeDef.localAnchorA.Set(0.0f, y);

			b2Body* prevBody = ground;
			for (int32 i = 20; i < N; ++i) {
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(0.5f + 1.0f * i, y);
				if (i == N - 1) {
					shape.SetAsBox(1.5f, 1.5f);
					fd.density = 1.0f;
					fd.filter.maskBits = 0x0003;
					bd.position.Set(1.0f * i, y);
					bd.linearDamping = 10.0f;
					bd.angularDamping = 100.0f;
				}

				b2Body* body = m_world.CreateBody(&bd);

				body->CreateFixture(&fd);

				auto objectEntity = anaxWorld.createEntity();
				auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
				auto& physComp = objectEntity.addComponent<PhysicsComponent>();
				auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();

				b2Vec2 anchor(float32(i), y);
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
	}

};

Rope::Rope() :
		m_impl(new RopeImpl()) {

}

Rope::~Rope() {
}

void Rope::createRope(b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createRope(box2dWorld, anaxWorld);
}
