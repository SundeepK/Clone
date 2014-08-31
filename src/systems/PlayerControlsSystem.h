#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>
#include <ActionController.h>
#include <components/PlayerControls.h>
#include <components/PlayerStateComponent.h>
#include <Box2D/Common/b2Math.h>
#include <components/PhysicsComponent.h>
#include <unordered_map>
#include <functional>
#include <components/PlayerState.h>
#include <components/Texcoords.h>
#include <iostream>

class PlayerControlsSystem : public anax::System<PlayerControlsSystem> {


	public:
		PlayerControlsSystem();
	//	PlayerControlsSystem(std::unordered_map<PlayerState, sf::Keyboard::Key, std::hash<int>> playerControlsMap);
		virtual ~PlayerControlsSystem();

		void update(float dt);
		b2Vec2 getMovementImpulse();

	private:

		std::function<void (float, b2Body*, PhysicsComponent& physicsComponent)>  movePlayerLeft();
		std::function<void (float, b2Body*, PhysicsComponent& physicsComponent)>  movePlayerRight();
		std::function<void (float, b2Body*, PhysicsComponent& physicsComponent)>  playerJump();
		std::function<void (float, b2Body*, PhysicsComponent& physicsComponent)>  movePlayerDown();

		Action m_moveLeft;
		Action m_moveRight;
		Action m_jump;
		Action m_moveDown;

	    ActionController<PlayerState, TemplateHasher<PlayerState>, b2Body*, PhysicsComponent&> m_actionController;
	    PlayerState m_currentPlayerState;

	    b2Vec2 left;
	    b2Vec2 right;
	    b2Vec2 jump;
	    b2Vec2 down;

	    const float m_impulse = 0.8f;

};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
