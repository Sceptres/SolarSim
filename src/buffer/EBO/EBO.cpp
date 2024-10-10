#include "EBO.hpp"

EBO::EBO(GLuint indices[], GLsizeiptr size) {
    glGenBuffers(1, &(Buffer::id));
    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer::id);
}

void EBO::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
    glDeleteBuffers(1, &(Buffer::id));
}