#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path)
{
    m_TexturePath = path;

    if(m_TexturePath)
        LoadTexture(m_TexturePath);
}

void Texture::LoadTexture(const char* path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_numComponents, 0);

    if (data)
    {
        GLenum format = 0;
        if (m_numComponents == 1)
            format = GL_RED;
        else if (m_numComponents == 3)
            format = GL_RGB;
        else if (m_numComponents == 4)
            format = GL_RGBA;

        glGenTextures(1, &m_textureID);

        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Invalid texture path: " << path << "\n";
    }
}

GLuint Texture::getID()
{
    return m_textureID;
}

void Texture::Bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::ClearTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureID);
}