#include <lua-exports/ExportBox2d.h>
#include <Box2D/Box2D.h>
#include <lua-exports/B2WorldProxy.h>
#include <game-objects/GameObjectTag.h>
#include <utilities/Bitwise.h>

class ExportBox2d::ExportBox2dImpl{

public:

	ExportBox2dImpl(){}
	~ExportBox2dImpl(){}

	 void exportToLua(lua_State *luaState){


			luabind::module(luaState)[
			luabind::class_<b2Vec2>("b2Vec2")
				.def(luabind::constructor<float32, float32>())
		 	   	.def_readwrite("x", &b2Vec2::x)
		 	   	.def_readwrite("y", &b2Vec2::y)
			];

			luabind::module(luaState)[
			luabind::class_<std::vector<b2Vec2>>("vectorOfb2Vec2")
				 .def(luabind::constructor<>())
				 .def("push_back",  static_cast<void (std::vector<b2Vec2>::*)(const b2Vec2&)>(&std::vector<b2Vec2>::push_back))
			];

		 luabind::module(luaState)[
		 		luabind::class_<b2BodyType>("b2BodyType")
		 		        .enum_("constants")
		 		        [
		 		         luabind::value("b2_staticBody", b2_staticBody),
		 		         luabind::value("b2_kinematicBody", b2_kinematicBody),
		 		         luabind::value("b2_dynamicBody", b2_dynamicBody)
		 		        ]
		 	];


		 luabind::module(luaState)[
		 		luabind::class_<GameObjectTag>("GameObjectTag")
		 		        .enum_("constants")
		 		        [
		 		         luabind::value("DYNAMIC_OBJECT", GameObjectTag::DYNAMIC_OBJECT),
		 		         luabind::value("SWITCH", GameObjectTag::SWITCH),
		 		         luabind::value("ROPE_BOX", GameObjectTag::ROPE_BOX)
		 		        ]
		 	];

		 	luabind::module(luaState)[
		 		luabind::class_<b2JointType>("b2JointType")
		 		        .enum_("constants")
		 		        [
		 		         luabind::value("e_unknownJoint", e_unknownJoint),
		 		         luabind::value("e_revoluteJoint", e_revoluteJoint),
		 		         luabind::value("e_prismaticJoint", e_prismaticJoint),
		 				 luabind::value("e_distanceJoint", e_distanceJoint),
		 				 luabind::value("e_pulleyJoint", e_pulleyJoint),
		 				 luabind::value("e_mouseJoint", e_mouseJoint),
		 			     luabind::value("e_gearJoint", e_gearJoint),
		 				 luabind::value("e_wheelJoint", e_wheelJoint),
		 				 luabind::value("e_weldJoint", e_weldJoint),
		 				 luabind::value("e_frictionJoint", e_frictionJoint),
		 				 luabind::value("e_ropeJoint", e_ropeJoint),
		 				 luabind::value("e_frictionJoint", e_frictionJoint),
		 				 luabind::value("e_motorJoint", e_motorJoint)

		 		        ]
		 	];

		 	luabind::module(luaState)[
		 			 		luabind::class_<b2Contact>("b2Contact")
		 			 	    .def("GetFixtureA", (const b2Fixture* (b2Contact::*) () const) &b2Contact::GetFixtureA)
		 			 	    .def("GetFixtureB", (const b2Fixture* (b2Contact::*) () const) &b2Contact::GetFixtureB)
		 				    .def("GetFixtureAConst", ( b2Fixture* (b2Contact::*) () ) &b2Contact::GetFixtureA)
		 					.def("GetFixtureBConst", ( b2Fixture* (b2Contact::*) () ) &b2Contact::GetFixtureB)
		 			 	    .def("GetFriction", (float32 (b2Contact::*) () const) &b2Contact::GetFriction)

		 	];


		 	luabind::module(luaState)[
			 			 luabind::class_<b2Fixture>("b2Fixture")
			 			 .def("GetBody", (b2Body* (b2Fixture::*) ()) &b2Fixture::GetBody)
			 			 .def("GetBodyConst", (const b2Body* (b2Fixture::*) () const) &b2Fixture::GetBody)
			 			 .def("CreateFixture", (bool (b2Fixture::*) () const) &b2Fixture::IsSensor)
		 			 	 .def("GetFilterData", (const b2Filter& (b2Fixture::*) () const) &b2Fixture::GetFilterData)
			 	];


		 	luabind::module(luaState)[
		 		luabind::class_<b2Body>("b2Body")
		 	    .def("CreateFixture", (b2Fixture* (b2Body::*) (const b2FixtureDef* def)) &b2Body::CreateFixture)
		 	    .def("CreateFixture", (b2Fixture* (b2Body::*) (const b2Shape* shape, float32 density)) &b2Body::CreateFixture)
		 	    .def("DestroyFixture", (void (b2Body::*) (b2Fixture* fixture)) &b2Body::DestroyFixture)
		 	    .def("SetTransform", (void (b2Body::*) (const b2Vec2& position, float32 angle)) &b2Body::SetTransform)
		 	    .def("GetTransform", &b2Body::GetTransform)
		 	    .def("GetPosition", (const b2Vec2& (b2Body::*) ()) &b2Body::GetPosition)
		 	    .def("GetAngle", (float32 (b2Body::*) ()) &b2Body::GetAngle)
		 	    .def("GetWorldCenter", (const b2Vec2&  (b2Body::*) ()) &b2Body::GetWorldCenter)
		 	    .def("GetLocalCenter", (const b2Vec2&  (b2Body::*) ()) &b2Body::GetLocalCenter)
		 	    .def("SetLinearVelocity", (void (b2Body::*) (const b2Vec2& v)) &b2Body::SetLinearVelocity)
		 	    .def("GetLinearVelocity", (const b2Vec2& (b2Body::*) ()) &b2Body::GetWorldCenter)
		 	    .def("GetAngularVelocity", (float32 (b2Body::*) ()) &b2Body::GetAngularVelocity)
		 	    .def("ApplyForce", (void (b2Body::*) (const b2Vec2& force, const b2Vec2& point, bool wake)) &b2Body::ApplyForce)
		 	    .def("ApplyForceToCenter", (void (b2Body::*) (const b2Vec2& force, bool wake)) &b2Body::ApplyForceToCenter)
		 	    .def("ApplyTorque", (void (b2Body::*) (float32 torque, bool wake)) &b2Body::ApplyTorque)
		 	    .def("ApplyLinearImpulse", (void (b2Body::*) (const b2Vec2& impulse, const b2Vec2& point, bool wake)) &b2Body::ApplyLinearImpulse)
		 	    .def("ApplyAngularImpulse", (void (b2Body::*) (float32 impulse, bool wake)) &b2Body::ApplyAngularImpulse)
		 	    .def("GetMass", (float32 (b2Body::*) ()) &b2Body::GetMass)
		 	    .def("GetMassData", (void (b2Body::*) (b2MassData* data)) &b2Body::GetMassData)
		 	    .def("SetMassData", (float32 (b2Body::*) (const b2MassData* data)) &b2Body::SetMassData)
		 	    .def("ResetMassData", (float32 (b2Body::*) ()) &b2Body::ResetMassData)
		 	    .def("GetWorldPoint", (b2Vec2 (b2Body::*) (const b2Vec2& localPoint)) &b2Body::GetWorldPoint)
		 	    .def("GetWorldVector", (float32 (b2Body::*) ()) &b2Body::GetWorldVector)
		 	    .def("GetInertia", (b2Vec2 (b2Body::*) (const b2Vec2& localVector)) &b2Body::GetInertia)
		 	    .def("GetLocalPoint", (b2Vec2 (b2Body::*) (const b2Vec2& worldPoint)) &b2Body::GetLocalPoint)
		 	    .def("GetLocalVector", (b2Vec2 (b2Body::*) (const b2Vec2& worldVector)) &b2Body::GetLocalVector)
		 	    .def("GetLinearVelocityFromWorldPoint", (b2Vec2 (b2Body::*) (const b2Vec2& worldPoint)) &b2Body::GetLinearVelocityFromWorldPoint)
		 	    .def("GetLinearVelocityFromLocalPoint", (b2Vec2 (b2Body::*) (const b2Vec2& localPoint)) &b2Body::GetLinearVelocityFromLocalPoint)
		 	    .def("GetLinearDamping", (float32 (b2Body::*) ()) &b2Body::GetLinearDamping)
		 	    .def("SetLinearDamping", (void (b2Body::*) (float32 linearDamping)) &b2Body::SetLinearDamping)
		 	    .def("GetAngularDamping", (float32 (b2Body::*) ()) &b2Body::GetAngularDamping)
		 	    .def("SetAngularDamping", (void (b2Body::*) (float32 angularDamping)) &b2Body::SetAngularDamping)
		 	    .def("GetGravityScale", (float32 (b2Body::*) ()) &b2Body::GetGravityScale)
		 	    .def("SetGravityScale", (void (b2Body::*) (float32 scale)) &b2Body::SetGravityScale)
		 	    .def("SetType", (void (b2Body::*) (b2BodyType type)) &b2Body::SetType)
		 	    .def("GetType", (float32 (b2Body::*) ()) &b2Body::GetType)
		 	    .def("GetInertia", (b2BodyType (b2Body::*) ()) &b2Body::GetInertia)
		 	    .def("SetBullet", (void (b2Body::*) (bool flag)) &b2Body::SetBullet)
		 	    .def("IsBullet", (bool (b2Body::*) ()) &b2Body::IsBullet)
		 	    .def("SetSleepingAllowed", (void (b2Body::*) (bool flag)) &b2Body::SetSleepingAllowed)
		 	    .def("IsSleepingAllowed", (bool (b2Body::*) ()) &b2Body::IsSleepingAllowed)
		 	    .def("SetAwake", (void (b2Body::*) (bool flag)) &b2Body::SetAwake)
		 	    .def("IsAwake", (bool (b2Body::*) ()) &b2Body::IsAwake)
		 	    .def("SetActive", (b2BodyType (b2Body::*) (bool flag)) &b2Body::SetActive)
		 	    .def("IsActive", (bool (b2Body::*) ()) &b2Body::IsActive)
		 	    .def("SetFixedRotation", (void (b2Body::*) (bool flag)) &b2Body::SetFixedRotation)
		 	    .def("IsFixedRotation", (bool (b2Body::*) ()) &b2Body::IsFixedRotation)
		 	    .def("GetFixtureList", ( b2Fixture* (b2Body::*) ()) &b2Body::GetFixtureList)
		 	    .def("GetJointList", ( b2JointEdge* (b2Body::*) ()) &b2Body::GetJointList)
		 	    .def("GetContactList", ( b2ContactEdge* (b2Body::*) ()) &b2Body::GetContactList)
		 	    .def("Dump", ( void  (b2Body::*) ()) &b2Body::Dump)
		 	];

		 	luabind::module(luaState)[
			 		luabind::class_<Bitwise>("Bitwise")
			 	    .def(luabind::constructor<>())
			 	    .def("band", (uint16 (Bitwise::*) (uint16 a, uint16 b)) &Bitwise::band)
			 	];

		 	luabind::module(luaState)[
		 		luabind::class_<b2World>("b2World")
		 	    .def(luabind::constructor<const b2Vec2&>())
		 	    .def_readwrite("CreateBody", (b2Body* (b2World::*) (const b2BodyDef* def)) &b2World::CreateBody)
		 	    .def_readwrite("DestroyBody", (void (b2World::*) (b2Body* body)) &b2World::DestroyBody)
		 	    .def_readwrite("CreateJoint", (b2Joint* (b2World::*) (const b2JointDef* def)) &b2World::CreateJoint)
		 	    .def_readwrite("DestroyJoint", (void (b2World::*) (b2Joint* joint)) &b2World::DestroyJoint)
		 	];

		 	luabind::module(luaState)[
		 		luabind::class_<B2WorldProxy>("B2WorldProxy")
		 	    .def(luabind::constructor<b2World&>())
		 	    .def("createNewBody", (b2Body* (B2WorldProxy::*) (b2BodyDef& bodyDef, b2PolygonShape& shape, b2FixtureDef& fixture)) &B2WorldProxy::createNewBody)
		 	    .def("createJoint", (void (B2WorldProxy::*) (b2RevoluteJointDef& joint)) &B2WorldProxy::createJoint)
		 	    .def("ropeJoint", (void (B2WorldProxy::*) (b2RopeJointDef& joint)) &B2WorldProxy::ropeJoint)
		 	    .def("UuidOf", (std::string (B2WorldProxy::*) (b2Body* body)) &B2WorldProxy::UuidOf)
		 	    .def("addFixture", (b2Fixture* (B2WorldProxy::*) (b2Body* body, b2PolygonShape& shape, b2FixtureDef& fixture)) &B2WorldProxy::addFixture)

		 	];

		 	luabind::module(luaState)[
		 		luabind::class_<b2JointDef>("b2JointDef")
		 	    .def(luabind::constructor<>())
		 	    .def_readwrite("type", &b2JointDef::type)
		 	   	.def_readwrite("bodyA", &b2JointDef::bodyA)
		 	   	.def_readwrite("bodyA", &b2JointDef::bodyB)
		 	   	.def_readwrite("collideConnected", &b2JointDef::collideConnected)

		 	];

		 	luabind::module(luaState)[
		 		luabind::class_<b2RevoluteJointDef, b2JointDef>("b2RevoluteJointDef")
		 	    .def(luabind::constructor<>())
		 	    .def_readwrite("localAnchorA", &b2RevoluteJointDef::localAnchorA)
		 	   	.def_readwrite("localAnchorB", &b2RevoluteJointDef::localAnchorB)
		 	   	.def_readwrite("referenceAngle", &b2RevoluteJointDef::referenceAngle)
		 	   	.def_readwrite("enableLimit", &b2RevoluteJointDef::enableLimit)
		 	   	.def_readwrite("lowerAngle", &b2RevoluteJointDef::lowerAngle)
		 	    .def_readwrite("upperAngle", &b2RevoluteJointDef::upperAngle)
		 	    .def_readwrite("enableMotor", &b2RevoluteJointDef::enableMotor)
		 	    .def_readwrite("motorSpeed", &b2RevoluteJointDef::motorSpeed)
		 	    .def_readwrite("maxMotorTorque", &b2RevoluteJointDef::maxMotorTorque)
		 	    .def("Initialize", (void (b2RevoluteJointDef::*) (b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor)) &b2RevoluteJointDef::Initialize)

		 	];



		 	luabind::module(luaState)[
		 		luabind::class_<b2Filter>("b2Filter")
		 	    .def(luabind::constructor<>())
		 	    .def_readwrite("categoryBits", &b2Filter::categoryBits)
		 	   	.def_readwrite("maskBits", &b2Filter::maskBits)
		 	   	.def_readwrite("groupIndex", &b2Filter::groupIndex)
		 	];

		 	luabind::module(luaState)[
		 		luabind::class_<b2RopeJointDef, b2JointDef>("b2RopeJointDef")
		 	    .def(luabind::constructor<>())
		 	    .def_readwrite("localAnchorA", &b2RopeJointDef::localAnchorA)
		 	   	.def_readwrite("localAnchorB", &b2RopeJointDef::localAnchorB)
		 	   	.def_readwrite("maxLength", &b2RopeJointDef::maxLength)
		 	];


		 	luabind::module(luaState)[
		 	    luabind::class_<b2Shape>("b2Shape"),
		 		luabind::class_<b2PolygonShape, b2Shape>("b2PolygonShape")
		 	    .def(luabind::constructor<>())
		 	    .def("GetChildCount", &b2PolygonShape::GetChildCount)
		 	    .def("SetAsBox", (void (b2PolygonShape::*) (float32 hx, float32 hy) ) &b2PolygonShape::SetAsBox)
		 	    .def("SetAsBox", (void (b2PolygonShape::*) (float32 hx, float32 hy, const b2Vec2& center, float32 angle) ) &b2PolygonShape::SetAsBox)
		 	    .def("TestPoint", (void (b2PolygonShape::*) (const b2Transform& transform, const b2Vec2& p) ) &b2PolygonShape::TestPoint)
		 	    .def("ComputeAABB", (void (b2PolygonShape::*) (b2AABB* aabb, const b2Transform& transform, int32 childIndex) ) &b2PolygonShape::ComputeAABB)
		 	    .def("GetVertexCount", (void (b2PolygonShape::*) () ) &b2PolygonShape::GetVertexCount)
		 	    .def("GetVertex", (const b2Vec2& (b2PolygonShape::*) (int32 index) ) &b2PolygonShape::GetVertexCount)
		 	    .def("Validate", &b2PolygonShape::Validate)
		     ];

		 	luabind::module(luaState)[
		 		luabind::class_<b2FixtureDef>("b2FixtureDef")
		 	    .def(luabind::constructor<>())
		 	    .def_readwrite("shape", &b2FixtureDef::shape)
		 	   	.def_readwrite("friction", &b2FixtureDef::friction)
		 	   	.def_readwrite("restitution", &b2FixtureDef::restitution)
		 	   	.def_readwrite("density", &b2FixtureDef::density)
		 	   	.def_readwrite("isSensor", &b2FixtureDef::isSensor)
		 	    .def_readwrite("filter", &b2FixtureDef::filter)
		 	];



		 	luabind::module(luaState)[
		 		luabind::class_<b2BodyDef>("b2BodyDef")
		 	      .def(luabind::constructor<>())
		 	      .def_readwrite("position", &b2BodyDef::position)
		 	      .def_readwrite("angle", &b2BodyDef::position)
		 	      .def_readwrite("linearVelocity", &b2BodyDef::linearVelocity)
		 	      .def_readwrite("angularVelocity", &b2BodyDef::angularVelocity)
		 	      .def_readwrite("linearDamping", &b2BodyDef::linearDamping)
		 	      .def_readwrite("angularDamping", &b2BodyDef::angularDamping)
		 	      .def_readwrite("allowSleep", &b2BodyDef::allowSleep)
		 	      .def_readwrite("awake", &b2BodyDef::awake)
		 	      .def_readwrite("fixedRotation", &b2BodyDef::fixedRotation)
		 	      .def_readwrite("bullet", &b2BodyDef::bullet)
		 	      .def_readwrite("type", &b2BodyDef::type)
		 	      .def_readwrite("active", &b2BodyDef::active)
		 	      .def_readwrite("gravityScale", &b2BodyDef::gravityScale)
		 	];

	}

};


ExportBox2d::ExportBox2d() : m_impl(new ExportBox2dImpl()) {

}

ExportBox2d::~ExportBox2d() {
}

void ExportBox2d::exportToLua(lua_State *luaState){
	m_impl->exportToLua(luaState);
}



