#include <Game.h>
#include "B2BoxBuilder.h"
#include <functional>

Game::Game(sf::RenderWindow& renderWindow) : m_mainRenderWindow(&renderWindow),  m_debugDrawer(renderWindow),
		m_box2DWorld(9.8f){
}

Game::~Game() {
}

void Game::init()
{
	m_componentLoader.loadWorldEntities(m_world, m_box2DWorld);
	m_box2DWorld.setDebugDraw(m_debugDrawer);
	m_debugDrawer.SetFlags(b2Draw::e_shapeBit);

	m_world.addSystem(m_playerControlsSystem);
	   m_world.addSystem(m_textureRectSystem);
	m_world.addSystem(m_openglTextureRenderer);
	m_world.addSystem(m_physicsInterpolator);
	m_world.addSystem(m_playerAnimationSystem);

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

	glDisable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, m_mainRenderWindow->getSize().x,
			m_mainRenderWindow->getSize().y);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 1280, 800, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);                  // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);             // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);

}

void Game::update(float deltaTime) {
    m_world.refresh();
  //  m_actionController.update(*m_mainRenderWindow.get());
  //  m_playerControlsSystem.update(deltaTime);
 //   m_box2DWorld.step(deltaTime);
    m_box2DWorld.update(deltaTime, m_physicsInterpolator, m_playerControlsSystem);
    m_playerAnimationSystem.update(deltaTime);

}

void Game::render() {
//	m_mainRenderWindow->pushGLStates();
//	m_mainRenderWindow->clear(sf::Color::Black);
//	m_mainRenderWindow->popGLStates();
//
////	m_box2DWorld.drawDebug();
//
	m_mainRenderWindow->setActive(true);
//
//	glClear(GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//    glColor3f(1.0f,1.0f,1.0f);
//
//	m_openglTextureRenderer.render();
//	m_mainRenderWindow->pushGLStates();
//	//TODO draw more sfml stuff here
//	m_mainRenderWindow->popGLStates();
	m_mainRenderWindow->clear(sf::Color(50, 50, 50));
	m_textureRectSystem.render(m_mainRenderWindow.get());
}
