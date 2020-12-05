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
    Shader();
    ~Shader();

    unsigned int getProgram();
    void Bind() const;
    void UnBind() const;

    void AddFragmentShader(const char* fileName);
    void AddVertexShader(const char* fileName);
    void AddGeometryShader(const char* fileName);
    void CompileShader();

    // Utility
    Shader& operator= (Shader& shader);
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, Vector3 vec) const;
    void setMat4(const std::string& name, const Matrix4& mat) const;

private:
    unsigned int program;

    std::string ReadFile(const char* filePath);
    void addProgram(GLenum type, const char* shaderCode);
    void GetCompileErrors(GLenum type);
};
#endif
