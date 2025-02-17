#ifndef OPENGL_VERTEX_ARRAY_HPP
#define OPENGL_VERTEX_ARRAY_HPP

#include "glad/glad.h"
#include <iostream>

extern GLuint CURRENT_VAO, CURRENT_VBO, CURRENT_EBO;

class VertexArray {
public:
    GLuint id;

    VertexArray();

    void bind() const;

    static inline void unbind(){
        glBindVertexArray(0);
    }

    void setVertexAttribute(int location, int count, GLenum type, int stride, GLuint64 offset) const;

    ~VertexArray();
};

class VertexBuffer{
public:
    GLuint id;

    VertexBuffer();

    void loadData(void *data, int size) const;

    void bind() const;

    static inline void unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

   ~VertexBuffer();
};

class ElementBuffer{
public:
    GLuint id;

    ElementBuffer();

    void loadData(void *data, int size) const;

    void bind() const;

    static inline void unbind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~ElementBuffer();
};

#endif //OPENGL_VERTEX_ARRAY_HPP
