#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &(this->id));
}

GLuint VAO::getId() {
    return this->id;
}

void VAO::LinkVBO(VBO vbo) {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void VAO::Bind() {
    glBindVertexArray(this->id);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &(this->id));
}