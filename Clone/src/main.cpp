#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "B2DWorld.h"


int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(1280, 800, desktop.bitsPerPixel), "Clone",sf::Style::Default, settings);

    //box
    B2DWorld box2DWorld(9.8f);
    SFMLB2dDebugDraw drawer(App);
    box2DWorld.setDebugDraw(drawer);
    drawer.SetFlags(b2Draw::e_shapeBit);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(((20.0f/2)/Box2DConstants::WORLD_SCALE),((20.0f/2)/Box2DConstants::WORLD_SCALE));
    B2BodyBuilder builder(&boxShape);
    builder
    .bodyType(b2_dynamicBody)
    .setPosition(b2Vec2(30,30))
    .setDensity(1.0f)
    .setFriction(0.3f);
    box2DWorld.createB2Body(builder);


    //ground
    b2PolygonShape groundShape;
    groundShape.SetAsBox(((50.0f/2)/Box2DConstants::WORLD_SCALE),((50.0f/2)/Box2DConstants::WORLD_SCALE));
    B2BodyBuilder groundShapebuilder(&groundShape);
    groundShapebuilder
    .bodyType(b2_staticBody)
    .setPosition(b2Vec2(0,700))
    .setDensity(1.0f)
    .setFriction(0.3f);
    box2DWorld.createB2Body(groundShapebuilder);

    sf::Clock deltaClock;


    float initialUpdateTime = deltaClock.getElapsedTime().asSeconds();

    // Start the game loop
    while (App.isOpen())
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                App.close();
            }
        }

        float currentTime = deltaClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - initialUpdateTime;
        initialUpdateTime = currentTime;

        // Clear screen
        App.clear();

        box2DWorld.update(deltaTime);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
