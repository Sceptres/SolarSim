#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &(this->id));
}

GLuint VAO::getId() {
    return this->id;
}

void VAO::LinkBuffers(GLuint layout, GLuint stride, void* offset) {
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
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