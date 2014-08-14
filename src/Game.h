#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game();
	virtual ~Game();

	 void init();
	 void update(float deltaTime);
	 void render();

};

#endif /* GAME_H_ */
