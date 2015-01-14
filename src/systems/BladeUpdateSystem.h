#ifndef SRC_SYSTEMS_BLADEUPDATESYSTEM_H_
#define SRC_SYSTEMS_BLADEUPDATESYSTEM_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <memory>
#include <anax/System.hpp>


class BladeUpdateSystem : public anax::System<BladeUpdateSystem> {
public:
	BladeUpdateSystem();
	~BladeUpdateSystem();

	void update();

private:

	class BladeUpdateSystemImpl;
	std::unique_ptr<BladeUpdateSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_BLADEUPDATESYSTEM_H_ */
