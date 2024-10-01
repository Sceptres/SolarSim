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

Cube::Cube(glm::vec3 initPosition, GLfloat scale, GLfloat angle, glm::vec3 rotateAxis) : 
    Entity(initPosition, scale, angle, rotateAxis) {
    this->revolveAxis = glm::vec3(0, 1, 0);
}

void Cube::RevolveOnAxis(GLfloat angle) {
    this->revolveAngle = angle;
}

void Cube::Draw() const {
    glDrawElements(GL_TRIANGLES, sizeof(Cube::indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Cube::ApplyTransformations() {
    Entity::ApplyTransformations();
    Entity::model = glm::rotate(Entity::model, glm::radians(this->revolveAngle), this->revolveAxis);
}