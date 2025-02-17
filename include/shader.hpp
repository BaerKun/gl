#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include "glad/glad.h"
#include "glm.hpp"

extern GLuint CURRENT_SHADER_PROGRAM;

class Shader {
public:
    GLuint id;

    inline explicit Shader(GLenum type) {
        id = glCreateShader(type);
    }

    void compile(const char *source) const;

    void load(const char *filename) const;

    inline ~Shader() {
        glDeleteShader(id);
    }
};

class ShaderProgram {
public:
    ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

    inline ~ShaderProgram() {
        glDeleteProgram(id);
    };

    void use() const;

    void setUniform(const char *name, float value) const;

    void setUniform(const char *name, int value) const;

    void setUniformv(const char *name, const float *value, int count) const;

    void setUniformm(const char *name, const float *value, int rowcols) const;

private:
    GLuint id;
};

#endif //OPENGL_SHADER_HPP
