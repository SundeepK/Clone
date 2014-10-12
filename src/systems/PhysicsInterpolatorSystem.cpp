#include <systems/PhysicsInterpolatorSystem.h>
#include <Box2D/Box2D.h>
#include <components/Texcoords.h>
#include <components/PhysicsComponent.h>
#include <anax/Component.hpp>

class PhysicsInterpolatorSystem::PhysicsInterpolatorSystemImpl{

public:
	std::function<void (b2Body*, float, PhysicsComponent&)> m_resetComponents;
	std::function<void (b2Body*, float, PhysicsComponent&)> m_interpolateComponents;

	PhysicsInterpolatorSystemImpl(){
		m_resetComponents = [](b2Body* body, float fixedTimestepAccumulatorRatio, PhysicsComponent& physicsComp){
			physicsComp.smoothedPosition = physicsComp.previousPosition =body->GetPosition();
			physicsComp.smoothedAngle = physicsComp.previousAngle = body->GetAngle ();
		};

		m_interpolateComponents = [](b2Body* body, float fixedTimestepAccumulatorRatio, PhysicsComponent& physicsComp){
			const float oneMinusRatio = 1.0f - fixedTimestepAccumulatorRatio;

			physicsComp.smoothedPosition = (fixedTimestepAccumulatorRatio * body->GetPosition() + oneMinusRatio * physicsComp.previousPosition);
			physicsComp.smoothedAngle = floor(fixedTimestepAccumulatorRatio * body->GetAngle() + oneMinusRatio * physicsComp.previousAngle);
		};
}

~PhysicsInterpolatorSystemImpl(){
}


void processPhysics(std::vector<anax::Entity>& entities, float fixedTimestepAccumulatorRatio, std::function<void(b2Body*, float, PhysicsComponent&)>& callback) {
	for (auto entity : entities) {
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComp.physicsBody;
		if (body->GetType() == b2_staticBody) {
			continue;
		}
		callback(body, fixedTimestepAccumulatorRatio, physicsComp);
	}
}

};

PhysicsInterpolatorSystem::PhysicsInterpolatorSystem() : Base(anax::ComponentFilter().requires<PhysicsComponent>()), m_impl(new PhysicsInterpolatorSystemImpl()) {

}

PhysicsInterpolatorSystem::~PhysicsInterpolatorSystem() {
}

void PhysicsInterpolatorSystem::resetComponents() {
	auto entities = getEntities();
	m_impl->processPhysics(entities, 0, m_impl->m_resetComponents);
}

void PhysicsInterpolatorSystem::interpolateComponents(float fixedTimestepAccumulatorRatio) {
	auto entities = getEntities();
	m_impl->processPhysics(entities, fixedTimestepAccumulatorRatio, m_impl->m_interpolateComponents);
}
