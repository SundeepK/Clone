#ifndef SRC_SYSTEMS_REMOVEDEADENTITYSYSTEM_H_
#define SRC_SYSTEMS_REMOVEDEADENTITYSYSTEM_H_


#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <memory>
#include <anax/System.hpp>


class RemoveDeadEntitySystem : public anax::System<RemoveDeadEntitySystem> {
public:
	RemoveDeadEntitySystem(b2World& box2dWorld);
	~RemoveDeadEntitySystem();

	void update();

private:
	class RemoveDeadEntitySystemImpl;
	std::unique_ptr<RemoveDeadEntitySystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_REMOVEDEADENTITYSYSTEM_H_ */
