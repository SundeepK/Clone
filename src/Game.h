#ifndef GAME_H_
#define GAME_H_

#include <anax/anax.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <systems/PlayerControlsSystem.h>
#include <B2DWorld.h>
#include <SFML/Graphics.hpp>


class Game {
	public:
		Game(sf::RenderWindow renderWindow);
		virtual ~Game();

		 void init();
		 void update(float deltaTime);
		 void render();

	private:
		 B2DWorld m_box2DWorld;
		 SFMLB2dDebugDraw m_debugDrawer;
		 anax::World m_world;
		 anax::Entity m_player;
		 PlayerControlsSystem m_playerControlsSystem;
		 sf::RenderWindow m_mainRenderWindow;

};

#endif /* GAME_H_ */
