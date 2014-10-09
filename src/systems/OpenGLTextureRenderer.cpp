#include <systems/OpenGLTextureRenderer.h>

OpenGLTextureRenderer::OpenGLTextureRenderer() : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()) {

}

OpenGLTextureRenderer::~OpenGLTextureRenderer() {
}

void OpenGLTextureRenderer::render() {
	auto entities = getEntities();
	const float M2P = 30.0f;
	for (auto entity : entities) {

		if(!entity.isActivated() || !entity.isValid()) continue;

		auto& texCoordsComp = entity.getComponent<Texcoords>();
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
		auto& image = texCoordsComp.image;

		auto& texCoordsVec = texCoordsComp.textCoords;
		b2Body* body = physicsComp.physicsBody;

		glBindTexture(GL_TEXTURE_2D, texCoordsComp.texture);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

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

	}

}
