#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include "glad/glad.h"
#include <string>

class Shader {
public:
    GLuint id;

    explicit Shader(const GLenum type, const char *source = nullptr) {
        id = glCreateShader(type);
        if (source != nullptr)
            compile(source);
    }

    void compile(const char *source) const;

    void load(const char *filename) const;

    static std::string loadSource(const char *filename);

    ~Shader() {
        glDeleteShader(id);
    }
};

class ShaderProgram;
extern const ShaderProgram *currShaderProgram;

class ShaderProgram {
public:
    ShaderProgram(const Shader &vertexShader, const Shader &fragmentShader);

    ~ShaderProgram() {
        glDeleteProgram(id);
    }

    void use() const {
        glUseProgram(id);
        currShaderProgram = this;
    }

    void setUniform(const char *name, float value) const;

    void setUniform(const char *name, int value) const;

    void setUniformVec(const char *name, const float *value, int dims) const;

    void setUniformMat(const char *name, const float *value, int rowCols) const;

private:
    GLuint id;
};

#endif //GL_SHADER_HPP
