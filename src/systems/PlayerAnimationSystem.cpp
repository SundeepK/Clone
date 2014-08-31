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
    		if(currentStatus == PlayerState::MOVE_RIGHT || currentStatus == PlayerState::MOVE_LEFT){
    			animationComp.animator.playAnimation("walk", true);
    		}else{
    			animationComp.animator.stopAnimation();
    		}
    		animationComp.animator.update(sf::seconds(dt));
    		animationComp.animator.animate(animationComp.m_sprite);
    }
}
