#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragCode = ReadFile(fragmentPath);
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragCode.c_str();

    // shader Program
    m_ShaderID = glCreateProgram();
    setUniforms();

    CompileShader(GL_VERTEX_SHADER, "VERTEX", vShaderCode);
    CompileShader(GL_FRAGMENT_SHADER, "FRAGMENT", fShaderCode);

    if (geometryPath != nullptr)
    {
        const char* gShaderCode = ReadFile(geometryPath).c_str();
        CompileShader(GL_GEOMETRY_SHADER, "GEOMETRY", gShaderCode);
    }

    glLinkProgram(m_ShaderID);
    CheckCompileErrors(m_ShaderID, "PROGRAM");
}

void Shader::setUniforms()
{
    glBindAttribLocation(m_ShaderID, 0, "aPosition");
    glBindAttribLocation(m_ShaderID, 1, "aTexCoord");
    glBindAttribLocation(m_ShaderID, 3, "aNormal");
}

unsigned int Shader::getID()
{
    return m_ShaderID;
}

void Shader::Bind() const
{
    glUseProgram(m_ShaderID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, Vector3 vec) const
{
    glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), vec[0], vec[1], vec[2]);
}

void Shader::setMat4(const std::string& name, const Matrix4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader()
{
    glUseProgram(0);
    glDeleteProgram(m_ShaderID);
}

Shader &Shader::operator= (Shader &rhs)
{
    std::swap(m_ShaderID, rhs.m_ShaderID);
    return *this;
}

void Shader::CompileShader(GLenum type, const char* charType, const char* shaderCode)
{
    unsigned int localShader = glCreateShader(type);
    glShaderSource(localShader, 1, &shaderCode, NULL);
    glCompileShader(localShader);
    CheckCompileErrors(localShader, charType);

    glAttachShader(m_ShaderID, localShader);
    glDeleteShader(localShader);
}

void Shader::CheckCompileErrors(GLuint shaderID, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

std::string Shader::ReadFile(const char* filePath)
{
    std::ifstream fileInput(filePath);
    if (!fileInput.good())
    {
        std::cout << "File failed to load: " << filePath;
    }

    return std::string(
        std::istreambuf_iterator<char>(fileInput),
        std::istreambuf_iterator<char>()
    );
}