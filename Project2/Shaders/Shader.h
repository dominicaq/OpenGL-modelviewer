#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include "Maths/glm.h"

#include "Transform.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();

    unsigned int getID();
    //void Update(const Transform& transform);
    void Bind();
    void UnBind();

    void Update(const Transform& transform);

    // Utility
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, glm::vec3 vec) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:    
    unsigned int m_ShaderID;

    void CompileShader(GLenum type, const char* charType, const char* shaderCode);
    void CheckCompileErrors(GLuint shader, std::string type);
    std::string ReadFile(const char* filePath);
};
#endif
