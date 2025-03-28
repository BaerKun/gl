#include <numeric>
#include "vertex.hpp"


void VertexArray::attribute(const GLuint location, const GLint count, const GLenum type, const GLint stride,
                            const GLuint64 offset) const {
    bind();
    glVertexAttribPointer(location, count, type, GL_FALSE, stride, reinterpret_cast<void *>(offset));
    glEnableVertexAttribArray(location);
}

void VertexBuffer::loadData(const void *data, const GLint64 size) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ElementBuffer::loadData(const void *data, const GLint64 size) const {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexSet::VertexSet(const void *buff, const GLint64 numVertices, const std::vector<GLint> &dimsEachProperty){
    const GLint dimsEachVertex = std::accumulate(dimsEachProperty.begin(), dimsEachProperty.end(), 0);
    const GLint sizeEachVertex = dimsEachVertex * static_cast<GLint>(sizeof(float));
    const GLint64 sizeBuff = numVertices * sizeEachVertex;
    const GLuint numProperties = dimsEachProperty.size();
    GLuint64 offset = 0;

    vbo_ = new VertexBuffer(buff, sizeBuff);
    vao_ = new VertexArray();

    for (GLuint i = 0; i < numProperties; ++i){
        vao_->attribute(i, dimsEachProperty[i], GL_FLOAT, sizeEachVertex, offset);
        offset += dimsEachProperty[i] * sizeof (float);
    }
}

void VertexSet::draw(const GLenum mode, const GLint count, const ElementBuffer *ebo) const {
    vbo_->bind();
    vao_->bind();

    if (ebo != nullptr) {
        ebo->bind();
        glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(mode, 0, count);
    }
}
