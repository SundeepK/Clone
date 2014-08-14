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

void PlayerControlsSystem::update(float dt) {

    auto entities = getEntities();

    for(auto entity : entities){
    	m_actionController.triggerCallbacks(dt);
    	auto& physicsComponent = entity.getComponent<PhysicsComponent>();
    	b2Body* body = physicsComponent.physicsBody;
    	if(body->GetLinearVelocity().x > -10.0f && body->GetLinearVelocity().x < 10.0f ){
    		body->ApplyLinearImpulse(m_impulse, body->GetWorldCenter(), true);
    	}
    }
}

std::function<void (float)> PlayerControlsSystem::movePlayerLeft() {
	 return [this](float x) { m_impulse = b2Vec2(-0.4f,0.0f); };
}

std::function<void (float)> PlayerControlsSystem::movePlayerRight() {
	 return [this](float x) { m_impulse =  b2Vec2( 0.4,0.0f);};
}

std::function<void (float)> PlayerControlsSystem::playerJump() {
	return [this](float x) { m_impulse =  b2Vec2(0.0f,-0.4);};
}

std::function<void (float)> PlayerControlsSystem::movePlayerDown() {
	 return [this](float x) { m_impulse = b2Vec2(0.0f,0.4);};
}


