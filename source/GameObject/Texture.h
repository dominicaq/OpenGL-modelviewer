#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

class Texture {
public:
	Texture(const char* path);
	uint8_t LoadTexture(const char* path);
	void clearTexture();

	GLuint getID();
	int width, height;

	void bind(unsigned int unit) const;
	void unbind() const;

private:
	unsigned int _textureID;
	int _numComponents;
};

#endif
