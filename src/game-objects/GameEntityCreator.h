#ifndef SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_
#define SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>

class GameEntityCreator {
public:
	GameEntityCreator(){

	}
	virtual ~GameEntityCreator(){

	}

	virtual void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) = 0;

};



#endif /* SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_ */
