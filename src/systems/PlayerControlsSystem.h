#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <anax/System.hpp>
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
#include <components/SensorComponent.h>
#include <memory>


class PlayerControlsSystem : public anax::System<PlayerControlsSystem> {


	public:
		PlayerControlsSystem();
	//	PlayerControlsSystem(std::unordered_map<PlayerState, sf::Keyboard::Key, std::hash<int>> playerControlsMap);
		~PlayerControlsSystem();
		void update(float dt);

	private:

		class PlayerControlsSystemImpl;
		std::unique_ptr<PlayerControlsSystemImpl> m_impl;

};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
