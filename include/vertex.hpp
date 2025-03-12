#ifndef GL_VERTEX_HPP
#define GL_VERTEX_HPP

#include "glad/glad.h"
#include <vector>

class VertexArray {
public:
    GLuint id{};

    VertexArray() {
        glGenVertexArrays(1, &id);
    }

    void bind() const {
        glBindVertexArray(id);
    }

    static void unbind() {
        glBindVertexArray(0);
    }

    void attribute(GLuint location, GLint count, GLenum type, GLint stride, GLuint64 offset) const;

    ~VertexArray() {
        glDeleteVertexArrays(1, &id);
    }
};

class VertexBuffer {
public:
    GLuint id{};

    VertexBuffer() {
        glGenBuffers(1, &id);
    }

    VertexBuffer(const void *data, const GLint64 size) {
        glGenBuffers(1, &id);
        loadData(data, size);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void loadData(const void *data, GLint64 size) const;

    static void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &id);
    }
};

class ElementBuffer {
public:
    GLuint id{};

    ElementBuffer() {
        glGenBuffers(1, &id);
    }

    ElementBuffer(const void *data, const GLint64 size) {
        glGenBuffers(1, &id);
        loadData(data, size);
    }

    void loadData(const void *data, GLint64 size) const;

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    static void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~ElementBuffer() {
        glDeleteBuffers(1, &id);
    }
};

class VertexSet {
public:
    VertexSet(const void *buff, GLint64 numVertices, const std::vector<GLint> &dimsEachProperty);

    void draw(GLenum mode, GLint count, const ElementBuffer *ebo = nullptr) const;

    ~VertexSet(){
        delete vao_;
        delete vbo_;
    }

private:
    const VertexArray *vao_;
    const VertexBuffer *vbo_;
};

#endif //GL_VERTEX_HPP
