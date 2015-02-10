#ifndef SRC_GAME_OBJECTS_ROPEBOX_H_
#define SRC_GAME_OBJECTS_ROPEBOX_H_

#include <memory.h>
#include <Box2D/Box2D.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <game-objects/GameEntityCreator.h>

class RopeBox : public GameEntityCreator  {
public:
	RopeBox();
	~RopeBox();

	void createEntity(const tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld);
	std::vector<std::string> getProperties();
	b2Body* createRope();

private:
	class RopeBoxImpl;
	std::auto_ptr<RopeBoxImpl> m_impl;
};



#endif /* SRC_GAME_OBJECTS_ROPEBOX_H_ */
