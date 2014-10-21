#include "PlayerControlsSystem.h"


class PlayerControlsSystem::PlayerControlsSystemImpl{

public:
	PlayerControlsSystemImpl() : m_moveLeft (PlayerControls::LEFT_KEY), m_moveRight (PlayerControls::RIGHT_KEY), m_jump (PlayerControls::JUMP_KEY),
								m_moveDown (PlayerControls::DOWN_KEY), m_moveLeftReleased(PlayerControls::LEFT_KEY,ActionType::Released), m_moveRightReleased(PlayerControls::RIGHT_KEY, ActionType::Released){
		 m_actionController[PlayerState::MOVE_LEFT] = m_moveLeft ;
	     m_actionController[PlayerState::MOVE_RIGHT] = m_moveRight ;
		 m_actionController[PlayerState::JUMP] = m_jump ;
		 m_actionController[PlayerState::MOVE_DOWN] = m_moveDown ;
//		 m_actionController[PlayerState::MOVE_LEFT_RELEASED] = m_moveLeftReleased ;
//		 m_actionController[PlayerState::MOVE_RIGHT_RELEASED] = m_moveRightReleased ;

		 m_actionController.addCallback(PlayerState::MOVE_LEFT, movePlayerLeft());
		 m_actionController.addCallback(PlayerState::MOVE_RIGHT,  movePlayerRight());
		 m_actionController.addCallback(PlayerState::JUMP,  playerJump());
		 m_actionController.addCallback(PlayerState::MOVE_LEFT_RELEASED,  movePlayerLeftReleased());
		 m_actionController.addCallback(PlayerState::MOVE_RIGHT_RELEASED,  movePlayerRightReleased());

		// m_actionController.addCallback(PlayerState::MOVE_DOWN,  movePlayerDown());
	}

	~PlayerControlsSystemImpl(){}

	Action m_moveLeft;
	Action m_moveLeftReleased;
	Action m_moveRightReleased;
	Action m_moveRight;
	Action m_jump;
	Action m_moveDown;

	ActionController<PlayerState, TemplateHasher<PlayerState>, anax::Entity&> m_actionController;
	PlayerState m_currentPlayerState;

	b2Vec2 left;
	b2Vec2 right;
	b2Vec2 jump;
	b2Vec2 down;

	const float m_impulse = 60.0f;
	const float m_jumpImpulse = 6.0f;
	int moved = 0;

	void update(sf::RenderWindow& window, float dt, std::vector<anax::Entity>& entities) {

	    if(moved == 0){
			for (auto entity : entities) {
				auto& physicsComponent = entity.getComponent<PhysicsComponent>();
				b2Body* body = physicsComponent.physicsBody;
				m_currentPlayerState = PlayerState::MOVE_LEFT_RELEASED;

				auto & sensorComp = entity.getComponent<SensorComponent>();
				if(sensorComp.currentTotalContacts >= 1)
					body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
			}
	    }
	    moved = 0;

	    for(auto entity : entities){
	    		auto& playerStateComp = entity.getComponent<PlayerStateComponent>();
	   			m_actionController.triggerCallbacks(dt, entity);
	    		playerStateComp.playerState = m_currentPlayerState;
	    }

	    m_currentPlayerState = PlayerState::DEFAULT_STATE;
	}

	std::function<void (float,  anax::Entity& entity)> movePlayerLeft() {
		 return [this](float,  anax::Entity& entity){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_LEFT;
			if(body->GetLinearVelocity().x > -20.0f  ) {
				body->ApplyForce( b2Vec2(-m_impulse,0.0f),  body->GetWorldCenter() , true);
			}
			moved++;
		};
	}

	std::function<void (float, anax::Entity& entity)> movePlayerRight() {
		 return [this](float,  anax::Entity& entity){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_RIGHT;
			if(body->GetLinearVelocity().x < 20.0f) {
				body->ApplyForce( b2Vec2(m_impulse,0.0f),  body->GetWorldCenter()  , true);
			}
			moved++;
		};
	}

	std::function<void (float,  anax::Entity& entity)> movePlayerLeftReleased() {
		 return [this](float,  anax::Entity& entity){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_LEFT_RELEASED;
			body->SetLinearVelocity(b2Vec2 (0,body->GetLinearVelocity().y));
		};
	}

	std::function<void (float,  anax::Entity& entity)> movePlayerRightReleased() {
		 return [this](float,  anax::Entity& entity){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_RIGHT_RELEASED;
			body->SetLinearVelocity(b2Vec2 (0,body->GetLinearVelocity().y));
		};
	}



	std::function<void (float, anax::Entity& entity)> playerJump() {
		return [this](float,  anax::Entity& entity) {
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			auto & sensorComp = entity.getComponent<SensorComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::JUMP;

			if(sensorComp.currentTotalContacts >= 1)
				body->ApplyLinearImpulse( b2Vec2(0.0f,-m_jumpImpulse*2), body->GetWorldCenter() , true);
			moved++;
		};
	}

	std::function<void (float, anax::Entity& entity)> movePlayerDown() {
		return [this](float, anax::Entity& entity) {
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_DOWN;
			body->ApplyLinearImpulse( b2Vec2(0.0f,m_impulse) , body->GetWorldCenter() , true);
		};
	}
};

PlayerControlsSystem::PlayerControlsSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, PhysicsComponent, SensorComponent>()), m_impl(new PlayerControlsSystemImpl()){
}

PlayerControlsSystem::~PlayerControlsSystem() {
}

void PlayerControlsSystem::update(sf::RenderWindow& window, float dt) {
    auto entities = getEntities();
    m_impl->update(window, dt, entities);
}




