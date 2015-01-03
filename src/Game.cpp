#include <Game.h>
#include "B2BoxBuilder.h"
#include <functional>

Game::Game(b2World& box2dWorld, sf::RenderWindow& renderWindow) :m_b2world(&box2dWorld), m_mainRenderWindow(&renderWindow),
		m_fixedTimeStepSystem(box2dWorld), m_mapLoader("maps/"), m_tmxLevelLoader(m_mapLoader, box2dWorld, m_anaxWorld, m_sensorSystem), m_cameraSystem(m_mainRenderWindow->getSize().x,m_mainRenderWindow->getSize().y), m_view(sf::FloatRect(0,0, 1280, 800)),
		m_b2Dsplitter(box2dWorld, m_anaxWorld), m_mouseSplitterSystem(m_b2Dsplitter), m_playerControlsSystem(), m_levelEndDetectSystem(m_tmxLevelLoader), m_breakableJointSystem(box2dWorld){
	box2dWorld.SetContactListener(&m_sensorSystem);
}

Game::~Game() {
}

void Game::init()
{

	m_sensorSystem.registerb2ContactListener(&m_tmxLevelLoader);
	m_sensorSystem.registerb2ContactListener(&m_breakableJointSystem);

	m_tmxLevelLoader.loadNextLevel();

	m_anaxWorld.addSystem(m_playerControlsSystem);
	m_anaxWorld.addSystem(m_animationSystem);
	m_anaxWorld.addSystem(m_openglTextureRenderer);
	m_anaxWorld.addSystem(m_physicsInterpolator);
	m_anaxWorld.addSystem(m_playerAnimationSystem);
	m_anaxWorld.addSystem(m_cameraSystem);
	m_anaxWorld.addSystem(m_b2Dsplitter);
	m_anaxWorld.addSystem(m_mouseSplitterSystem);
	m_anaxWorld.addSystem(m_sensorSystem);
	m_anaxWorld.addSystem(m_levelEndDetectSystem);
	m_anaxWorld.addSystem(m_breakableJointSystem);

	//m_anaxWorld.addSystem(m_filterCollisionsSystem);


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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
//    m_filterCollisionsSystem.filterCollisions();
	m_anaxWorld.refresh();
  //  m_actionController.update(*m_mainRenderWindow.get());
  //  m_playerControlsSystem.update(deltaTime);
  //  m_box2dWorld.step(deltaTime);
    m_fixedTimeStepSystem.update(events, deltaTime, m_physicsInterpolator, m_playerControlsSystem);
    m_b2Dsplitter.refreshEntityBodyTypes();
    m_cameraSystem.update(*m_mainRenderWindow, m_tmxLevelLoader.getMapSize());
    m_playerAnimationSystem.update(deltaTime);
    m_tmxLevelLoader.update();
    m_levelEndDetectSystem.processEndLevel();
    m_breakableJointSystem.update(1/deltaTime);
}

void Game::render() {

	//TODO draw opengl stuff here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_openglTextureRenderer.render();

	//TODO sfml stuff here
	glPushAttrib(GL_CURRENT_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
	TextureLoader::checkError("glPushAttrib");
   	glPushMatrix();

	m_mainRenderWindow->resetGLStates();
	m_mainRenderWindow->draw(m_cameraSystem);
	m_mainRenderWindow->draw(m_mapLoader);
//	m_mainRenderWindow->draw(m_animationSystem);
	m_mainRenderWindow->draw(m_mouseSplitterSystem);
	m_fixedTimeStepSystem.drawDebug();

	glPopAttrib();
	glPopMatrix();

	m_mainRenderWindow->display();

}
