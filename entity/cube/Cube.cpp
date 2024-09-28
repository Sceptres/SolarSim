#include "Cube.hpp"

GLfloat Cube::verts[] = {
    // Positions            // Colors (R, G, B)
    // Back face (green)
    -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  // Vertex 0
    1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  // Vertex 1
    1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  // Vertex 2
    -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  // Vertex 3

    // Front face (red)
    -1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,  // Vertex 4
    1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,  // Vertex 5
    1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,  // Vertex 6
    -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,  // Vertex 7

    // Left face (blue)
    -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,  // Vertex 8
    -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f,  // Vertex 9
    -1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f,  // Vertex 10
    -1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f,  // Vertex 11

    // Right face (aqua)
    1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 1.0f,  // Vertex 12
    1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 1.0f,  // Vertex 13
    1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,  // Vertex 14
    1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 1.0f,  // Vertex 15

    // Bottom face (yellow)
    -1.0f, -1.0f,  1.0f,   1.0f, 1.0f, 0.0f,  // Vertex 16
    1.0f, -1.0f,  1.0f,   1.0f, 1.0f, 0.0f,  // Vertex 17
    1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 0.0f,  // Vertex 18
    -1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 0.0f,  // Vertex 19

    // Top face (futchsia)
    -1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,  // Vertex 20
    1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,  // Vertex 21
    1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 1.0f,  // Vertex 22
    -1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 1.0f   // Vertex 23
};

GLuint Cube::indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,

    // Front face
    4, 5, 6,
    6, 7, 4,

    // Left face
    8, 9, 10,
    10, 11, 8,

    // Right face
    12, 13, 14,
    14, 15, 12,

    // Bottom face
    16, 17, 18,
    18, 19, 16,

    // Top face
    20, 21, 22,
    22, 23, 20
};

VBO Cube::InstantiateVBO() {
    VBO vbo(Cube::verts, sizeof(Cube::verts));
    return vbo;
}

EBO Cube::InstantiateEBO() {
    EBO ebo(Cube::indices, sizeof(Cube::indices));
    return ebo;
}

void Cube::LinkAttribs(VAO& vao) {
    GLuint stride = 6 * sizeof(float);
	vao.LinkBuffers(0, stride, (void*) 0);
	vao.LinkBuffers(1, stride, (void*) (3 * sizeof(float)));
}

Cube::Cube(glm::vec3 initPosition) {
    this->position = glm::vec3(0.0);
    this->model = glm::mat4(1.0f);
    this->setPosition(initPosition);
}

glm::vec3 Cube::getPosition() {
    return this->position;
}

void Cube::MoveTo(glm::vec3 newPosition) {
    this->setPosition(newPosition);
}

void Cube::UpdateShader(ShaderProgram& shaderProgram) {
    shaderProgram.setMat4("model", this->model);
}

void Cube::Render() {
    glDrawElements(GL_TRIANGLES, sizeof(Cube::indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Cube::setPosition(glm::vec3 newPosition) {
    this->position.x = newPosition.x;
    this->position.y = newPosition.y;
    this->position.z = newPosition.z;
    this->model = glm::mat4(1.0f);
    this->model = glm::translate(this->model, this->position);
}