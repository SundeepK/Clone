#include <systems/OpenGLTextureRenderer.h>

OpenGLTextureRenderer::OpenGLTextureRenderer() : Base(anax::ComponentFilter().requires<Texcoords, PhysicsComponent>()) {

}

OpenGLTextureRenderer::~OpenGLTextureRenderer() {
}

void OpenGLTextureRenderer::render() {
	auto entities = getEntities();
	const float M2P = 30;
	int s = entities.size();
	for (auto entity : entities) {
		auto& texCoordsComp = entity.getComponent<Texcoords>();
		auto& physicsComp = entity.getComponent<PhysicsComponent>();
		auto image = texCoordsComp.image;
		auto name = texCoordsComp.name;

		std::cout << name << "hello" << std::endl;

//		auto& texCoordsVec = texCoordsComp.textCoords;
//		b2Body* body = physicsComp.physicsBody;
//
//		//std::vector<b2Vec2> texCoordsVec = entity.getComponent<Texcoords>().textCoords;
//
////	    std::vector<b2Vec2> texCoordsVec;
////	    texCoordsVec.push_back(b2Vec2(0.0f, 1.f));
////	    texCoordsVec.push_back(b2Vec2(1.0f, 1.0f));
////	    texCoordsVec.push_back(b2Vec2(1.0f, 0.0f));
////	    texCoordsVec.push_back(b2Vec2(0.0f, 0.0f));
//
//		GLuint texture = 0;
//		{
//			if (!image.loadFromFile("1.png"))
//				return;
//			image.flipVertically();
//			glGenTextures(1, &texture);
//			glBindTexture(GL_TEXTURE_2D, texture);
//			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x,
//					image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,
//					image.getPixelsPtr());
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//					GL_LINEAR_MIPMAP_LINEAR);
//		}
//
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glDisableClientState(GL_NORMAL_ARRAY);
//		glDisableClientState(GL_COLOR_ARRAY);
//
//		b2PolygonShape* shape =
//				((b2PolygonShape*) body->GetFixtureList()->GetShape());
//		std::vector<b2Vec2> points(shape->GetVertexCount());
//		for (int i = 0; i < shape->GetVertexCount(); i++) {
//			points[i] = (shape)->GetVertex(i);
//		}
//
//		glPushMatrix();
//		b2Vec2 center = body->GetPosition();
//		float angle = body->GetAngle();
//		glTranslatef(center.x * M2P, center.y * M2P, 0.0f);
//		glRotatef(angle * 180.0 / M_PI, 0, 0, 1);
//
//		glBegin(GL_POLYGON); //begin drawing of polygon
//		for (int i = 0; i < shape->GetVertexCount(); i++) {
//				glTexCoord2d(texCoordsVec[i].x, texCoordsVec[i].y);
//			glVertex2f(points[i].x * M2P, points[i].y * M2P);
//		}
//		glEnd(); //end drawing of polygon
//		glPopMatrix();
	}

}
