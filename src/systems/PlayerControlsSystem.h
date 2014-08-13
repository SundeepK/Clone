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

class PlayerControlsSystem : anax::System<PlayerControlsSystem>, Updateable {


	public:
		PlayerControlsSystem();
	//	PlayerControlsSystem(std::unordered_map<PlayerState, sf::Keyboard::Key, std::hash<int>> playerControlsMap);
		virtual ~PlayerControlsSystem();

		void update(float dt);
		b2Vec2 getMovementImpulse();

	private:

	//	void movePlayerLeft(float dt);
		void movePlayerRight(float dt);
		void playerJump(float dt);
		void movePlayerDown(float dt);

		Action m_moveLeft;
		Action m_moveRight;
		Action m_jump;
		Action m_moveDown;

	    ActionController<PlayerState> m_actionController;
	    b2Vec2 m_impulse;
};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
