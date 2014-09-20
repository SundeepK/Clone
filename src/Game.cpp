#include <Game.h>
#include "B2BoxBuilder.h"
#include <functional>

Game::Game(b2World& box2dWorld, sf::RenderWindow& renderWindow) :m_b2world(&box2dWorld), m_mainRenderWindow(&renderWindow),
		m_fixedTimeStepSystem(box2dWorld), m_mapLoader("maps/"), m_tmxLevelLoader(m_mapLoader), m_cameraSystem(1280, 800) {
}

Game::~Game() {
}

void Game::init()
{


	m_entityLoader.loadWorldEntities(m_anaxWorld, *m_b2world);
	m_tmxLevelLoader.loadLevel("level-1-test.tmx", *m_b2world);

	m_anaxWorld.addSystem(m_playerControlsSystem);
	m_anaxWorld.addSystem(m_textureRectSystem);
	m_anaxWorld.addSystem(m_openglTextureRenderer);
	m_anaxWorld.addSystem(m_physicsInterpolator);
	m_anaxWorld.addSystem(m_playerAnimationSystem);
	m_anaxWorld.addSystem(m_cameraSystem);

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
    m_anaxWorld.refresh();
  //  m_actionController.update(*m_mainRenderWindow.get());
  //  m_playerControlsSystem.update(deltaTime);
  //  m_box2dWorld.step(deltaTime);
    m_fixedTimeStepSystem.update(deltaTime, m_physicsInterpolator, m_playerControlsSystem);
    m_cameraSystem.update();
    m_playerAnimationSystem.update(deltaTime);

}

void Game::render() {
//	m_mainRenderWindow->pushGLStates();
//	m_mainRenderWindow->clear(sf::Color::Black);
//	m_mainRenderWindow->popGLStates();
//
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
	m_mainRenderWindow->draw(m_cameraSystem);
	m_mainRenderWindow->draw(m_mapLoader);
	m_textureRectSystem.render(m_mainRenderWindow.get());
	m_fixedTimeStepSystem.drawDebug();


}
