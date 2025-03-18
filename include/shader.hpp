#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include "glad/glad.h"
#include <string>

class Shader {
public:
    GLuint id;

    explicit Shader(const GLenum type, const std::string &source = std::string()) {
        id = glCreateShader(type);
        if (!source.empty())
            compile(source);
    }

    void compile(const std::string &source) const;

    void load(const std::string &filename) const;

    static std::string loadSource(const std::string &filename);

    ~Shader() {
        glDeleteShader(id);
    }
};

class ShaderProgram {
public:
    ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

    ~ShaderProgram() {
        glDeleteProgram(id);
    }

    void use() const {
        glUseProgram(id);
    }

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniformVec(const std::string &name, const float *value, int dims) const;

    void setUniformMat(const std::string &name, const float *value, int rowCols) const;

private:
    GLuint id;
};

#endif //GL_SHADER_HPP
