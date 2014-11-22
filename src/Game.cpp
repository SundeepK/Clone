#include <Game.h>
#include "B2BoxBuilder.h"
#include <functional>

Game::Game(b2World& box2dWorld, sf::RenderWindow& renderWindow) :m_b2world(&box2dWorld), m_mainRenderWindow(&renderWindow),
		m_fixedTimeStepSystem(box2dWorld), m_mapLoader("maps/"), m_tmxLevelLoader(m_mapLoader), m_cameraSystem(m_mainRenderWindow->getSize().x,m_mainRenderWindow->getSize().y), m_view(sf::FloatRect(0,0, 1280, 800)),
		m_b2Dsplitter(box2dWorld, m_anaxWorld), m_mouseSplitterSystem(m_b2Dsplitter), m_playerControlsSystem(){
	box2dWorld.SetContactListener(&m_sensorSystem);
}

Game::~Game() {
}

void Game::init()
{


	m_tmxLevelLoader.loadLevel("level-1.tmx", *m_b2world, m_anaxWorld);

	m_anaxWorld.addSystem(m_playerControlsSystem);
	m_anaxWorld.addSystem(m_textureRectSystem);
	m_anaxWorld.addSystem(m_openglTextureRenderer);
	m_anaxWorld.addSystem(m_physicsInterpolator);
	m_anaxWorld.addSystem(m_playerAnimationSystem);
	m_anaxWorld.addSystem(m_cameraSystem);
	m_anaxWorld.addSystem(m_b2Dsplitter);
	m_anaxWorld.addSystem(m_mouseSplitterSystem);
	m_anaxWorld.addSystem(m_sensorSystem);
	m_anaxWorld.addSystem(m_levelEndDetectSystem);



	glDisable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, m_mainRenderWindow->getSize().x,
			m_mainRenderWindow->getSize().y);

	glMatrixMode(GL_PROJECTION);
  //  gluPerspective( 90.0f, 1.0f, 1.0f, 1500.0f );
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


	std::vector<sf::Event> events;
    sf::Event event;
    while (m_mainRenderWindow->pollEvent(event))
    {
    	sf::Event e = event;
    	events.push_back(e);
    }

	sf::Vector2f p(m_cameraSystem.getView().getCenter());
	m_mouseSplitterSystem.processMouseEventsForSplitter(events, sf::Vector2f(p.x - 1280/2, p.y - 800/2));
    m_anaxWorld.refresh();

  //  m_actionController.update(*m_mainRenderWindow.get());
  //  m_playerControlsSystem.update(deltaTime);
  //  m_box2dWorld.step(deltaTime);
    m_fixedTimeStepSystem.update(events, deltaTime, m_physicsInterpolator, m_playerControlsSystem);
    m_b2Dsplitter.refreshEntityBodyTypes();
    m_cameraSystem.update();
    m_playerAnimationSystem.update(deltaTime);
    m_levelEndDetectSystem.processEndLevel();
}

void Game::render() {
	m_mainRenderWindow->setActive(true);

	//TODO draw more sfml stuff here
	m_mainRenderWindow->pushGLStates();
	m_mainRenderWindow->clear(sf::Color(50, 50, 50));
	m_mainRenderWindow->draw(m_cameraSystem);
	sf::Vector2f p(m_cameraSystem.getView().getViewport().left, m_cameraSystem.getView().getViewport().top);

	m_mainRenderWindow->draw(m_mapLoader);
	m_mainRenderWindow->draw(m_textureRectSystem);
	m_mainRenderWindow->draw(m_mouseSplitterSystem);
	m_fixedTimeStepSystem.drawDebug();
	m_mainRenderWindow->popGLStates();

	//TODO draw opengl stuff here
	glClear(GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
    m_cameraSystem.updateOpenglCamera();
	m_openglTextureRenderer.render();
	glPopMatrix();

}
