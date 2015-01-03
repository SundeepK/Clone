#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_


#include <SFML/OpenGL.hpp>
#include <components/Texcoords.h>
#include <GL/glut.h>


class TextureLoader {
public:
	TextureLoader();
	virtual ~TextureLoader();

    static GLuint loadAsOpenglTexture(Texcoords* texCoords);
    static GLuint loadAsOpenglTexture(GLuint& gluint, sf::Image& image);
    static GLuint checkError(const char *context);


};

#endif /* TEXTURELOADER_H_ */
