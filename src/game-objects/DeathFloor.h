#ifndef SRC_GAME_OBJECTS_DEATHFLOOR_H_
#define SRC_GAME_OBJECTS_DEATHFLOOR_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <memory>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class DeathFloor : public GameEntityCreator {
public:
	DeathFloor();
	~DeathFloor();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	GameObjectProperty getProperties();

private:
	class DeathFloorImpl;
	std::unique_ptr<DeathFloorImpl> m_impl;

};

#endif /* SRC_GAME_OBJECTS_DEATHFLOOR_H_ */
