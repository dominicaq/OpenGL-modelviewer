#include "Shader.h"

Shader::Shader()
{
    program = glCreateProgram();
    if (program == 0)
        std::cout << "ERROR: Could not allocate memory for shader" << std::endl;

    glBindAttribLocation(program, 0, "aPosition");
    glBindAttribLocation(program, 1, "aTexCoord");
    glBindAttribLocation(program, 3, "aNormal");
}

void Shader::CompileShader()
{
    glLinkProgram(program);
    GetCompileErrors(GL_LINK_STATUS);

    glValidateProgram(program);
    GetCompileErrors(GL_VALIDATE_STATUS);
}

void Shader::addProgram(GLenum type, const char* fileName)
{
    std::string file = ReadFile(fileName);
    const char* shaderCode = file.c_str();

    unsigned int localShader = glCreateShader(type);
    glShaderSource(localShader, 1, &shaderCode, NULL);
    glCompileShader(localShader);
    GetCompileErrors(GL_COMPILE_STATUS);

    glAttachShader(program, localShader);
    glDeleteShader(localShader);
}

void Shader::GetCompileErrors(GLenum type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, type, &success);

    const char* charType = "";
    switch (type){
        case GL_COMPILE_STATUS:
            charType = "GL_COMPILE_STATUS";
        case GL_VALIDATE_STATUS:
            charType = "GL_VALIDATE_STATUS";
        case GL_LINK_STATUS:
            charType = "GL_LINK_STATUS";
    }

    if (success == 0)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_ERROR of type: " << charType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void Shader::AddVertexShader(const char* fileName)
{
    addProgram(GL_VERTEX_SHADER, fileName);
}

void Shader::AddFragmentShader(const char* fileName)
{
    addProgram(GL_FRAGMENT_SHADER, fileName);
}

void Shader::AddGeometryShader(const char* fileName)
{
    addProgram(GL_GEOMETRY_SHADER, fileName);
}

unsigned int Shader::getProgram()
{
    return program;
}

Shader::~Shader()
{
    glUseProgram(0);
    glDeleteProgram(program);
}

Shader& Shader::operator= (Shader& rhs)
{
    std::swap(program, rhs.program);
    return *this;
}

void Shader::Bind() const
{
    glUseProgram(program);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, Vector3 vec) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), vec[0], vec[1], vec[2]);
}

void Shader::setMat4(const std::string& name, const Matrix4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::string Shader::ReadFile(const char* filePath)
{
    std::ifstream fileInput(filePath);
    if (!fileInput.good())
        std::cout << "File failed to load: " << filePath;

    return std::string(
        std::istreambuf_iterator<char>(fileInput),
        std::istreambuf_iterator<char>()
    );
}