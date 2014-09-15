#include <entity-loaders/PlayerEntityLoader.h>

void PlayerEntityLoader::loadEntity(anax::World& anaxWorld, b2World& b2dWorld, lua_State* luaState) {

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
    auto& texCoordsComp = playerEntity.addComponent<Texcoords>();
    auto& animationComp = playerEntity.addComponent<AnimationComponent>();
    auto& playerStateComp = playerEntity.addComponent<PlayerStateComponent>();
    //auto& textureRectComp = m_player.addComponent<TextureRectComponent>();
    auto& physComp = playerEntity.addComponent<PhysicsComponent>();
    auto& playerTagComp = playerEntity.addComponent<PlayerTagComponent>();

    B2BoxBuilder builder(20,20);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(30,30))
    .setDensity(2.0f);
    b2Body* playerBody = builder.build(b2dWorld);
    playerBody->ApplyLinearImpulse( b2Vec2(0.1f,0.1f), playerBody->GetWorldCenter(), true);
    playerBody->SetBullet(true);

    physComp.physicsBody = playerBody;

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
	    luabind::call_function<void>(luaState, "loadTexCoords", &texCoordsComp);
	    luabind::call_function<void>(luaState, "loadAnimations", &animationComp);
	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	animationComp.loadSpriteSheet("Spritesheet.PNG");

//	animationComp.animator.playAnimation("walkRight", true);

	playerEntity.activate();
}
