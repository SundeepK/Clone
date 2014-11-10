#include "PhysicsTimeStepSystem.h"
#include <GL/gl.h>
#include <GL/glu.h>


class PhysicsTimeStepSystem::PhysicsTimeStepSystemImpl{

public:

	PhysicsTimeStepSystemImpl(b2World& b2World) : m_world(&b2World){}
	~PhysicsTimeStepSystemImpl(){}

    std::unique_ptr<b2World> m_world;
    float m_fixedTimestepAccumulator = 0.0f;
    float m_fixedTimestepAccumulatorRatio = 0.0f;

    const float FIXED_TIMESTEP = 1.0f / 60.0f;
    const int MAX_STEPS = 5;
    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;

    void setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer){
        m_world->SetDebugDraw(&box2dDEbugDrawer);
    }

    void update(std::vector<sf::Event>& events, float dt, PhysicsInterpolatorSystem& physicsInterpolator, PlayerControlsSystem& controlSystem){
        m_fixedTimestepAccumulator += dt/1000;
        const int steps = static_cast<int>(floor(m_fixedTimestepAccumulator / FIXED_TIMESTEP));

        if (steps > 0)
    	{
    		m_fixedTimestepAccumulator -= steps * FIXED_TIMESTEP;
    	}

    	assertAccumilation();
        m_fixedTimestepAccumulatorRatio = m_fixedTimestepAccumulator / FIXED_TIMESTEP;
        const int clampedSteps = std::min(steps, MAX_STEPS) <= 0 ? 1 : std::min(steps, MAX_STEPS);
    	for (int i = 0; i < clampedSteps; ++ i)
    	{
    		physicsInterpolator.resetComponents();
    		controlSystem.update(events, dt);
    		step(FIXED_TIMESTEP);
    	}

    	m_world->ClearForces();
    	physicsInterpolator.interpolateComponents(m_fixedTimestepAccumulatorRatio);

    }

    void step(float dt){
        m_world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }

    void assertAccumilation(){
    	assert (
    		"Accumulator must have a value lesser than the fixed time step" &&
    		m_fixedTimestepAccumulator < FIXED_TIMESTEP + FLT_EPSILON
    	);
    }

    void drawDebug() {
    	m_world->DrawDebugData();
    }

};

PhysicsTimeStepSystem::PhysicsTimeStepSystem(b2World& b2World) : m_impl(new PhysicsTimeStepSystemImpl(b2World))
{

}

PhysicsTimeStepSystem::~PhysicsTimeStepSystem(){}

void PhysicsTimeStepSystem::update(std::vector<sf::Event>& events, float dt, PhysicsInterpolatorSystem& physicsInterpolator, PlayerControlsSystem& controlSystem) {
	m_impl->update(events, dt, physicsInterpolator, controlSystem);
}

void PhysicsTimeStepSystem::setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer) {
	m_impl->setDebugDraw(box2dDEbugDrawer);
}

void PhysicsTimeStepSystem::drawDebug() {
	m_impl->drawDebug();
}

void PhysicsTimeStepSystem::step(float dt) {
	m_impl->step(dt);
}
