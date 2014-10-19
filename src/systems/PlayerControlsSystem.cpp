#include "PlayerControlsSystem.h"

PlayerControlsSystem::PlayerControlsSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, PhysicsComponent, SensorComponent>()),
 	 m_moveLeft (PlayerControls::LEFT_KEY), m_moveRight (PlayerControls::RIGHT_KEY), m_jump (PlayerControls::JUMP_KEY), m_moveDown (PlayerControls::DOWN_KEY){

	 m_actionController[PlayerState::MOVE_LEFT] = m_moveLeft ;
     m_actionController[PlayerState::MOVE_RIGHT] = m_moveRight ;
	 m_actionController[PlayerState::JUMP] = m_jump ;
	 m_actionController[PlayerState::MOVE_DOWN] = m_moveDown ;

	 m_actionController.addCallback(PlayerState::MOVE_LEFT, movePlayerLeft());
	 m_actionController.addCallback(PlayerState::MOVE_RIGHT,  movePlayerRight());
	 m_actionController.addCallback(PlayerState::JUMP,  playerJump());
	// m_actionController.addCallback(PlayerState::MOVE_DOWN,  movePlayerDown());
}

PlayerControlsSystem::~PlayerControlsSystem() {
}

void PlayerControlsSystem::update(float dt) {
    auto entities = getEntities();
    for(auto entity : entities){
   			m_actionController.triggerCallbacks(dt, entity);
    		auto& playerStateComp = entity.getComponent<PlayerStateComponent>();
    		playerStateComp.playerState = m_currentPlayerState;

    }
 m_currentPlayerState = PlayerState::DEFAULT_STATE;
}

std::function<void (float,  anax::Entity& entity)> PlayerControlsSystem::movePlayerLeft() {
	 return [this](float,  anax::Entity& entity){
		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComponent.physicsBody;
		m_currentPlayerState = PlayerState::MOVE_LEFT;
		if(body->GetLinearVelocity().x < -10.0f) {return;}
		body->ApplyLinearImpulse( b2Vec2(-m_impulse,0.0f), body->GetWorldCenter(), true);
	};
}

std::function<void (float, anax::Entity& entity)> PlayerControlsSystem::movePlayerRight() {
	 return [this](float,  anax::Entity& entity){
		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComponent.physicsBody;
		m_currentPlayerState = PlayerState::MOVE_RIGHT;
		if(body->GetLinearVelocity().x > 10.0f) {return;}
		body->ApplyLinearImpulse( b2Vec2(m_impulse,0.0f), body->GetWorldCenter() , true);
	};
}

std::function<void (float, anax::Entity& entity)> PlayerControlsSystem::playerJump() {
	return [this](float,  anax::Entity& entity) {
		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
		auto & sensorComp = entity.getComponent<SensorComponent>();
		b2Body* body = physicsComponent.physicsBody;
		m_currentPlayerState = PlayerState::JUMP;

		if(sensorComp.currentTotalContacts >= 1)
			body->ApplyLinearImpulse( b2Vec2(0.0f,-m_impulse*2), body->GetWorldCenter() , true);
	};
}

std::function<void (float, anax::Entity& entity)> PlayerControlsSystem::movePlayerDown() {
	return [this](float, anax::Entity& entity) {
		auto& physicsComponent = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComponent.physicsBody;
		m_currentPlayerState = PlayerState::MOVE_DOWN;
		body->ApplyLinearImpulse( b2Vec2(0.0f,m_impulse) , body->GetWorldCenter() , true);
	};
}


