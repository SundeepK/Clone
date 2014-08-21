#ifndef PHYSICSINTERPOLATORSYSTEM_H_
#define PHYSICSINTERPOLATORSYSTEM_H_


#include <anax/System.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <components/Texcoords.h>
#include <components/PhysicsComponent.h>
#include <anax/Component.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>
#include <vector>
#include <iostream>

class PhysicsInterpolatorSystem :  public anax::System<PhysicsInterpolatorSystem> {
public:
	PhysicsInterpolatorSystem();
	virtual ~PhysicsInterpolatorSystem();

	void resetComponents();
	void interpolateComponents(float fixedTimestepAccumulatorRatio);
};

#endif /* PHYSICSINTERPOLATORSYSTEM_H_ */
