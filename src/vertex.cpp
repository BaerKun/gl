#include "vertex.hpp"


void VertexArray::attribute(GLuint location, GLint count, GLenum type, GLint stride,
                            GLuint64 offset) const {
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

VertexSet::VertexSet(const void *buff, const GLint64 numVertices, const std::vector<GLint> &dimsEachProperty,
          const VertexBuffer **vbo, const VertexArray **vao){
    GLint dimsEachVertex = 0;
    for (const GLint dims : dimsEachProperty)
        dimsEachVertex += dims;

    const GLint sizeEachVertex = dimsEachVertex * static_cast<GLint>(sizeof(float));
    const GLint64 sizeBuff = numVertices * sizeEachVertex;

    _vbo = new VertexBuffer(buff, sizeBuff);
    _vao = new VertexArray();

    const GLuint numProperties = dimsEachProperty.size();
    GLuint64 offset = 0;
    for (GLuint i = 0; i < numProperties; ++i){
        _vao->attribute(i, dimsEachProperty[i], GL_FLOAT, sizeEachVertex, offset);
        offset += dimsEachProperty[i] * sizeof (float);
    }

    if (vbo != nullptr) *vbo = _vbo;
    if (vao != nullptr) *vao = _vao;
}

void VertexSet::draw(const GLenum mode, const GLint count, const ElementBuffer *ebo) const {
    _vbo->bind();
    _vao->bind();

    if (ebo != nullptr) {
        ebo->bind();
        glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(mode, 0, count);
    }
}
