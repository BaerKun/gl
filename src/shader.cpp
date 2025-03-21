#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

static char errorLog[256];

static inline void uniformNotFound(const std::string &name) {
    std::cerr << "Error: Uniform " << name << " not found." << std::endl;
}

std::string Shader::loadSource(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();
    return content;
}

void Shader::compile(const std::string &source) const {
    int success;
    const char *str = source.c_str();

    glShaderSource(id, 1, &str, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 256, nullptr, errorLog);
        std::cerr << "Shader Compilation Error:" << std::endl << errorLog;
        std::memset(errorLog, 0, 256);
    }
}

void Shader::load(const std::string &filename) const {
    const std::string source = loadSource(filename);
    if (!source.empty())
        compile(source.c_str());
}

ShaderProgram::ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader) {
    id = glCreateProgram();
    glAttachShader(id, vertexShader.id);
    glAttachShader(id, fragmentShader.id);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 256, &success, errorLog);
        std::cerr << "Shader Program Link Error:" << std::endl << errorLog << std::endl;
    }
}

void ShaderProgram::setUniform(const std::string &name, const int value) const {
    const GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1)
        uniformNotFound(name);
    else
        glUniform1i(location, value);
}

void ShaderProgram::setUniform(const std::string &name, const float value) const {
    const GLint location = glGetUniformLocation(id, name.c_str());
    if (location == -1)
        uniformNotFound(name);
    else
        glUniform1f(location, value);
}

void ShaderProgram::setUniformVec(const std::string &name, const float *value, const int dims) const {
    const GLint location = glGetUniformLocation(this->id, name.c_str());
    if (location == -1) {
        uniformNotFound(name);
        return;
    }
    switch (dims) {
        case 2:
            glUniform2fv(location, 1, value);
            break;
        case 3:
            glUniform3fv(location, 1, value);
            break;
        case 4:
            glUniform4fv(location, 1, value);
        default:
            break;
    }
}

void ShaderProgram::setUniformMat(const std::string &name, const float *value, const int rowCols) const {
    const GLint location = glGetUniformLocation(this->id, name.c_str());
    if (location == -1) {
        uniformNotFound(name);
        return;
    }
    switch (rowCols) {
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
