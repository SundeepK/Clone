#include <systems/PlayerAnimationSystem.h>
#include <components/PlayerControls.h>
#include <components/PlayerStateComponent.h>
#include <components/PlayerState.h>
#include <components/AnimationComponent.h>

class PlayerAnimationSystem::PlayerAnimationSystemImpl{

public:
	PlayerAnimationSystemImpl(){
	}

	~PlayerAnimationSystemImpl() {
	}

	void update(float dt, std::vector<anax::Entity>& entities) {
	    for(auto entity : entities){
	    		auto& playerState = entity.getComponent<PlayerStateComponent>();
	    		auto& animationComp = entity.getComponent<AnimationComponent>();
	    		PlayerState currentStatus = playerState.playerState;

			if (animationComp.animator.isPlayingAnimation()) {
				if (currentStatus == PlayerState::MOVE_RIGHT && animationComp.animator.getPlayingAnimation() != "walkRight") {
					animationComp.animator.playAnimation("walkRight", true);
				} else if (currentStatus == PlayerState::MOVE_LEFT && animationComp.animator.getPlayingAnimation() != "walkLeft") {
					animationComp.animator.playAnimation("walkLeft", true);
				}else if(currentStatus == PlayerState::DEFAULT_STATE && animationComp.animator.getPlayingAnimation() != "standing"){
	    			animationComp.animator.playAnimation("standing");
	    		}
			}else{
    			animationComp.animator.playAnimation("standing");
			}
	    		animationComp.animator.update(sf::milliseconds(dt));
	    		animationComp.animator.animate(animationComp.m_sprite);
	    }
	}

};

PlayerAnimationSystem::PlayerAnimationSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, AnimationComponent>()), m_impl(new PlayerAnimationSystemImpl()){

}

PlayerAnimationSystem::~PlayerAnimationSystem() {
}

void PlayerAnimationSystem::update(float dt) {
    auto entities = getEntities();
    m_impl->update(dt, entities);
}
