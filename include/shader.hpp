#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include "glad/glad.h"

class Shader {
public:
    GLuint id;

    explicit Shader(GLenum type) {
        id = glCreateShader(type);
    }

    void compile(const char *source) const;

    void load(const char *filename) const;

    ~Shader() {
        glDeleteShader(id);
    }
};

class ShaderProgram {
public:
    ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

    ~ShaderProgram() {
        glDeleteProgram(id);
    };

    void use() const {
        glUseProgram(this->id);
    }

    void setUniform(const char *name, float value) const;

    void setUniform(const char *name, int value) const;

    void setUniformv(const char *name, const float *value, int count) const;

    void setUniformm(const char *name, const float *value, int rowcols) const;

private:
    GLuint id;
};

#endif //GL_SHADER_HPP
