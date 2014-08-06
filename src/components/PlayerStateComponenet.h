#ifndef PLAYERSTATECOMPONENET_H_
#define PLAYERSTATECOMPONENET_H_

class PlayerStateComponent : anax::Component<PlayerStateComponent>
{
	public:
		enum class State {
		NO_STATE = -1,
		DEFAULT_STATE = 0,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP
	};

	private:
		State m_state;


};



#endif /* PLAYERSTATECOMPONENET_H_ */
