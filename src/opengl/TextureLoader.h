#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_


#include <SFML/OpenGL.hpp>
#include <components/Texcoords.h>

class TextureLoader {
public:
	TextureLoader();
	virtual ~TextureLoader();

	GLuint loadAsOpenglTexture(Texcoords& texCoords);

};

#endif /* TEXTURELOADER_H_ */
