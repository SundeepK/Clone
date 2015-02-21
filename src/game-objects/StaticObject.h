#ifndef SRC_GAME_OBJECTS_STATICOBJECT_H_
#define SRC_GAME_OBJECTS_STATICOBJECT_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>
#include <tmx/MapObject.h>
#include <unordered_map>

class StaticObject : public GameEntityCreator {
public:
	StaticObject();
	~StaticObject();

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	GameObjectProperty getProperties();

private:

	static const std::unordered_map<std::string, b2BodyType> BODY_TYPE;

};

#endif /* SRC_GAME_OBJECTS_STATICOBJECT_H_ */
