#include <opengl/TextureLoader.h>

TextureLoader::TextureLoader() {
}

TextureLoader::~TextureLoader() {
}

//GLuint TextureLoader::loadAsOpenglTexture(Texcoords* texCoordsComp) {
//		glGenTextures(1, &texCoordsComp->texture);
//		glBindTexture(GL_TEXTURE_2D, texCoordsComp->texture);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texCoordsComp->image.getSize().x,
//				texCoordsComp->image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,
//				texCoordsComp->image.getPixelsPtr());
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//				GL_LINEAR_MIPMAP_LINEAR);
//		return texCoordsComp->texture;
//}

GLuint TextureLoader::loadAsOpenglTexture(GLuint& gluint, sf::Image& image) {
		glGenTextures(1, &gluint);
		glBindTexture(GL_TEXTURE_2D,gluint);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x,
				image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,
				image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		return gluint;
}
