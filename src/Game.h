#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>


#include <anax/anax.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <systems/PlayerControlsSystem.h>
#include <systems/TextureRectRenderSystem.h>
#include <systems/CameraSystem.h>
#include <components/Texcoords.h>
#include <PhysicsTimeStepSystem.h>
#include <memory.h>
#include <components/PlayerStateComponent.h>
#include <systems/OpenGLTextureRenderer.h>
#include <chrono>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>
#include <vector>
#include <ActionController.h>
#include <entity-loaders/WorldEntityLoader.h>
#include <systems/PlayerAnimationSystem.h>
#include <levels/TmxBox2dLevelLoader.h>
#include <input-events/B2dSplitter.h>
#include <systems/MouseSplitterSystem.h>
#include <systems/SensorSystem.h>
#include <systems/DetectLevelEndSystem.h>
#include <systems/FilterCollisionsSystem.h>
#include <systems/BreakableJointSystem.h>
#include <systems/NinjaSenseDetector.h>
#include <systems/NinjaSenseEntityTagger.h>
#include <systems/NinjaSenseRemoverSystem.h>

class Game {

	public:

		Game(b2World& box2dWorld, sf::RenderWindow& renderWindow);
		virtual ~Game();

		 void loadMap(tmx::MapLoader& levelLoader,b2World* b2world);
		 void init();
		 void update(float deltaTime);
		 void render();

	private:
		 std::shared_ptr<b2World> m_b2world;
		 std::unique_ptr<sf::RenderWindow> m_mainRenderWindow;
		 PhysicsTimeStepSystem m_fixedTimeStepSystem;
		 tmx::MapLoader m_mapLoader;
		 TmxBox2dLevelLoader m_tmxLevelLoader;

		 anax::World m_anaxWorld;
		 anax::Entity m_player;
		 PlayerControlsSystem m_playerControlsSystem;
		 TextureRectRenderSystem m_animationSystem;
		 OpenGLTextureRenderer m_openglTextureRenderer;
		 PhysicsInterpolatorSystem m_physicsInterpolator;
		 CameraSystem m_cameraSystem;
		 std::vector<b2Vec2> m_texs;
		 ActionController<PlayerState, TemplateHasher<PlayerState>, b2Body*> m_actionController;
		 PlayerAnimationSystem m_playerAnimationSystem;
		 std::vector<tmx::MapLayer> layers;
		 std::unique_ptr<std::vector<b2Vec2*>> arrays;
		 sf::View m_view;
		 B2dSplitter m_b2Dsplitter;
		 MouseSplitterSystem m_mouseSplitterSystem;
		 SensorSystem m_sensorSystem;
		 DetectLevelEndSystem m_levelEndDetectSystem;
		 FilterCollisionsSystem m_filterCollisionsSystem;
		 BreakableJointSystem m_breakableJointSystem;
		 NinjaSenseEntityTagger m_ninjaSenseEntityTagger;
		 NinjaSenseDetector m_ninjaSenseDetector;
		 NinjaSenseRemoverSystem m_ninjaSenseRemoverSystem;


};

#endif /* GAME_H_ */
