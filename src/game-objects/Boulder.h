#ifndef SRC_GAME_OBJECTS_BOULDER_H_
#define SRC_GAME_OBJECTS_BOULDER_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class Boulder : public GameEntityCreator {
public:
	Boulder();
	~Boulder();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);

private:

	class BoulderImpl;
	std::unique_ptr<BoulderImpl> m_impl;

};

#endif /* SRC_GAME_OBJECTS_BOULDER_H_ */
