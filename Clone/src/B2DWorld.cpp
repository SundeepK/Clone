#include "B2DWorld.h"

B2DWorld::B2DWorld(float gravity) : m_world(b2Vec2(0.f, gravity))
{
    m_world.SetAutoClearForces(false);
    m_world.SetAllowSleeping(true);
}

B2DWorld::~B2DWorld()
{
}

void B2DWorld::setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer){
    m_world.SetDebugDraw(&box2dDEbugDrawer);
}


b2Body* B2DWorld::createB2Body(B2Builder* builder){
    return builder->build(m_world);
}

void B2DWorld::update(float dt){
    m_fixedTimestepAccumulator += dt;
    const int steps = floor(m_fixedTimestepAccumulator / FIXED_TIMESTEP);

    if (steps > 0)
	{
		m_fixedTimestepAccumulator -= steps * FIXED_TIMESTEP;
	}

	assertAccumilation();
    m_fixedTimestepAccumulatorRatio = m_fixedTimestepAccumulator / FIXED_TIMESTEP;

    const int clampedSteps = std::min(steps, MAX_STEPS);
	for (int i = 0; i < clampedSteps; ++ i)
	{
		resetStates();
		step(FIXED_TIMESTEP);
	}

    m_world.DrawDebugData();

	m_world.ClearForces();

    //smooth positions via interpolation
	interpolateStates();

}

void B2DWorld::assertAccumilation(){
	assert (
		"Accumulator must have a value lesser than the fixed time step" &&
		m_fixedTimestepAccumulator < FIXED_TIMESTEP + FLT_EPSILON
	);
}

void B2DWorld::step(float dt){
    m_world.Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void B2DWorld::interpolateStates(){
}

void B2DWorld::resetStates(){
}





