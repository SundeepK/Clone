#include <systems/PhysicsInterpolatorSystem.h>

PhysicsInterpolatorSystem::PhysicsInterpolatorSystem() : Base(anax::ComponentFilter().requires<PhysicsComponent>()) {

}

PhysicsInterpolatorSystem::~PhysicsInterpolatorSystem() {
}

void PhysicsInterpolatorSystem::resetComponents() {
	auto entities = getEntities();
	for (auto entity : entities) {
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComp.physicsBody;

			if (body->GetType () == b2_staticBody)
			{
				continue;
			}

			physicsComp.smoothedPosition = physicsComp.previousPosition =body->GetPosition();
			physicsComp.smoothedAngle = physicsComp.previousAngle = body->GetAngle ();
		}
}

void PhysicsInterpolatorSystem::interpolateComponents(float fixedTimestepAccumulatorRatio) {

	const float oneMinusRatio = 1.0f - fixedTimestepAccumulatorRatio;

	auto entities = getEntities();
	for (auto entity : entities) {
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
		b2Body* body = physicsComp.physicsBody;
		if (body->GetType () == b2_staticBody)
		{
			continue;
		}
		physicsComp.smoothedPosition = fixedTimestepAccumulatorRatio * body->GetPosition() + oneMinusRatio * physicsComp.previousPosition;
		physicsComp.smoothedAngle = floor(fixedTimestepAccumulatorRatio * body->GetAngle() + oneMinusRatio * physicsComp.previousAngle);
	}

}
