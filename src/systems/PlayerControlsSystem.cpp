#include "PlayerControlsSystem.h"

PlayerControlsSystem::PlayerControlsSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, PhysicsComponent>()),
 	 m_moveLeft (PlayerControls::LEFT_KEY), m_moveRight (PlayerControls::RIGHT_KEY), m_jump (PlayerControls::JUMP_KEY), m_moveDown (PlayerControls::DOWN_KEY){

	 m_actionController[PlayerState::MOVE_LEFT] = m_moveLeft ;
     m_actionController[PlayerState::MOVE_RIGHT] = m_moveRight ;
	 m_actionController[PlayerState::JUMP] = m_jump ;
	 m_actionController[PlayerState::MOVE_DOWN] = m_moveDown ;

	 m_actionController.addCallback(PlayerState::MOVE_LEFT, movePlayerLeft());
	 m_actionController.addCallback(PlayerState::MOVE_RIGHT,  movePlayerRight());
	 m_actionController.addCallback(PlayerState::JUMP,  playerJump());
	 m_actionController.addCallback(PlayerState::MOVE_DOWN,  movePlayerDown());
}

PlayerControlsSystem::~PlayerControlsSystem() {
}

void PlayerControlsSystem::update(float dt, sf::RenderWindow* renderWindow) {
	m_actionController.update(*renderWindow);
    auto entities = getEntities();

    for(auto entity : entities){

    	if(	m_currentPlayerState != PlayerState::NO_STATE || m_currentPlayerState != PlayerState::DEFAULT_STATE){
    		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
    		b2Body* body = physicsComponent.physicsBody;

    		if(m_currentPlayerState ==  PlayerState::MOVE_LEFT && (body->GetLinearVelocity().x < -10.0f)){
    			return;
    		}

    		if(m_currentPlayerState ==  PlayerState::MOVE_RIGHT && (body->GetLinearVelocity().x > 10.0f)){
    			return;
    		}
    		body->ApplyLinearImpulse(m_impulse, body->GetWorldCenter(), true);
    	}
    }
	m_actionController.triggerCallbacks(dt);

}

std::function<void (float)> PlayerControlsSystem::movePlayerLeft() {
	 return [this](float x) {
		 m_currentPlayerState = PlayerState::MOVE_LEFT;
		 m_impulse = b2Vec2(-0.4f,0.0f);
	 };
}

std::function<void (float)> PlayerControlsSystem::movePlayerRight() {
	 return [this](float x) {
		 m_currentPlayerState = PlayerState::MOVE_RIGHT;
		 m_impulse =  b2Vec2( 0.4,0.0f);};
}

std::function<void (float)> PlayerControlsSystem::playerJump() {
	return [this](float x) {
		 m_currentPlayerState = PlayerState::JUMP;
		m_impulse =  b2Vec2(0.0f,-0.4);};
}

std::function<void (float)> PlayerControlsSystem::movePlayerDown() {
	 return [this](float x) {
		 m_currentPlayerState = PlayerState::MOVE_DOWN;
		 m_impulse = b2Vec2(0.0f,0.4);};
}


