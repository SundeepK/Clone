#include <game-objects/Rope.h>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <components/SplitDirectionComponent.h>
#include <components/BreakableJointComponent.h>
#include <iostream>
#include <game-objects/GameObjectTag.h>
#include <math.h>
class Rope::RopeImpl{

public:
	RopeImpl(){}
	~RopeImpl(){}

	b2RopeJointDef m_ropeDef;


	b2Body* createStartingBody(b2Vec2 position,  b2World& box2dWorld){
		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = position;
		b2PolygonShape shape;
		shape.SetAsBox(0.1f, 0.1f);
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
		fd.filter.categoryBits = GameObjectTag::ROPE_SEGMENT;
		return fd;
	}

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		b2Vec2 statingPosition = tmx::SfToBoxVec(mapObject.GetPosition());
		b2Vec2 endPosition = tmx::SfToBoxVec(sf::Vector2f(mapObject.GetPosition().x + mapObject.GetAABB().width, mapObject.GetPosition().y));

		b2Body* firstBodyToJoinWith = createStartingBody(statingPosition, box2dWorld);
		b2Body* prevBody = firstBodyToJoinWith;
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.125f);

			b2FixtureDef fd  = getRopeFixture(shape);

			b2RevoluteJointDef jd;
			jd.collideConnected = false;

			const int32 N = ceilf((mapObject.GetAABB().width / 30) / (1.0f )) + 1;

			for (int32 xVal = 1; xVal < N; ++xVal) {
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(statingPosition.x + xVal , statingPosition.y );
				if (xVal == N - 1) {
					bd.type = b2_staticBody;
					shape.SetAsBox(0.1f, 0.1f);
					fd.density = 1.0f;
					bd.position.Set(endPosition.x, endPosition.y);
				}

				b2Body* body = box2dWorld.CreateBody(&bd);
				body->CreateFixture(&fd);

				auto objectEntity = anaxWorld.createEntity();
				auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
				auto& physComp = objectEntity.addComponent<PhysicsComponent>();
				auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();
				auto& breakableJointComp = objectEntity.addComponent<BreakableJointComponent>();
				breakableJointComp.maxWeight = 1 ;


				b2Vec2 anchor( statingPosition.x + xVal  , statingPosition.y );
				jd.Initialize(prevBody, body, anchor);
				box2dWorld.CreateJoint(&jd);

				physComp.physicsBody = body;

				objectEntity.activate();
				prevBody = body;
			}

		}



	}


};


Rope::Rope() : m_impl(new RopeImpl()) {

}

Rope::~Rope() {
}

void Rope::createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}
