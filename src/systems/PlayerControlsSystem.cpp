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

	enum class KeyPressed {
		LEFT,
		RIGHT
	};

	struct PlayerAction{
		bool shouldApplyAction;
		b2Vec2 force;
		int keyOppositePressedCount;
		bool isWallJumped;
		sf::Time lastActionTime;
	};


public:
	PlayerControlsSystemImpl() : m_moveLeft (PlayerControls::LEFT_KEY), m_moveRight (PlayerControls::RIGHT_KEY), m_jump (PlayerControls::JUMP_KEY),
								m_moveDown (PlayerControls::DOWN_KEY), m_moveLeftReleased(PlayerControls::LEFT_KEY,ActionType::Released),
								m_moveRightReleased(PlayerControls::RIGHT_KEY, ActionType::Released), m_jumpReleased(PlayerControls::JUMP_KEY, ActionType::Released){
		 m_actionController[PlayerState::MOVE_LEFT] = m_moveLeft ;
	     m_actionController[PlayerState::MOVE_RIGHT] = m_moveRight ;
		 m_actionController[PlayerState::JUMP] = m_jump ;
		 m_actionController[PlayerState::MOVE_DOWN] = m_moveDown ;
		 m_actionController[PlayerState::JUMP_RLEASED] = m_jumpReleased;
//		 m_actionController[PlayerState::MOVE_LEFT_RELEASED] = m_moveLeftReleased ;
//		 m_actionController[PlayerState::MOVE_RIGHT_RELEASED] = m_moveRightReleased ;

		 m_actionController.addCallback(PlayerState::MOVE_LEFT, movePlayerLeft());
		 m_actionController.addCallback(PlayerState::MOVE_RIGHT,  movePlayerRight());
		 m_actionController.addCallback(PlayerState::JUMP,  playerJump());
		 m_actionController.addCallback(PlayerState::MOVE_LEFT_RELEASED,  movePlayerLeftReleased());
		 m_actionController.addCallback(PlayerState::MOVE_RIGHT_RELEASED,  movePlayerRightReleased());
		 m_actionController.addCallback(PlayerState::JUMP_RLEASED,  jumpReleased());


		// m_actionController.addCallback(PlayerState::MOVE_DOWN,  movePlayerDown());
	}

	~PlayerControlsSystemImpl(){}

	Action m_moveLeft;
	Action m_moveLeftReleased;
	Action m_moveRightReleased;
	Action m_moveRight;
	Action m_jumpReleased;
	Action m_jump;
	Action m_moveDown;

	sf::Clock m_clock;
	sf::Time m_changeInDirectionTime;
	sf::Time m_leftPressed;
	sf::Time m_rightPressed;
	sf::Time m_lastJumpTime;
	sf::Time m_lastTimeOnGround;

	float frameIteration = 1.0f/60.0f;
	float beginBoostVal;
	float m_switchDirectionBoost = 170.0f;

	bool m_boostInAction;
	bool m_isLeftWallJumpTriggered;
	bool m_isRightWallJumpTriggered;
	bool m_isJumpedTriggered;
	bool m_isBoostInMidAir;
	bool m_canJump = true;
	int m_timesAppliedJumpReducer;

	ActionController<PlayerState, TemplateHasher<PlayerState>, anax::Entity&> m_actionController;
	PlayerState m_currentPlayerState;

	b2Vec2 left;
	b2Vec2 right;
	b2Vec2 jump;
	b2Vec2 down;

	const float m_impulse = 35.0f;
	const float m_slowDownForce = 5.f;
	const float m_jumpImpulse = 30.0f;
	const float m_wallJumpImpulse = 10.5f;
	const float m_wallJumpForce = 4.0f;
	int movedLeft = 0;
	int movedRight = 0;
	int m_jumpedCount = 0;
	b2Vec2 m_beforeJumpPosition;

	PlayerAction m_playerLeftAction;
	PlayerAction m_playerRightAction;

	void update(std::vector<sf::Event>& events, float dt, std::vector<anax::Entity>& entities) {

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

			for (auto entity : entities) {
				auto& physicsComponent = entity.getComponent<PhysicsComponent>();
				b2Body* body = physicsComponent.physicsBody;
				m_currentPlayerState = PlayerState::MOVE_LEFT_RELEASED;
				body->SetGravityScale(2);

				auto &sensorComps = entity.getComponent<Sensor>();
				auto sensor = sensorComps.sensors["FootSensor"];
//				std::cout << "jumping velocity " << body->GetLinearVelocity().y  << std::endl;
					if(sensor.currentTotalContacts < 1 && m_isJumpedTriggered){
//							std::cout << "jumping velocity " << body->GetPosition().y - m_beforeJumpPosition.y << std::endl;
							//std::cout << "jumping velocity " << body->GetLinearVelocity().y  << std::endl;

						if((!m_isLeftWallJumpTriggered && !m_isRightWallJumpTriggered ) ){
							if(body->GetLinearVelocity().y >= -5){
//								body->ApplyLinearImpulse(b2Vec2(0, 3), body->GetWorldCenter(), true);
//								m_timesAppliedJumpReducer++;
//								if(m_timesAppliedJumpReducer > 1){
//									m_isJumpedTriggered = false;
//									m_timesAppliedJumpReducer = 0;
//								}
							}
						}else{
							m_isJumpedTriggered = false;
							m_timesAppliedJumpReducer = 0;
						}
					}
			}



	    for(sf::Event event : events)
	    {
	        if (event.type == sf::Event::KeyReleased && event.key.code == PlayerControls::JUMP_KEY){
	        		m_canJump = true;
	        		break;
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


	void setupChangeDirectionBoost(SensorComponent& footSensor,  float dtSinceChangeInDirection, sf::Time lastKeyPress, int keyPressCount, b2Body* player, KeyPressed keypressed){
		float xvelocity = player->GetLinearVelocity().x;
		if (footSensor.currentTotalContacts >= 1) {
			if (((keypressed == KeyPressed::LEFT && xvelocity > 0) || (keypressed == KeyPressed::RIGHT  && xvelocity < 0)) && !m_boostInAction && dtSinceChangeInDirection < 500 && keyPressCount == 0) {
				m_boostInAction = true;
				m_changeInDirectionTime = lastKeyPress;
				beginBoostVal = xvelocity;
				frameIteration = 1.0f / 60.0f;
			}
		}else if(!m_isLeftWallJumpTriggered && !m_isRightWallJumpTriggered){
			if (((keypressed == KeyPressed::LEFT && xvelocity > 0) || (keypressed == KeyPressed::RIGHT  && xvelocity < 0)) && !m_boostInAction && dtSinceChangeInDirection < 500 && keyPressCount == 0) {
				m_isBoostInMidAir = true;
			}
		}
	}

	void applyForce(b2Body* playerBody, const PlayerAction& playerAction){
		float xVelocity = playerBody->GetLinearVelocity().x ;
		b2Vec2 playerCenter = playerBody->GetWorldCenter();
		if(playerAction.shouldApplyAction) {
			if(playerAction.isWallJumped && !m_boostInAction && playerAction.keyOppositePressedCount <= 0){
				playerBody->ApplyForce( b2Vec2(playerAction.force.x, -80), playerCenter , true);
				m_boostInAction = true;
				m_changeInDirectionTime = playerAction.lastActionTime;
				frameIteration = 1.0f/60.0f;
				beginBoostVal = xVelocity;
			}else{
				playerBody->ApplyForce( playerAction.force, playerCenter , true);
			}
		}
	}

	std::function<void (float,  anax::Entity& entity)> movePlayerLeft() {
		return [this](float, anax::Entity& entity) {
			auto& physicsComponent = entity.getComponent<PhysicsComponent>();
			auto & sensorComp = entity.getComponent<Sensor>().sensors["FootSensor"];
			auto & footSensor = entity.getComponent<Sensor>().sensors["FootSensor"];

			b2Body* body = physicsComponent.physicsBody;
			m_currentPlayerState = PlayerState::MOVE_LEFT;
			m_leftPressed = m_clock.getElapsedTime();
			float impulse = m_impulse;

			setupChangeDirectionBoost(sensorComp, (m_leftPressed - m_rightPressed).asMilliseconds(), m_leftPressed, movedRight, body, KeyPressed::LEFT);

			if(m_isBoostInMidAir){
				movedLeft++;
				body->ApplyLinearImpulse(b2Vec2(-1.75,0.5), body->GetWorldCenter(), true);
				m_isBoostInMidAir = false;
				return;
			}

			if(m_boostInAction){
				frameIteration += 1.0f/60.0f;
				if(m_isLeftWallJumpTriggered){
					impulse = PlayerControlsSystemImpl::easeOutExpo(frameIteration,beginBoostVal, -60  - beginBoostVal ,2.0f);
				}else{
					impulse = PlayerControlsSystemImpl::easeOutExpo(frameIteration,beginBoostVal, -m_switchDirectionBoost  - beginBoostVal ,1.0f);
				}
				float elapsed = (m_leftPressed - m_changeInDirectionTime ).asMilliseconds();
				if(elapsed > 500.0f){
					m_boostInAction = false;
					m_isLeftWallJumpTriggered = false;
				}
			}

			m_playerLeftAction.isWallJumped = m_isLeftWallJumpTriggered;
			m_playerLeftAction.force = b2Vec2(-std::abs(impulse),0);
			m_playerLeftAction.lastActionTime = m_leftPressed;
			m_playerLeftAction.keyOppositePressedCount = movedRight;
			m_playerLeftAction.shouldApplyAction = body->GetLinearVelocity().x >  -40.0f;

			applyForce(body, m_playerLeftAction);

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

			setupChangeDirectionBoost(sensorComp, ( m_rightPressed - m_leftPressed).asMilliseconds(), m_rightPressed, movedLeft, body, KeyPressed::RIGHT);

			if(m_isBoostInMidAir){
				movedRight++;
				body->ApplyLinearImpulse(b2Vec2(1.75,0.5), body->GetWorldCenter(), true);
				m_isBoostInMidAir = false;
				return;
			}

			if(m_boostInAction){
				frameIteration += 1.0f/60.0f;
				if(m_isRightWallJumpTriggered){
					impulse = PlayerControlsSystemImpl::easeOutExpo(frameIteration,beginBoostVal, 60  - beginBoostVal ,2.0f);
				}else{
					impulse = PlayerControlsSystemImpl::easeOutExpo(frameIteration,beginBoostVal, m_switchDirectionBoost  - beginBoostVal ,1.0f);
				}
				float elapsed = (m_rightPressed - m_changeInDirectionTime ).asMilliseconds();
				if(elapsed > 500.0f){
					m_boostInAction = false;
					m_isRightWallJumpTriggered = false;
				}
			}

			m_playerRightAction.isWallJumped = m_isRightWallJumpTriggered;
			m_playerRightAction.force = b2Vec2(std::abs(impulse),0);
			m_playerRightAction.lastActionTime = m_rightPressed;
			m_playerRightAction.keyOppositePressedCount = movedLeft;
			m_playerRightAction.shouldApplyAction = body->GetLinearVelocity().x < 40.0f;

			applyForce(body, m_playerRightAction);
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

	std::function<void (float,  anax::Entity& entity)> jumpReleased() {
		 return [this](float,  anax::Entity& entity){
			 m_canJump = true;
			 std::cout << "jumpoed rleased" << std::endl;
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
				if(!m_canJump){
					return;
				}
				m_isJumpedTriggered = true;
				body->ApplyLinearImpulse( b2Vec2(0.0f,-m_jumpImpulse), body->GetWorldCenter() , true);
				m_canJump = false;
				m_beforeJumpPosition = body->GetPosition();
			}else if(leftSensor.currentTotalContacts >= 1){
				body->ApplyLinearImpulse( b2Vec2(m_wallJumpForce,-m_wallJumpImpulse), body->GetWorldCenter() , true);
				m_isLeftWallJumpTriggered = true;
				m_canJump = false;
			}else if(rightSensor.currentTotalContacts >= 1){
				body->ApplyLinearImpulse( b2Vec2(-m_wallJumpForce,-m_wallJumpImpulse), body->GetWorldCenter() , true);
				m_isRightWallJumpTriggered = true;
				m_canJump = false;
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

void PlayerControlsSystem::update(std::vector<sf::Event>& events, float dt) {
    auto entities = getEntities();
    m_impl->update(events, dt, entities);
}




