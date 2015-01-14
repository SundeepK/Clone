#ifndef SRC_SYSTEMS_BREAKABLEJOINTSYSTEM_H_
#define SRC_SYSTEMS_BREAKABLEJOINTSYSTEM_H_

#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <Box2D/Box2D.h>

class BreakableJointSystem :  public b2ContactListener, public anax::System<BreakableJointSystem> {
public:
	BreakableJointSystem(b2World& b2World);
	~BreakableJointSystem();

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
	void update(float inverseDt);

private:

	class BreakableJointSystemImpl;
	std::unique_ptr<BreakableJointSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_BREAKABLEJOINTSYSTEM_H_ */
