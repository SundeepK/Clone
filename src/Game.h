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


class Game {

	public:

		Game(b2World& box2dWorld, sf::RenderWindow& renderWindow);
		virtual ~Game();

		 void loadMap(tmx::MapLoader& levelLoader,b2World* b2world);
		 void init();
		 void update(float deltaTime);
		 void render();

	private:
		 std::unique_ptr<b2World> m_b2world;
		 std::unique_ptr<sf::RenderWindow> m_mainRenderWindow;
		 PhysicsTimeStepSystem m_fixedTimeStepSystem;
		 tmx::MapLoader m_mapLoader;
		 TmxBox2dLevelLoader m_tmxLevelLoader;

		 anax::World m_anaxWorld;
		 anax::Entity m_player;
		 PlayerControlsSystem m_playerControlsSystem;
		 TextureRectRenderSystem m_textureRectSystem;
		 OpenGLTextureRenderer m_openglTextureRenderer;
		 PhysicsInterpolatorSystem m_physicsInterpolator;
		 CameraSystem m_cameraSystem;
		 std::vector<b2Vec2> m_texs;
		 ActionController<PlayerState, TemplateHasher<PlayerState>, b2Body*> m_actionController;
		 WorldEntityLoader m_entityLoader;
		 PlayerAnimationSystem m_playerAnimationSystem;
		 std::vector<tmx::MapLayer> layers;
		 std::unique_ptr<std::vector<b2Vec2*>> arrays;
		 sf::View m_view;

};

#endif /* GAME_H_ */
