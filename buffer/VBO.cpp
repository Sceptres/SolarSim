#include "VBO.h"

VBO::VBO(GLfloat verticies[], GLsizeiptr size) {
    glGenBuffers(1, &(this->id));
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}

GLuint VBO::getId() {
    return this->id;
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
    glDeleteBuffers(1, &(this->id));
}