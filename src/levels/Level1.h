#ifndef LEVEL1_H_
#define LEVEL1_H_

#include <Box2D/Box2D.h>
#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>
#include <anax/World.hpp>
#include <anax/System.hpp>
#include <levels/Level.h>
#include <memory.h>
#include <levels/Level.h>
#include <systems/SensorSystem.h>
#include <levels/Box2dLis.h>

class LuaScriptLevel : public Level{
public:
	 LuaScriptLevel(b2World& b2dworld, std::string luaScriptLevel);
	 ~LuaScriptLevel();

	 void loadLevel(std::unordered_map<std::string, tmx::MapObject>& levelObjects);
	 void updateLevel();
	 void endLevel();

	 void BeginContact(b2Contact* contact);
	 void EndContact(b2Contact* contact);

private:
	 class LuaScriptLevelImpl;
	 std::unique_ptr<LuaScriptLevelImpl> m_impl;

};

#endif /* LEVEL1_H_ */
