#ifndef SENSORSYSTEM_H_
#define SENSORSYSTEM_H_

#include <Box2D/Box2D.h>
#include <anax/System.hpp>
#include <memory>
#include <levels/Box2dLis.h>

class SensorSystem : public b2ContactListener, public anax::System<SensorSystem> {
public:
	SensorSystem();
	~SensorSystem();

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void registerb2ContactListener(b2ContactListener* listener);

private:

	std::vector<b2ContactListener*> m_listeners;
	class SensorSystemImpl;
	std::unique_ptr<SensorSystemImpl> m_impl;

};

#endif /* SENSORSYSTEM_H_ */
