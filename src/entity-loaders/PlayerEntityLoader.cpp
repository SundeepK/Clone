#include <entity-loaders/PlayerEntityLoader.h>
#include <components/EndPointCollisionTagComponent.h>
#include <lua-exports/ExportBox2d.h>
#include <boost/scoped_ptr.hpp>
#include <lua-exports/B2WorldProxy.h>

void PlayerEntityLoader::loadEntity(anax::World& anaxWorld, b2World& b2dWorld, std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* luaState) {

	if(luaL_dofile(luaState, "lua-configs/playerConfig.lua")){
        printf("%s\n", lua_tostring(luaState, -1));
	}

//	ExportBox2d exportBox2d;
//	exportBox2d.exportToLua(luaState);

	B2WorldProxy box2dWorldProxy(b2dWorld);

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
	    .def("SetLinearVelocity", (void (b2Body::*) (const b2Vec2& v)) &b2Body::GetLinearVelocity)
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
	];


	luabind::module(luaState)[
		luabind::class_<b2RevoluteJointDef>("b2RevoluteJointDef")
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

	luabind::module(luaState)[
	luabind::class_<PhysicsComponent>("PhysicsComponent")
	      .def(luabind::constructor<>())
	      .def_readwrite("previousAngle", &PhysicsComponent::previousAngle)
	      .def_readwrite("previousPosition", &PhysicsComponent::previousPosition)
	];

	luabind::module(luaState)[
	luabind::class_<Texcoords>("Texcoords")
	      .def(luabind::constructor<>())
	      .def_readwrite("textCoords", &Texcoords::textCoords)
	];

	luabind::module(luaState)[
	luabind::class_<sf::Time>("sf_Time")
	      .def(luabind::constructor<>())
		  .def("asSeconds",  &sf::Time::asSeconds)
	];

	luabind::module(luaState)[
	       luabind::def("sf_seconds", &sf::seconds)
	];

	luabind::module(luaState)[
	luabind::class_<thor::Animator<sf::Sprite, std::string>>("thor_Animator")
	      .def(luabind::constructor<>())
	      .def("addAnimation", &thor::Animator<sf::Sprite, std::string>::addAnimation)
	];

	luabind::module(luaState)[
	luabind::class_<sf::IntRect>("sf_IntRect")
	      .def(luabind::constructor<float32, float32, float32, float32>())
	];

	luabind::module(luaState)[
	luabind::class_<thor::FrameAnimation>("thor_FrameAnimation")
	      .def(luabind::constructor<>())
		  .def("addFrame",  &thor::FrameAnimation::addFrame)
	];

	luabind::module(luaState)[
	luabind::class_<AnimationComponent>("AnimationComponent")
	      .def(luabind::constructor<>())
	      .def("registerAnimation", &AnimationComponent::registerAnimation)
	      .def_readwrite("animator", &AnimationComponent::animator)
	];

	auto playerEntity = anaxWorld.createEntity();
//    auto& texCoordsComp = playerEntity.addComponent<Texcoords>();
    auto& animationComp = playerEntity.addComponent<AnimationComponent>();
    auto& playerStateComp = playerEntity.addComponent<PlayerStateComponent>();
    auto& sensorsComp = playerEntity.addComponent<Sensor>();
    auto& interestedInLevelEnd = playerEntity.addComponent<EndPointCollisionTagComponent>();

    //auto& textureRectComp = m_player.addComponent<TextureRectComponent>();
    auto& physComp = playerEntity.addComponent<PhysicsComponent>();
    auto& playerTagComp = playerEntity.addComponent<PlayerTagComponent>();
  //  auto& fixtureMap = playerEntity.addComponent<FixtureMapComponent>();

    auto startPositionVec = loadedMapData["PlayerStartPoint"].GetPosition();
   // std::cout << "player start pos x:" << startPositionVec.x << " y: " << startPositionVec.y << std::endl;

    uint16 playerBitMask = 0x0003;

    B2BoxBuilder builder(30,40);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(startPositionVec.x,startPositionVec.y))
    .fixedRotation(true)
    .setRestitution(0.0f)
    .setcategoryBits(playerBitMask)
    .setDensity(1.0f);
    b2Body* playerBody = builder.build(b2dWorld);
    playerBody->ApplyLinearImpulse( b2Vec2(0.1f,0.1f), playerBody->GetWorldCenter(), true);
    playerBody->SetBullet(true);

    physComp.physicsBody = playerBody;


    //foot sensor
    b2PolygonShape footShape;
    b2FixtureDef footSensor;
    footSensor.shape = &footShape;

    footSensor.density = 1;
    footSensor.restitution = 0.0f;
    footShape.SetAsBox(0.15, 0.15, b2Vec2(0,0.7), 0);
    footSensor.isSensor = true;
    footSensor.filter.categoryBits = playerBitMask;
    b2Fixture* footSensorFixture = physComp.physicsBody->CreateFixture(&footSensor);
    SensorComponent footSensorComp;
    footSensorComp.sensors = footSensorFixture;
    footSensorComp.tag = "FootSensor";
    sensorsComp.sensors.insert(std::pair<std::string,SensorComponent>("FootSensor", footSensorComp));


    //right sensor
    b2PolygonShape rightShape;
    b2FixtureDef rightSensor;
    rightSensor.shape = &rightShape;

    rightSensor.density = 0.3;
    rightSensor.restitution = 0.0f;
    rightSensor.friction = 10.0f;
    rightSensor.filter.categoryBits = playerBitMask;


    rightShape.SetAsBox(0.1, 0.3, b2Vec2(0.6,0), 0);
    rightSensor.isSensor = true;
    b2Fixture* rightSensorFixture = physComp.physicsBody->CreateFixture(&rightSensor);
    SensorComponent rightSensorComp;
    rightSensorComp.sensors = rightSensorFixture;
    rightSensorComp.tag = "RightSensor";
    sensorsComp.sensors.insert(std::pair<std::string,SensorComponent>("RightSensor", rightSensorComp));


    //left sensor
    b2PolygonShape leftShape;
    b2FixtureDef leftSensor;
    leftSensor.shape = &leftShape;
    leftSensor.filter.categoryBits = playerBitMask;

    leftSensor.density = 0.3;
    leftSensor.restitution = 0.0f;
    leftSensor.friction = 10.0f;
    leftShape.SetAsBox(0.1, 0.3, b2Vec2(-0.6,0), 0);
    leftSensor.isSensor = true;
    b2Fixture* leftSensorFixture = physComp.physicsBody->CreateFixture(&leftSensor);
    SensorComponent leftSensorComp;
    leftSensorComp.sensors = leftSensorFixture;
    leftSensorComp.tag = "LeftSensor";
    sensorsComp.sensors.insert(std::pair<std::string,SensorComponent>("LeftSensor", leftSensorComp));

    sf::RectangleShape rect(sf::Vector2f(20,20));
    rect.setPosition(sf::Vector2f(playerBody->GetPosition().x,playerBody->GetPosition().y));

//    sf::Texture texture;
//    if (!texture.loadFromFile("1.png")) {
//    	std::cout << "no 1.png found" << std::endl;
//    }
//
//    textureRectComp.rect = rect;
//    textureRectComp.texture = texture;
//    rect.setTexture(&textureRectComp.texture);

	try {
	    luabind::call_function<void>(luaState, "init", &box2dWorldProxy);
	    luabind::call_function<void>(luaState, "loadPhysicsComp", &physComp);
	   // luabind::call_function<void>(luaState, "loadTexCoords", &texCoordsComp);
	    luabind::call_function<void>(luaState, "loadAnimations", &animationComp);
	    luabind::call_function<void>(luaState, "testBox");


	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	animationComp.loadSpriteSheet("Spritesheet.PNG");

//	animationComp.animator.playAnimation("walkRight", true);

	playerEntity.activate();
}
