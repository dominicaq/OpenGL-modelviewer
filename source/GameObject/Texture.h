#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

class Texture
{
public:
	const char* type;
	Texture(const char* path);
	void LoadTexture(const char* path);
	
	GLuint getID();

	void Bind(unsigned int unit) const;
	void UnBind() const;
	
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	void ClearTexture();

private:
	const char* m_TexturePath;
	unsigned int m_textureID;
	int m_Width, m_Height, m_numComponents;
};

#endif
