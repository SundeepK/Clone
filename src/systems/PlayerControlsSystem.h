#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>
#include <ActionController.h>
#include <components/PlayerControls.h>
#include <components/PlayerState.h>
#include <components/PlayerStateComponent.h>
#include <Box2D/Common/b2Math.h>
#include <components/PhysicsComponent.h>
#include <unordered_map>
#include <functional>
#include <components/PlayerState.h>

class PlayerControlsSystem : public anax::System<PlayerControlsSystem> {


	public:
		PlayerControlsSystem();
	//	PlayerControlsSystem(std::unordered_map<PlayerState, sf::Keyboard::Key, std::hash<int>> playerControlsMap);
		virtual ~PlayerControlsSystem();

		void update(float dt, sf::RenderWindow* renderWindow);
		b2Vec2 getMovementImpulse();

	private:

		std::function<void (float)>  movePlayerLeft();
		std::function<void (float)>  movePlayerRight();
		std::function<void (float)>  playerJump();
		std::function<void (float)>  movePlayerDown();

		Action m_moveLeft;
		Action m_moveRight;
		Action m_jump;
		Action m_moveDown;

	    ActionController<PlayerState> m_actionController;
	    b2Vec2 m_impulse;
	    PlayerState m_currentPlayerState;
};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
