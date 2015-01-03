#include <systems/OpenGLTextureRenderer.h>
#include <opengl/TextureLoader.h>

class OpenGLTextureRenderer::OpenGLTextureRendererImpl{

public:
	OpenGLTextureRendererImpl(){
	}

	~OpenGLTextureRendererImpl(){
	}

	void render(std::vector<anax::Entity>& entities);

};

void OpenGLTextureRenderer::OpenGLTextureRendererImpl::render(std::vector<anax::Entity>& entities) {
	const float M2P = 30.0f;
	for (auto entity : entities) {

		if(!entity.isActivated() || !entity.isValid()) continue;

		auto& texCoordsComp = entity.getComponent<Texcoords>();
		auto& physicsComp = entity.getComponent<PhysicsComponent>();

		auto& texCoordsVec = texCoordsComp.textCoords;

		if(texCoordsVec.size() <= 0)
			continue;

		b2Body* body = physicsComp.physicsBody;

		glBindTexture(GL_TEXTURE_2D, texCoordsComp.texture);
				TextureLoader::checkError("glBindTexture");

//		glDisableClientState(GL_NORMAL_ARRAY);
//		TextureLoader::checkError("glDisableClientState");
//		glDisableClientState(GL_COLOR_ARRAY);
//		TextureLoader::checkError("glDisableClientState");

		b2PolygonShape* shape =
				((b2PolygonShape*) body->GetFixtureList()->GetShape());
		std::vector<b2Vec2> points(shape->GetVertexCount());
		for (int i = 0; i < shape->GetVertexCount(); i++) {
			points[i] = (shape)->GetVertex(i);
		}

		glPushMatrix();

//		b2Vec2 center = physicsComp.smoothedPosition;
		b2Vec2 center = (body->GetPosition());

		float angle = body->GetAngle();
		glTranslatef(static_cast<float>(floor(center.x * M2P)), static_cast<float>(floor(center.y * M2P)), 0.0f);
		glRotatef(angle * 180.0 / M_PI, 0, 0, 1);

		glBegin(GL_POLYGON); //begin drawing of polygon
		for (int i = 0; i < shape->GetVertexCount(); i++) {
			glTexCoord2d(texCoordsVec[i].x, texCoordsVec[i].y);
			glVertex2f(floor(points[i].x * M2P), floor(points[i].y * M2P));
		}
		glEnd(); //end drawing of polygon
		glPopMatrix();

		TextureLoader::checkError("gen");

	}
}


OpenGLTextureRenderer::OpenGLTextureRenderer() : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()), m_impl(new OpenGLTextureRendererImpl()) {
}

OpenGLTextureRenderer::~OpenGLTextureRenderer() {
}

void OpenGLTextureRenderer::render() {
	auto entities = getEntities();
	m_impl->render(entities);
}
