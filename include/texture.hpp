#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP

#include "glad/glad.h"

class Texture {
public:
    GLuint id;
    int index;
    int width, height, channels;

    Texture(const char *path);

    ~Texture();

    void bind() const;

    static void setParam(GLenum param, GLenum value);

    void use() const;
};

#endif //OPENGL_TEXTURE_HPP
