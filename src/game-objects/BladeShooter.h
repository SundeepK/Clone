#ifndef SRC_GAME_OBJECTS_BLADESHOOTER_H_
#define SRC_GAME_OBJECTS_BLADESHOOTER_H_

#include <memory>
#include <game-objects/GameEntityCreator.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>

class BladeShooter : public GameEntityCreator{
public:
	BladeShooter();
	~BladeShooter();

	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	std::vector<std::string> getProperties();


private:
	class BladeShooterImpl;
	std::unique_ptr<BladeShooterImpl> m_impl;

};

#endif /* SRC_GAME_OBJECTS_BLADESHOOTER_H_ */
