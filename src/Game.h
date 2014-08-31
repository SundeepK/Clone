#ifndef GAME_H_
#define GAME_H_

#include <anax/anax.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <systems/PlayerControlsSystem.h>
#include <systems/TextureRectRenderSystem.h>
#include <components/Texcoords.h>
#include <B2DWorld.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
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

class Game {

	public:

		Game(sf::RenderWindow& renderWindow);
		virtual ~Game();

		 void init();
		 void update(float deltaTime);
		 void render();

	private:
		 std::unique_ptr<sf::RenderWindow> m_mainRenderWindow;
		 SFMLB2dDebugDraw m_debugDrawer;
		 B2DWorld m_box2DWorld;
		 anax::World m_world;
		 anax::Entity m_player;
		 PlayerControlsSystem m_playerControlsSystem;
		 TextureRectRenderSystem m_textureRectSystem;
		 OpenGLTextureRenderer m_openglTextureRenderer;
		 PhysicsInterpolatorSystem m_physicsInterpolator;
		 std::vector<b2Vec2> m_texs;
		 ActionController<PlayerState, TemplateHasher<PlayerState>, b2Body*> m_actionController;
		 WorldEntityLoader m_componentLoader;
		 PlayerAnimationSystem m_playerAnimationSystem;

};

#endif /* GAME_H_ */
