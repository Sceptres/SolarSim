#include "VBO.hpp"

VBO::VBO(GLfloat verticies[], GLsizeiptr size) {
    glGenBuffers(1, &(Buffer::id));
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, Buffer::id);
}

void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
    glDeleteBuffers(1, &(Buffer::id));
}