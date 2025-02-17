#include "vertex.hpp"


void VertexArray::setVertexAttribute(const int location, const int count, const GLenum type, const int stride,
                                     const GLuint64 offset) const {
    bind();
    glVertexAttribPointer(location, count, type, GL_FALSE, stride, reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(location);
}


void VertexBuffer::loadData(const void *data, const int size) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ElementBuffer::loadData(const void *data, const int size) const {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexSet::draw(const GLenum mode, const int count) const {
    vbo->bind();
    vao->bind();

    if (ebo != nullptr) {
        ebo->bind();
        glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(mode, 0, count);
    }
}
