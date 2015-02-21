#ifndef SRC_GAME_OBJECTS_PLAYERENDPOINT_H_
#define SRC_GAME_OBJECTS_PLAYERENDPOINT_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>


class PlayerEndPoint : public GameEntityCreator {
public:
	PlayerEndPoint();
	~PlayerEndPoint();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	GameObjectProperty getProperties();

};

#endif /* SRC_GAME_OBJECTS_PLAYERENDPOINT_H_ */
