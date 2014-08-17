#ifndef GAME_H_
#define GAME_H_

#include <anax/anax.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <systems/PlayerControlsSystem.h>
#include <systems/TextureRectRenderSystem.h>
#include <B2DWorld.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory.h>
#include <components/PlayerStateComponent.h>

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

};

#endif /* GAME_H_ */
