
#ifndef SRC_SYSTEMS_FILTERCOLLISIONSSYSTEM_H_
#define SRC_SYSTEMS_FILTERCOLLISIONSSYSTEM_H_

#include <anax/System.hpp>
#include <memory>

class FilterCollisionsSystem : public anax::System<FilterCollisionsSystem> {
public:
	FilterCollisionsSystem();
	~FilterCollisionsSystem();

	void filterCollisions();


private:
	class FilterCollisionsSystemImpl;
	std::unique_ptr<FilterCollisionsSystemImpl> m_impl;
};

#endif /* SRC_SYSTEMS_FILTERCOLLISIONSSYSTEM_H_ */
