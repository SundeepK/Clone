#ifndef PLAYERCONTROLSCOMPONENT_H_
#define PLAYERCONTROLSCOMPONENT_H_

#include <anax/Component.hpp>

class PlayerControlsComponent : anax::Component<PlayerControlsComponent>
{
	public:
		enum class PlayerMovementControls {
			NO_STATE = -1,
			DEFAULT_STATE = 0,
			MOVE_LEFT,
			MOVE_RIGHT,
			JUMP
	};

};

#endif /* PLAYERCONTROLSCOMPONENT_H_ */
