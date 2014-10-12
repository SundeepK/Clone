#ifndef PHYSICSINTERPOLATORSYSTEM_H_
#define PHYSICSINTERPOLATORSYSTEM_H_


#include <anax/System.hpp>
#include <memory>

class PhysicsInterpolatorSystem :  public anax::System<PhysicsInterpolatorSystem> {
public:
	PhysicsInterpolatorSystem();
	virtual ~PhysicsInterpolatorSystem();

	void resetComponents();
	void interpolateComponents(float fixedTimestepAccumulatorRatio);

private:
	class PhysicsInterpolatorSystemImpl;
	std::unique_ptr<PhysicsInterpolatorSystemImpl> m_impl;
};

#endif /* PHYSICSINTERPOLATORSYSTEM_H_ */
