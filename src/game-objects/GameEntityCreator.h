#ifndef SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_
#define SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>
#include <unordered_map>

struct GameObjectProperty{

	enum tmx::MapObjectShape objectShapeType;
	bool hasShape = true;
	std::unordered_map<std::string, std::string> properties;

};


class GameEntityCreator {
public:
	GameEntityCreator(){

	}

	virtual ~GameEntityCreator(){

	}

	GameEntityCreator(GameEntityCreator&& other){

	}

	GameEntityCreator(GameEntityCreator& other){

	}


	virtual void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) = 0;
	virtual GameObjectProperty getProperties() = 0;

};



#endif /* SRC_GAME_OBJECTS_GAMEENTITYCREATOR_H_ */
