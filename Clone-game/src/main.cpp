#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "B2DWorld.h"
#include "B2BoxBuilder.h"
#include <functional>
#include <iostream>
#include "ActionController.h"
#include <string>

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
//    settings.antialiasingLevel = 4;
//    settings.majorVersion = 3;
//    settings.minorVersion = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(1280, 800,32), "Clone",sf::Style::Default, settings);
	App.setKeyRepeatEnabled(true);
//    App.setFramerateLimit(60);
////   App.setVerticalSyncEnabled(true);

    //box
    B2DWorld box2DWorld(9.8f);
    SFMLB2dDebugDraw drawer(App);
    box2DWorld.setDebugDraw(drawer);
    drawer.SetFlags(b2Draw::e_shapeBit);

    B2BoxBuilder builder(20,20);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(30,30))
    .setDensity(1.0f);
//    .setFriction(0.2f);
   b2Body* b = box2DWorld.createB2Body(&builder);
   b->ApplyLinearImpulse( b2Vec2(0.1f,0.1f), b->GetWorldCenter(), true);
    b->SetBullet(true);

    //ground
    B2BoxBuilder groundShapebuilder(1200, 50);
    groundShapebuilder
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(0,700))
    .setDensity(1.0f);
     box2DWorld.createB2Body(&groundShapebuilder);

    B2BoxBuilder left(50, 700);
    left
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(0,0))
    .setDensity(1.0f);
     box2DWorld.createB2Body(&left);

    B2BoxBuilder right(50, 700);
    right
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(1200,0))
    .setDensity(1.0f);
     box2DWorld.createB2Body(&right);




    ActionController<std::string> actionController;
    Action a (sf::Keyboard::Key::A);
    Action d(sf::Keyboard::Key::D);
    Action w (sf::Keyboard::Key::W);
    Action s (sf::Keyboard::Key::S);

    actionController["a"] = a ;
    actionController["d"] = d ;
    actionController["w"] = w ;
    actionController["s"] = s ;

    int count = 0;
    actionController.addCallback("a",  [&count, &b](float dt) -> void { if(b->GetLinearVelocity().x < -10.0f) {return ;}    b->ApplyLinearImpulse( b2Vec2(-0.4f,0.0f), b->GetWorldCenter(), true);});
    actionController.addCallback("d",  [&count, &b](float dt) -> void {  if(b->GetLinearVelocity().x > 10.0f) {return ;} b->ApplyLinearImpulse( b2Vec2( 0.4,0.0f), b->GetWorldCenter() ,  true);});
    actionController.addCallback("w",  [&count, &b](float dt) -> void {  b->ApplyLinearImpulse( b2Vec2(0.0f,-0.4), b->GetWorldCenter() ,  true);});
    actionController.addCallback("s",  [&count, &b](float dt) -> void {  b->ApplyLinearImpulse( b2Vec2(0.0f,0.4) , b->GetWorldCenter() , true);});


    	// wrap everything up into a struct
	PhysicsComponent *physicsTrack = new PhysicsComponent();
	physicsTrack->previousAngle = b->GetAngle();
	physicsTrack->previousPosition = b->GetPosition();
	physicsTrack->smoothedAngle = b->GetAngle();
	physicsTrack->smoothedPosition = b->GetPosition();
	b->SetUserData(physicsTrack);


    sf::RectangleShape rect(sf::Vector2f(20,20));
    rect.setPosition(sf::Vector2f(b->GetPosition().x,b->GetPosition().y));
    // Start the game loop

        sf::Clock deltaClock;

    float initialUpdateTime = deltaClock.getElapsedTime().asSeconds();
    double currentTime = deltaClock.getElapsedTime().asSeconds();
    double accumulator = 0.0;
    sf::RenderStates r(sf::BlendAdd);

sf::Texture texture;
        if (!texture.loadFromFile("1.png"))
        {}

    rect.setTexture(&texture);
    sf::VertexArray quad(sf::Quads, 4);

    while (App.isOpen())
    {

            App.clear();

        actionController.update(App);

        float currentTime = deltaClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - initialUpdateTime;
        initialUpdateTime = currentTime;

          if ( deltaTime > 0.25 )
        deltaTime = 0.25;


        box2DWorld.update(deltaTime, actionController, App);

        PhysicsComponent *c   = (PhysicsComponent*) b->GetUserData();
       rect.setPosition(sf::Vector2f(floor(b->GetPosition().x*30-10),floor(b->GetPosition().y*30-10)));
//        rect.setPosition(sf::Vector2f(floor(c->smoothedPosition.x*30-10),floor(c->smoothedPosition.y*30-10)));

//        for(int i=0;i<4;i++){
//                 b2Vec2 vec=((b2PolygonShape*)b->GetFixtureList()->GetShape())->GetVertex(i);
//                 vec = b->GetWorldPoint(vec);
//                 quad[i].position = sf::Vector2f(floor(vec.x*30),floor( vec.y*30));
//                 quad[i].color = sf::Color::White;
//        }
//
//        App.draw(quad);
        App.draw(rect);
        App.display();


    }
    delete physicsTrack;

}


