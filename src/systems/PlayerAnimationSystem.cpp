#include <systems/PlayerAnimationSystem.h>

PlayerAnimationSystem::PlayerAnimationSystem() : Base(anax::ComponentFilter().requires<PlayerStateComponent, AnimationComponent>()){

}

PlayerAnimationSystem::~PlayerAnimationSystem() {
}

void PlayerAnimationSystem::update(float dt) {
    auto entities = getEntities();
    for(auto entity : entities){
    		auto& playerState = entity.getComponent<PlayerStateComponent>();
    		auto& animationComp = entity.getComponent<AnimationComponent>();
    		PlayerState currentStatus = playerState.playerState;

    		if(currentStatus == PlayerState::MOVE_RIGHT && animationComp.animator.getPlayingAnimation() != "walkRight"){
    			animationComp.animator.playAnimation("walkRight", true);
    		}else if(currentStatus == PlayerState::MOVE_LEFT && animationComp.animator.getPlayingAnimation() != "walkLeft"){
    			animationComp.animator.playAnimation("walkLeft", true);
    		}

    		if (!animationComp.animator.isPlayingAnimation()){
    			animationComp.animator.playAnimation("standing");
    		}else if(currentStatus == PlayerState::DEFAULT_STATE && animationComp.animator.getPlayingAnimation() != "standing"){
    			animationComp.animator.playAnimation("standing");
    		}

    		animationComp.animator.update(sf::milliseconds(dt));
    		animationComp.animator.animate(animationComp.m_sprite);
    }
}
