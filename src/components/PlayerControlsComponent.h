#ifndef PLAYERCONTROLSCOMPONENT_H_
#define PLAYERCONTROLSCOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/System.hpp>

class PlayerControlsComponent : anax::Component<PlayerControlsComponent>
{
	public:
	 struct Controls
	    {
	       typedef sf::Keyboard::Key Key;

	       const Key JUMP_KEY = Key::W;
	       const Key LEFT_KEY = Key::A;
	       const Key DOWN_KEY = Key::S;
	       const Key RIGHT_KEY = Key::D;

	    };

	 const Controls controls;
};

#endif /* PLAYERCONTROLSCOMPONENT_H_ */
