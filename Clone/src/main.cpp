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

//    b2Vec2 gravity(0.0f, -10.0f);
//    b2World world(gravity);
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(0.0f, 4.0f);
//    b2Body* body = world.CreateBody(&bodyDef);
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.0f, 10.0f);
//    body->CreateFixture(&groundBox, 0.0f);

    B2DWorld box2DWorld(-9.8f);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);
    B2BodyBuilder builder(&boxShape);
    builder
        .bodyType(b2_dynamicBody)
        .bodyType(b2_dynamicBody)
        .setPosition(b2Vec2(10,10))
        .setDensity(1.0f)
        .setFriction(0.3f);



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

        // Clear screen
        App.clear();

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
