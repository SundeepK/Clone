#ifndef SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_
#define SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_

#include <anax/System.hpp>
#include <memory.h>
#include <anax/World.hpp>
#include <Box2D/Box2D.h>

class BladeShooterSystem : public anax::System<BladeShooterSystem> {
public:
	BladeShooterSystem(b2World& box2dWorld);
	~BladeShooterSystem();

	void update();

private:
	class BladeShooterSystemImpl;
	std::unique_ptr<BladeShooterSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_ */
