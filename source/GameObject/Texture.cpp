#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texture_path) {
    uint8_t success = LoadTexture(texture_path);
    if (success == 0) {
        std::cout << "ERROR: Failed to initialize texture\n";
    }
}

uint8_t Texture::LoadTexture(const char* texture_path) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texture_path, &width, &height, &_numComponents, 0);

    if (data == NULL) {
        std::cout << "ERROR: Invalid texture path: " << texture_path << "\n";
        return 0;
    }

    GLenum format = 0;
    switch (_numComponents) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            std::cout << "ERROR: Unsupported texture component" << "\n";
            return 0;
    }

    glGenTextures(1, &_textureID);

    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return 1;
}

GLuint Texture::getID() {
    return _textureID;
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clearTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &_textureID);
}