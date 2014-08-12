#include "PlayerControlsSystem.h"

PlayerControlsSystem::PlayerControlsSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent,PhysicsComponent>()) {
	 m_actionController[PlayerState::MOVE_LEFT] = m_moveLeft ;
     m_actionController[PlayerState::MOVE_RIGHT] = m_moveRight ;
	 m_actionController[PlayerState::JUMP] = m_jump ;
	 m_actionController[PlayerState::MOVE_DOWN] = m_moveDown ;

	 m_actionController.addCallback(PlayerState::MOVE_LEFT, movePlayerLeft);
	 m_actionController.addCallback(PlayerState::MOVE_RIGHT,  movePlayerRight);
	 m_actionController.addCallback(PlayerState::JUMP,  playerJump);
	 m_actionController.addCallback(PlayerState::MOVE_DOWN,  movePlayerDown);
}

PlayerControlsSystem::~PlayerControlsSystem() {
}

void PlayerControlsSystem::update(float dt) {

    auto entities = getEntities();

    for(auto e : entities){
    	m_actionController.triggerCallbacks(dt);

    }

}

void PlayerControlsSystem::movePlayerLeft(float dt) {
	m_impulse = b2Vec2(-0.4f,0.0f);
}

void PlayerControlsSystem::movePlayerRight(float dt) {
	m_impulse = b2Vec2( 0.4,0.0f);
}

void PlayerControlsSystem::playerJump(float dt) {
	m_impulse = b2Vec2(0.0f,-0.4);
}

void PlayerControlsSystem::movePlayerDown(float dt) {
	m_impulse = b2Vec2(0.0f,0.4);
}

b2Vec2 PlayerControlsSystem::getMovementImpulse() {
	return m_impulse;
}

