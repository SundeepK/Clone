#ifndef PLAYERANIMATIONSYSTEM_H_
#define PLAYERANIMATIONSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>

class PlayerAnimationSystem :  public anax::System<PlayerAnimationSystem>{
public:
	PlayerAnimationSystem();
	virtual ~PlayerAnimationSystem();

	void update(float dt);

private:
	class PlayerAnimationSystemImpl;
	std::unique_ptr<PlayerAnimationSystemImpl> m_impl;


};

#endif /* PLAYERANIMATIONSYSTEM_H_ */
