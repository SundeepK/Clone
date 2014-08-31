#ifndef PLAYERANIMATIONSYSTEM_H_
#define PLAYERANIMATIONSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <components/PlayerControls.h>
#include <components/PlayerStateComponent.h>
#include <components/PlayerState.h>
#include <components/AnimationComponent.h>

class PlayerAnimationSystem :  public anax::System<PlayerAnimationSystem>{
public:
	PlayerAnimationSystem();
	virtual ~PlayerAnimationSystem();

	void update(float dt);

};

#endif /* PLAYERANIMATIONSYSTEM_H_ */
