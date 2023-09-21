#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "standardMath.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    Shader(const char* vert_path, const char* frag_path);
    ~Shader();

    unsigned int getProgram();
    void bind() const;
    void unbind() const;

    // Utility
    Shader& operator= (Shader& shader);

    // Set uniforms
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, Vector3 vec) const;
    void setMat4(const std::string& name, const Matrix4& mat) const;

private:
    unsigned int _program;

    void printProgramStatus(GLenum type);
    uint8_t addProgram(const char* shaderCode, GLenum type);
    uint8_t readFile(const char* fpath, std::string& shader_src);
};
#endif