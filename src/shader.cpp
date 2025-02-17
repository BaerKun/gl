#include "shader.hpp"
#include <iostream>

GLuint CURRENT_SHADER_PROGRAM = 0;
static char errorLog[256];

void Shader::compile(const char *source) const {
    int success;

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(id, 256, nullptr, errorLog);
        std::cerr << "Shader Compilation Error:" << std::endl << errorLog;
        std::memset(errorLog, 0, 256);
        return;
    }
}

void Shader::load(const char *filename) const  {
    FILE *file = fopen(filename, "r");

    if(file == nullptr){
        std::cerr << "Failed to open shader source file: " << filename << std::endl;
        return;
    }

    std::fseek(file, 0, SEEK_END);
    size_t size = std::ftell(file);
    std::rewind(file);

    char *source = new char[size + 1];
    std::fread(source, 1, size, file);
    source[size] = '\0';

    compile(source);

    fclose(file);
    delete[] source;
}

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
    id = glCreateProgram();
    glAttachShader(id, vertexShader.id);
    glAttachShader(id, fragmentShader.id);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(id, 256, &success, errorLog);
        std::cerr << "Shader Program Link Error:" << std::endl << errorLog << std::endl;
    }
}

void ShaderProgram::use() const {
    glUseProgram(this->id);
    CURRENT_SHADER_PROGRAM = id;
}

void ShaderProgram::setUniform(const char *name, const int value) const {
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void ShaderProgram::setUniform(const char *name, const float value) const {
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void ShaderProgram::setUniformv(const char *name, const float *value, int count) const {
    GLint location = glGetUniformLocation(this->id, name);
    switch (count) {
        case 4:
            glUniform4fv(location, 1, value);
            break;
        case 3:
            glUniform3fv(location, 1, value);
            break;
        case 2:
            glUniform2fv(location, 1, value);
        default:
            break;
    }
}

void ShaderProgram::setUniformm(const char *name, const float *value, int rowcols) const {
    GLint location = glGetUniformLocation(this->id, name);
    switch (rowcols) {
        case 4:
            glUniformMatrix4fv(location, 1, GL_FALSE, value);
            break;
        case 3:
            glUniformMatrix3fv(location, 1, GL_FALSE, value);
            break;
        case 2:
            glUniformMatrix2fv(location, 1, GL_FALSE, value);
        default:
            break;
    }
}
