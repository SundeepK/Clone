#include <game-objects/RopeBox.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <iostream>
#include <game-objects/GameObjectTag.h>

class RopeBox::RopeBoxImpl {

public:

	RopeBoxImpl()  {
	}

	~RopeBoxImpl() {
	}

	b2RopeJointDef m_ropeDef;


	b2Body* createGround(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = position;
		b2PolygonShape shape;
		shape.SetAsBox(2.0f, 0.5f);
		b2FixtureDef fd;
		fd.shape = &shape;
		b2Body* ground  = box2dWorld.CreateBody(&bd);
		ground->CreateFixture(&fd);
		return ground;
	}

	b2FixtureDef getRopeFixture(b2PolygonShape& shape){
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 20.0f;
		fd.friction = 0.2f;
		fd.filter.categoryBits = 0x0001;
		fd.filter.maskBits = 0xff - 0x0003;
		return fd;
	}

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		b2Vec2 position = tmx::SfToBoxVec(mapObject.GetPosition());
		b2Body* ground = createGround(position, box2dWorld);
		b2Body* prevBody = ground;
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.1f, 0.5f);

			b2FixtureDef fd  = getRopeFixture(shape);

			b2RevoluteJointDef jd;
			jd.collideConnected = false;

			const int32 N = 50;
			const float32 x = position.x;
			m_ropeDef.localAnchorA.Set(0.0f, x);

			for (int32 yVal = (position.y); yVal < N; ++yVal) {
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(x, yVal);
				if (yVal == N - 1) {
					shape.SetAsBox(1.5f, 1.5f);
					fd.density = 1.0f;
					fd.filter.categoryBits = GameObjectTag::ROPE_BOX;
					fd.filter.maskBits = GameObjectTag::DYNAMIC_OBJECT;
					bd.position.Set(x, yVal);
				}

				b2Body* body = box2dWorld.CreateBody(&bd);

				body->CreateFixture(&fd);

				auto objectEntity = anaxWorld.createEntity();
				auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
				auto& physComp = objectEntity.addComponent<PhysicsComponent>();
				auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();

				b2Vec2 anchor(x, float32(yVal) - 0.5f);
				jd.Initialize(prevBody, body, anchor);
				box2dWorld.CreateJoint(&jd);

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
			box2dWorld.CreateJoint(&m_ropeDef);
		}
	}

};

RopeBox::RopeBox() :
		m_impl(new RopeBoxImpl()) {

}

RopeBox::~RopeBox() {
}

void RopeBox::createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}
