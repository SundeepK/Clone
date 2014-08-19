#include <systems/OpenGLTextureRenderer.h>

OpenGLTextureRenderer::OpenGLTextureRenderer() :
		Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()) {

}

OpenGLTextureRenderer::~OpenGLTextureRenderer() {
}

void OpenGLTextureRenderer::render() {
	auto entities = getEntities();
    const float M2P=30;

	for (auto& entity : entities) {

        auto bn = entity.getComponent<PhysicsComponent>().physicsBody;
		b2PolygonShape* shape = ((b2PolygonShape*) bn->GetFixtureList()->GetShape());
		std::vector<b2Vec2> points(shape->GetVertexCount());
		for (int i = 0; i < shape->GetVertexCount(); i++) {
			points[i] = (shape)->GetVertex(i);
		}

		glPushMatrix();
		b2Vec2 center = bn->GetPosition();
		float angle = bn->GetAngle();
		glTranslatef(center.x * M2P, center.y * M2P, 0.0f);
		glRotatef(angle * 180.0 / M_PI, 0, 0, 1);

		Texcoords *tex = (Texcoords*) bn->GetUserData();
		glBegin (GL_POLYGON); //begin drawing of polygon
		for (int i = 0; i < shape->GetVertexCount(); i++) {
			if (tex) {
				glTexCoord2d(tex->textCoords[i].x, tex->textCoords[i].y);
			}
			glVertex2f(points[i].x * M2P, points[i].y * M2P);
		}
		glEnd(); //end drawing of polygon
		glPopMatrix();
	}
}
