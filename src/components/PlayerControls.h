#ifndef PLAYERCONTROLSCOMPONENT_H_
#define PLAYERCONTROLSCOMPONENT_H_

#include <anax/Component.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
class PlayerControls
{
	public:
		PlayerControls();
	    typedef sf::Keyboard::Key Key;

	     static const Key JUMP_KEY = Key::W;
	     static const Key LEFT_KEY = Key::A;
	     static const Key DOWN_KEY = Key::S;
	     static const Key RIGHT_KEY = Key::D;
	     static const Key LEFT_SHIFT_KEY = Key::LShift;
	     static const Key LEFT_CTRL_KEY = Key::LControl;

};

#endif /* PLAYERCONTROLSCOMPONENT_H_ */
