#include "Shader.h"

Shader::Shader(const char* vert_path, const char* frag_path) {
    _program = glCreateProgram();
    if (_program == 0) {
        std::cout << "ERROR: Could not create shader program" << "\n";
        return;
    }

    // Uniform attributes
    glBindAttribLocation(_program, 0, "aPosition");
    glBindAttribLocation(_program, 1, "aTexCoord");
    glBindAttribLocation(_program, 3, "aNormal");

    // Add vertex program
    if (addProgram(vert_path, GL_VERTEX_SHADER) == 0) {
        std::cout << "Failed to add vertex program: " << vert_path << "\n";
        return;
    }

    // Add fragment program
    if (addProgram(frag_path, GL_FRAGMENT_SHADER) == 0) {
        std::cout << "Failed to add fragment program: " << frag_path << "\n";
        return;
    }

    GLint program_success = 0;

    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &program_success);

    // ERROR: Link error
    if (program_success == 0) {
        printProgramStatus(GL_LINK_STATUS);
        return;
    }

    // Validate program and check status
    glValidateProgram(_program);
    glGetProgramiv(_program, GL_VALIDATE_STATUS, &program_success);

    // ERROR: Valdiation error
    if (program_success == 0) {
        printProgramStatus(GL_VALIDATE_STATUS);
        return;
    }
}

Shader::~Shader() {
    // Delete shader program
    glUseProgram(0);
    glDeleteProgram(_program);
}

void Shader::bind() const {
    glUseProgram(_program);
}

void Shader::unbind() const {
    glUseProgram(0);
}

uint8_t Shader::addProgram(const char* fpath, GLenum type) {
    std::string shader_src;
    uint8_t success = readFile(fpath, shader_src);

    // ERROR: Failed to read file
    if (success == 0) {
        std::cout << "Failed to read file: " << fpath << "\n";
        return 0;
    }

    // Create a local shader with type and src code
    const char* shader_src_cstr = shader_src.c_str();
    GLuint local_shader = glCreateShader(type);
    glShaderSource(local_shader, 1, &shader_src_cstr, NULL);
    glCompileShader(local_shader);

    GLint program_success = 0;
    glGetProgramiv(_program, GL_COMPILE_STATUS, &program_success);

    // ERROR: Shader failed to compile
    if (success == 0) {
        printProgramStatus(GL_COMPILE_STATUS);
        glDeleteShader(local_shader);
        return 0;
    }

    glAttachShader(_program, local_shader);
    glDeleteShader(local_shader);

    return 1;
}

void Shader::printProgramStatus(GLenum type) {
    GLint program_success = 0;
    glGetProgramiv(_program, type, &program_success);

    // ERROR: Program of GLenum type failed
    const int log_size = 1024;
    const char* enumString = std::to_string(type).c_str();
    GLchar info_log[log_size];

    glGetProgramInfoLog(_program, log_size, NULL, info_log);
    std::cout << "ERROR: PROGRAM_ERROR of type: " << enumString;
    std::cout << "\n" << info_log << "\n";
}

uint8_t Shader::readFile(const char* fpath, std::string& shader_src) {
    std::ifstream file(fpath);
    // ERROR: Failed to open file
    if (!file.is_open()) {
        return 0;
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    file.close();

    // Assign the contents to the output parameter
    shader_src = contents.str();

    return 1;
}

unsigned int Shader::getProgram() {
    return _program;
}

Shader& Shader::operator= (Shader& rhs) {
    // Assign lhs to rhs program
    std::swap(_program, rhs._program);
    return *this;
}

// Assign uniform attributes
// -----------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, Vector3 vec) const {
    glUniform3f(glGetUniformLocation(_program, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setMat4(const std::string& name, const Matrix4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}