#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>
#include <ActionController.h>
#include <PlayerControls.h>
#include <PlayerState.h>
#include <Box2D/Common/b2Math.h>

class PlayerControlsSystem : anax::System<PlayerControlsSystem>, Updateable {
	public:
		PlayerControlsSystem();
		virtual ~PlayerControlsSystem();

		void update(float dt);
		b2Vec2 getMovementImpulse();

	private:

		void movePlayerLeft(float dt);
		void movePlayerRight(float dt);
		void playerJump(float dt);
		void movePlayerDown(float dt);

		Action m_moveLeft (PlayerControls::LEFT_KEY);
		Action m_moveRight (PlayerControls::RIGHT_KEY);
		Action m_jump (PlayerControls::JUMP_KEY);
		Action m_moveDown (PlayerControls::DOWN_KEY);

	    ActionController<PlayerState> m_actionController;
	    b2Vec2 m_impulse;
};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
