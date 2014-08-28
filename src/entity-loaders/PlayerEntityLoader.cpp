#include <entity-loaders/PlayerEntityLoader.h>

void PlayerEntityLoader::loadEntity(anax::World& anaxWorld, B2DWorld& b2dWorld, lua_State* myLuaState) {

	luabind::module(myLuaState)[
	luabind::class_<PhysicsComponent>("PhysicsComponent")
	      .def(luabind::constructor<>())
	      .def_readwrite("previousAngle", &PhysicsComponent::previousAngle)
	      .def_readwrite("previousPosition", &PhysicsComponent::previousPosition)
	];


    auto playerEntity = anaxWorld.createEntity();
    auto& texCoordsComp = playerEntity.addComponent<Texcoords>();
    auto& playerStateComp = playerEntity.addComponent<PlayerStateComponent>();
    //auto& textureRectComp = m_player.addComponent<TextureRectComponent>();
    auto& physComp = playerEntity.addComponent<PhysicsComponent>();

    std::vector<b2Vec2> texCoords;
    texCoords.push_back(b2Vec2(0.0f, 1.f));
    texCoords.push_back(b2Vec2(1.0f, 1.0f));
    texCoords.push_back(b2Vec2(1.0f, 0.0f));
    texCoords.push_back(b2Vec2(0.0f, 0.0f));

    texCoordsComp.textCoords = texCoords;

    B2BoxBuilder builder(20,20);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(30,30))
    .setDensity(2.0f);
    b2Body* playerBody = b2dWorld.createB2Body(&builder);
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
	    luabind::call_function<void>(myLuaState, "loadPlayerComponent", &physComp);
	} catch (luabind::error& e) {
	    std::string error = lua_tostring(e.state(), -1);
	    std::cout << error << std::endl;
	}

	std::cout << physComp.previousPosition.x << std::endl;
	playerEntity.activate();
}
