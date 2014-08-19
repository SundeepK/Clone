#ifndef OPENGLTEXTURERENDERER_H_
#define OPENGLTEXTURERENDERER_H_

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <components/Texcoords.h>
#include <components/PhysicsComponent.h>
#include <anax/System.hpp>
#include <anax/Component.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glut.h>

class OpenGLTextureRenderer : public anax::System<OpenGLTextureRenderer>  {
public:
	OpenGLTextureRenderer();
	virtual ~OpenGLTextureRenderer();

	void render();

};

#endif /* OPENGLTEXTURERENDERER_H_ */
