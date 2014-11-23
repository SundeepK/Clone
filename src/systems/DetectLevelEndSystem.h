#ifndef DETECTLEVELENDSYSTEM_H_
#define DETECTLEVELENDSYSTEM_H_

#include <memory>
#include <anax/System.hpp>
#include <levels/TmxBox2dLevelLoader.h>

class DetectLevelEndSystem : public anax::System<DetectLevelEndSystem> {
public:
	DetectLevelEndSystem(TmxBox2dLevelLoader& tmxMapLoader);
	virtual ~DetectLevelEndSystem();

	void processEndLevel();

private:

	class DetectLevelEndSystemImpl;
	std::unique_ptr<DetectLevelEndSystemImpl> m_impl;
};

#endif /* DETECTLEVELENDSYSTEM_H_ */
