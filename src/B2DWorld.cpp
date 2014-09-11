#include "B2DWorld.h"
#include <GL/gl.h>
#include <GL/glu.h>

B2DWorld::B2DWorld(b2World& b2World) : m_world(&b2World)
{

}


void B2DWorld::setDebugDraw(SFMLB2dDebugDraw& box2dDEbugDrawer){
    m_world->SetDebugDraw(&box2dDEbugDrawer);
}


b2Body* B2DWorld::createB2Body(B2Builder* builder){
    return builder->build(*m_world);
}

void B2DWorld::update(float dt, PhysicsInterpolatorSystem& physicsInterpolator, PlayerControlsSystem& controlSystem){
    m_fixedTimestepAccumulator += dt/1000;
    const int steps = static_cast<int>(floor(m_fixedTimestepAccumulator / FIXED_TIMESTEP));

    if (steps > 0)
	{
		m_fixedTimestepAccumulator -= steps * FIXED_TIMESTEP;
	}

	assertAccumilation();
    m_fixedTimestepAccumulatorRatio = m_fixedTimestepAccumulator / FIXED_TIMESTEP;
    const int clampedSteps = std::min(steps, MAX_STEPS);
	for (int i = 0; i < clampedSteps; ++ i)
	{
		physicsInterpolator.resetComponents();
		controlSystem.update(dt);
		step(FIXED_TIMESTEP);
	}

	m_world->ClearForces();
	physicsInterpolator.interpolateComponents(m_fixedTimestepAccumulatorRatio);

}

void B2DWorld::drawSquare(b2Vec2* points,b2Vec2 center,float angle)
{
const float M2P=30;
const float P2M=1/M2P;
     //   glColor3f(distribution(generator),distribution(generator),distribution(generator));
        glPushMatrix();
                glTranslatef(center.x*M2P,center.y*M2P,0);
                glRotatef(angle*180.0/M_PI,0,0,1);
                glBegin(GL_QUADS);
                        for(int i=0;i<4;i++)
                                glVertex2f(points[i].x*M2P,points[i].y*M2P);
                glEnd();
        glPopMatrix();
}

void B2DWorld::step(float dt){
    m_world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}


//void B2DWorld::update(float accumulator, ActionController<std::string>& actionController){
//
//        actionController.triggerCallbacks(m_fixedTimestepAccumulatorRatio);
//		step(FIXED_TIMESTEP);
//
////	m_world.ClearForces();
//
//    //smooth positions via interpolation
//	m_world.DrawDebugData();
//
//
//}

void B2DWorld::assertAccumilation(){
	assert (
		"Accumulator must have a value lesser than the fixed time step" &&
		m_fixedTimestepAccumulator < FIXED_TIMESTEP + FLT_EPSILON
	);
}

void B2DWorld::drawDebug() {
	m_world->DrawDebugData();
}
