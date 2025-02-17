#include "data_base.hpp"

GLuint CURRENT_VAO, CURRENT_VBO, CURRENT_EBO;

VertexArray::VertexArray() : id(){
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const{
    glBindVertexArray(id);
    CURRENT_VAO = id;
}

void VertexArray::setVertexAttribute(int location, int count, GLenum type, int stride, GLuint64 offset) const {
    if (CURRENT_VAO != id)
        bind();
    glVertexAttribPointer(location, count, type, GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(location);
}

VertexBuffer::VertexBuffer() : id(){
    glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    CURRENT_VBO = id;
}

void VertexBuffer::loadData(void *data, int size) const {
    if (CURRENT_VBO != id)
        bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

ElementBuffer::ElementBuffer() : id(){
    glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer(){
    glDeleteBuffers(1, &id);
}

void ElementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    CURRENT_EBO = id;
}

void ElementBuffer::loadData(void *indices, int size) const {
    if (CURRENT_EBO != id)
        bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}