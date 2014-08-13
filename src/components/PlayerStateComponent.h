#ifndef PLAYERSTATECOMPONENET_H_
#define PLAYERSTATECOMPONENET_H_

#include <components/PlayerState.h>

class PlayerStateComponent : public anax::Component<PlayerStateComponent>
{
	public:
	PlayerStateComponent();
	~PlayerStateComponent();

	PlayerState playerState;

	private:


};



#endif /* PLAYERSTATECOMPONENET_H_ */
