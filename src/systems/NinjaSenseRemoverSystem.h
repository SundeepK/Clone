#ifndef SRC_SYSTEMS_NINJASENSEREMOVERSYSTEM_H_
#define SRC_SYSTEMS_NINJASENSEREMOVERSYSTEM_H_

#include <memory>
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class NinjaSenseRemoverSystem : public anax::System<NinjaSenseRemoverSystem> {
public:
	NinjaSenseRemoverSystem();
	~NinjaSenseRemoverSystem();

	void update();

private:

	class NinjaSenseRemoverSystemImpl;
	std::unique_ptr<NinjaSenseRemoverSystemImpl> m_impl;

};

#endif /* SRC_SYSTEMS_NINJASENSEREMOVERSYSTEM_H_ */
