#ifndef SRC_SYSTEMS_LEVELRESTARTSYSTEM_H_
#define SRC_SYSTEMS_LEVELRESTARTSYSTEM_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <memory>
#include <anax/System.hpp>
#include <levels/TmxBox2dLevelLoader.h>

class LevelRestartSystem : public anax::System<LevelRestartSystem> {
public:
	LevelRestartSystem(TmxBox2dLevelLoader& levelLoader);
	~LevelRestartSystem();

	void update();

private:
	class LevelRestartSystemImpl;
	std::unique_ptr<LevelRestartSystemImpl> m_impl;

};

#endif /* SRC_SYSTEMS_LEVELRESTARTSYSTEM_H_ */
