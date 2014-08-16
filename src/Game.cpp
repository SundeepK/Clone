#include <Game.h>
#include "B2BoxBuilder.h"
#include <functional>

Game::Game(sf::RenderWindow renderWindow) : m_box2DWorld(9.8f), m_mainRenderWindow(renderWindow) {

}

Game::~Game() {
}

void Game::init()
{

	SFMLB2dDebugDraw drawer(App);
	m_box2DWorld.setDebugDraw(drawer);
    drawer.SetFlags(b2Draw::e_shapeBit);

    m_world.addSystem(m_playerControlsSystem);

    m_player = m_world.createEntity();
    auto& textureRectComp = m_player.addComponent<TextureRectComponent>();
    auto& physComp = m_player.addComponent<PhysicsComponent>();

    B2BoxBuilder builder(20,20);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(30,30))
    .setDensity(1.0f);
    b2Body* playerBody = m_box2DWorld.createB2Body(&builder);
    playerBody->ApplyLinearImpulse( b2Vec2(0.1f,0.1f), playerBody->GetWorldCenter(), true);
    playerBody->SetBullet(true);

    physComp.physicsBody = playerBody;

    sf::RectangleShape rect(sf::Vector2f(20,20));
    rect.setPosition(sf::Vector2f(playerBody->GetPosition().x,playerBody->GetPosition().y));

    sf::Texture texture;
    if (!texture.loadFromFile("1.png")) {}

    textureRectComp.rect = rect;
    textureRectComp.texture = texture;
    rect.setTexture(&textureRectComp.texture);


    //TODO below should be removed once parsing tile-maps
    //ground
    B2BoxBuilder groundShapebuilder(1200, 50);
    groundShapebuilder
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(0,700))
    .setDensity(1.0f);
     m_box2DWorld.createB2Body(&groundShapebuilder);

    B2BoxBuilder left(50, 700);
    left
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(0,0))
    .setDensity(1.0f);
    m_box2DWorld.createB2Body(&left);

    B2BoxBuilder right(50, 700);
    right
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(1200,0))
    .setDensity(1.0f);
    m_box2DWorld.createB2Body(&right);


    m_player.activate();
}

void Game::update(float deltaTime) {
    m_world.refresh();
    m_box2DWorld.update(1.0f/60.0f);
    m_playerControlsSystem.update(deltaTime);
}

void Game::render() {

}
