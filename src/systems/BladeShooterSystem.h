#ifndef SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_
#define SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_

#include <anax/System.hpp>
#include <memory.h>

class BladeShooterSystem : public anax::System<BladeShooterSystem> {
public:
	BladeShooterSystem();
	~BladeShooterSystem();

	void update();

private:
	class BladeShooterSystemImpl;
	std::unique_ptr<BladeShooterSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_BLADESHOOTERSYSTEM_H_ */
