#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Maths/glm.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const char* vertexPath = "Shaders/vertexShader.vert", const char* fragmentPath = "Shaders/fragmentShader.frag", const char* geometryPath = nullptr);
    ~Shader();

    unsigned int getID();
    void Bind() const;
    void UnBind() const;

    // Utility
    Shader& operator= (Shader& shader);
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, Vector3 vec) const;
    void setMat4(const std::string& name, const Matrix4& mat) const;

private:
    unsigned int m_ShaderID, m_lightBuffer;
    void setUniforms();

    std::string ReadFile(const char* filePath);
    void CompileShader(GLenum type, const char* charType, const char* shaderCode);
    void CheckCompileErrors(GLuint shaderID, std::string type);
};
#endif
