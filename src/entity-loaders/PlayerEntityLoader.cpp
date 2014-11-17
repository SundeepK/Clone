#include <entity-loaders/PlayerEntityLoader.h>

void PlayerEntityLoader::loadEntity(anax::World& anaxWorld, b2World& b2dWorld, std::unordered_map<std::string, tmx::MapObject>& loadedMapData, lua_State* luaState) {

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

    //auto& textureRectComp = m_player.addComponent<TextureRectComponent>();
    auto& physComp = playerEntity.addComponent<PhysicsComponent>();
    auto& playerTagComp = playerEntity.addComponent<PlayerTagComponent>();
  //  auto& fixtureMap = playerEntity.addComponent<FixtureMapComponent>();

    auto startPositionVec = loadedMapData["PlayerStartPoint"].GetPosition();
    std::cout << "player start pos x:" << startPositionVec.x << " y: " << startPositionVec.y << std::endl;
    B2BoxBuilder builder(30,40);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(startPositionVec.x,startPositionVec.y))
    .fixedRotation(true)
    .setRestitution(0.0f)
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

    rightShape.SetAsBox(0.1, 0.6, b2Vec2(0.6,0), 0);
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

    leftSensor.density = 0.3;
    leftSensor.restitution = 0.0f;
    leftSensor.friction = 10.0f;
    leftShape.SetAsBox(0.1, 0.6, b2Vec2(-0.6,0), 0);
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
	    luabind::call_function<void>(luaState, "loadPhysicsComp", &physComp);
	   // luabind::call_function<void>(luaState, "loadTexCoords", &texCoordsComp);
	    luabind::call_function<void>(luaState, "loadAnimations", &animationComp);
	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	animationComp.loadSpriteSheet("Spritesheet.PNG");

//	animationComp.animator.playAnimation("walkRight", true);

	playerEntity.activate();
}
