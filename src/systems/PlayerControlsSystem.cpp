#include "PlayerControlsSystem.h"
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
#include <components/Sensors.h>
#include <components/SensorComponent.h>

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

	sf::Clock m_clock;
	sf::Time m_leftPressed;
	sf::Time m_leftBoost;
	sf::Time m_rightBoost;
	sf::Time m_rightPressed;
	sf::Time m_lastJumpTime;

	float rightFrame = 1.0f/60.0f;
	float leftFrame = 1.0f/60.0f;
	float beginLeftBoostVal;
	float beginRightBoostVal;
	float m_switchDirectionBoost = 200.0f;
	bool m_leftBoostInAction;
	bool m_rightBoostInAction;

	bool m_isLeftWallJumpTriggered;
	bool m_isRightWallJumpTriggered;

	ActionController<PlayerState, TemplateHasher<PlayerState>, anax::Entity&> m_actionController;
	PlayerState m_currentPlayerState;

	b2Vec2 left;
	b2Vec2 right;
	b2Vec2 jump;
	b2Vec2 down;

	const float m_impulse = 40.0f;
	const float m_slowDownForce = 5.f;
	const float m_jumpImpulse = 160.0f;
	const float m_wallJumpForce = 300.0f;
	int movedLeft = 0;
	int movedRight = 0;
	int m_jumpedCount = 0;

	void update(sf::RenderWindow& window, float dt, std::vector<anax::Entity>& entities) {

		if(m_leftPressed.asMilliseconds() == 0){
			m_leftPressed = m_clock.getElapsedTime();
		}

		if(m_rightPressed.asMilliseconds() == 0){
			m_rightPressed = m_clock.getElapsedTime();
		}

	    if(movedLeft == 0 && movedRight ==0 ){
			for (auto entity : entities) {
				auto& physicsComponent = entity.getComponent<PhysicsComponent>();
				b2Body* body = physicsComponent.physicsBody;
				m_currentPlayerState = PlayerState::MOVE_LEFT_RELEASED;

				auto &sensorComps = entity.getComponent<Sensor>();
				auto sensor = sensorComps.sensors["FootSensor"];
					if(sensor.currentTotalContacts >= 1){
						body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
					}
			}
	    }


	    movedLeft = 0;
	    movedRight = 0;
	    for(auto entity : entities){
	    		auto& playerStateComp = entity.getComponent<PlayerStateComponent>();
	   			m_actionController.triggerCallbacks(dt, entity);
	    		playerStateComp.playerState = m_currentPlayerState;
	    }

	    m_currentPlayerState = PlayerState::DEFAULT_STATE;
	}


	static float easeOutExpo(float currentTime,float beginingValue,float changeInValue, float duration){
		return (currentTime==duration) ? beginingValue+changeInValue : changeInValue * (- std::pow(6, -10 * currentTime/duration) + 1) + beginingValue;
	}

	std::function<void (float,  anax::Entity& entity)> movePlayerLeft() {
		return [this](float, anax::Entity& entity) {
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			auto & sensorComp = entity.getComponent<Sensor>().sensors["FootSensor"];

			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_LEFT;
			m_leftPressed = m_clock.getElapsedTime();
			float impulse = m_impulse;

			if(sensorComp.currentTotalContacts >= 1) {

				if(( m_leftPressed - m_rightPressed ).asMilliseconds() < 500 && movedRight== 0 && body->GetLinearVelocity().x > 0 && !m_leftBoostInAction) {
					m_leftBoostInAction = true;
					m_leftBoost = m_leftPressed;
					beginLeftBoostVal = body->GetLinearVelocity().x;
					leftFrame = 1.0f/60.0f;
				}
			}

			if(m_leftBoostInAction){
				leftFrame += 1.0f/60.0f;
				if(m_isLeftWallJumpTriggered){
					impulse = PlayerControlsSystemImpl::easeOutExpo(leftFrame,beginLeftBoostVal, -60  - beginLeftBoostVal ,2.0f);
				}else{
					impulse = PlayerControlsSystemImpl::easeOutExpo(leftFrame,beginLeftBoostVal, -m_switchDirectionBoost  - beginLeftBoostVal ,1.0f);
				}
				float elapsed = (m_leftPressed - m_leftBoost ).asMilliseconds();
				if(elapsed > 500.0f){
					m_leftBoostInAction = false;
					m_isLeftWallJumpTriggered = false;
				}
			}

			if(body->GetLinearVelocity().x > -40.0f ) {
				if(m_isLeftWallJumpTriggered && !m_leftBoostInAction && movedRight <= 0){
					body->ApplyForce( b2Vec2(-std::abs(impulse),-80), body->GetWorldCenter() , true);
					m_leftBoostInAction = true;
					m_leftBoost = m_leftPressed;
					leftFrame = 1.0f/60.0f;
					beginLeftBoostVal = body->GetLinearVelocity().x;
				}else{
					body->ApplyForce( b2Vec2(-std::abs(impulse),0.0f), body->GetWorldCenter() , true);
				}
			}
			movedLeft++;
		};
	}

	std::function<void (float, anax::Entity& entity)> movePlayerRight() {
		 return [this](float,  anax::Entity& entity){
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			auto & sensorComp = entity.getComponent<Sensor>().sensors["FootSensor"];

			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_RIGHT;
			float impulse = m_impulse;
			m_rightPressed = m_clock.getElapsedTime();

			if(sensorComp.currentTotalContacts >= 1) {

				if((m_rightPressed - m_leftPressed).asMilliseconds() < 500 && movedLeft== 0 && body->GetLinearVelocity().x < 0 && !m_rightBoostInAction) {
					std::cout << "in right" <<std::endl;
					m_rightBoostInAction = true;
					m_rightBoost = m_rightPressed;
					beginRightBoostVal= body->GetLinearVelocity().x;
					rightFrame = 1.0f/60.0f;
				}

			}


			if(m_rightBoostInAction){
				rightFrame += 1.0f/60.0f;
				if(m_isRightWallJumpTriggered){
					impulse = PlayerControlsSystemImpl::easeOutExpo(rightFrame,beginLeftBoostVal, 60  - beginRightBoostVal ,2.0f);
				}else{
					impulse = PlayerControlsSystemImpl::easeOutExpo(rightFrame,beginLeftBoostVal, m_switchDirectionBoost  - beginRightBoostVal ,1.0f);
				}
				float elapsed = (m_rightPressed - m_rightBoost ).asMilliseconds();
				if(elapsed > 1000.0f){
					m_rightBoostInAction = false;
					m_isRightWallJumpTriggered = false;
				}
			}


			if(body->GetLinearVelocity().x < 40.0f) {

				if(m_isRightWallJumpTriggered && !m_rightBoostInAction){
					body->ApplyForce( b2Vec2(std::abs(impulse),-80), body->GetWorldCenter() , true);
					m_rightBoostInAction = true;
					m_rightBoost = m_leftPressed;
					rightFrame = 1.0f/60.0f;
					beginLeftBoostVal = body->GetLinearVelocity().x;
				}else{
					body->ApplyForce( b2Vec2(std::abs(impulse),0.0f), body->GetWorldCenter() , true);
				}
			}
			movedRight++;
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
			auto & footSensor = entity.getComponent<Sensor>().sensors["FootSensor"];
			auto & rightSensor = entity.getComponent<Sensor>().sensors["RightSensor"];
			auto & leftSensor = entity.getComponent<Sensor>().sensors["LeftSensor"];


			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::JUMP;

			if(footSensor.currentTotalContacts >= 1){
				body->ApplyForce( b2Vec2(0.0f,-m_jumpImpulse), body->GetWorldCenter() , true);
			}else if(leftSensor.currentTotalContacts >= 1){
				body->ApplyForce( b2Vec2(m_wallJumpForce,-m_jumpImpulse*3), body->GetWorldCenter() , true);
				m_isLeftWallJumpTriggered = true;
			}else if(rightSensor.currentTotalContacts >= 1){
				body->ApplyForce( b2Vec2(-m_wallJumpForce,-m_jumpImpulse*3), body->GetWorldCenter() , true);
				m_isRightWallJumpTriggered = true;
			}
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

PlayerControlsSystem::PlayerControlsSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, PhysicsComponent, Sensor>()), m_impl(new PlayerControlsSystemImpl()){
}

PlayerControlsSystem::~PlayerControlsSystem() {
}

void PlayerControlsSystem::update(sf::RenderWindow& window, float dt) {
    auto entities = getEntities();
    m_impl->update(window, dt, entities);
}




