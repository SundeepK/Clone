#ifndef PLAYERCONTROLSSYSTEM_H_
#define PLAYERCONTROLSSYSTEM_H_

#include <anax/System.hpp>
#include <Updateable.h>


class PlayerControlsSystem : anax::System<PlayerControlsSystem>, Updateable {
	public:
		PlayerControlsSystem();
		virtual ~PlayerControlsSystem();

		void update(float dt);

	private:

		void movePlayerLeft();
		void movePlayerRight();
		void playerJump();
		void movePlayerDown();



};

#endif /* PLAYERCONTROLSSYSTEM_H_ */
