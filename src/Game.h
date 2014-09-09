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
#include <components/Texcoords.h>
#include <B2DWorld.h>
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
#include <levels/Box2dLevelLoader.h>

class Game {

	public:

		Game(sf::RenderWindow& renderWindow, b2World& b2World, tmx::MapLoader& maploader);
		virtual ~Game();

		 void init();
		 void update(float deltaTime);
		 void render();

	private:
		 std::unique_ptr<sf::RenderWindow> m_mainRenderWindow;
		 b2World m_b2world;
		 SFMLB2dDebugDraw m_debugDrawer;
		 B2DWorld m_box2DWorld;
		 std::unique_ptr<tmx::MapLoader> m_mapLoader;
		 anax::World m_anaxWorld;
		 anax::Entity m_player;
		 PlayerControlsSystem m_playerControlsSystem;
		 TextureRectRenderSystem m_textureRectSystem;
		 OpenGLTextureRenderer m_openglTextureRenderer;
		 PhysicsInterpolatorSystem m_physicsInterpolator;
		 std::vector<b2Vec2> m_texs;
		 ActionController<PlayerState, TemplateHasher<PlayerState>, b2Body*> m_actionController;
		 WorldEntityLoader m_componentLoader;
		 PlayerAnimationSystem m_playerAnimationSystem;
		 std::vector<tmx::MapLayer> layers;
};

#endif /* GAME_H_ */
