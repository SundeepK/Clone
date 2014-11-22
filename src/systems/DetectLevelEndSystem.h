#ifndef DETECTLEVELENDSYSTEM_H_
#define DETECTLEVELENDSYSTEM_H_

#include <memory>
#include <anax/System.hpp>

class DetectLevelEndSystem : public anax::System<DetectLevelEndSystem> {
public:
	DetectLevelEndSystem();
	virtual ~DetectLevelEndSystem();

	void processEndLevel();

private:

	class DetectLevelEndSystemImpl;
	std::unique_ptr<DetectLevelEndSystemImpl> m_impl;
};

#endif /* DETECTLEVELENDSYSTEM_H_ */
