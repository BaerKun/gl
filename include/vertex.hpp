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

    void setVertexAttribute(int location, int count, GLenum type, int stride, GLuint64 offset) const;

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

    VertexBuffer(const void *data, const int size) {
        loadData(data, size);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void loadData(const void *data, int size) const;

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

    ElementBuffer(const void *data, const int size) {
        loadData(data, size);
    }

    void loadData(const void *data, int size) const;

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
    VertexSet(const VertexBuffer *vbo, const VertexArray *vao, const ElementBuffer *ebo = nullptr) {
        this->vbo = vbo;
        this->vao = vao;
        this->ebo = ebo;
    }

    VertexSet(const void *buff, std::vector<int> &count,
              const VertexBuffer *vbo = nullptr, const VertexArray *vao = nullptr);

    void bindElemBuff(const ElementBuffer *ebo) {
        this->ebo = ebo;
    }

    void draw(GLenum mode, int count) const;

private:
    const VertexArray *vao;
    const VertexBuffer *vbo;
    const ElementBuffer *ebo;
};

#endif //GL_VERTEX_HPP
