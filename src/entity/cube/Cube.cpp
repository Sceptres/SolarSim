#include "Cube.hpp"

Color green(0.0f, 1.0f, 0.0f);
Color red(1.0f, 0.0f, 0.0f);
Color blue(0.0f, 0.0f, 1.0f);
Color aqua(0.0f, 1.0f, 1.0f);
Color yellow(1.0f, 1.0f, 0.0f);
Color futchsia(1.0f, 0.0f, 1.0f);

GLfloat Cube::verts[] = {
    // Positions            // Colors (R, G, B)
    // Back face (green)
    -1.0f, -1.0f, -1.0f,   green.r, green.g, green.b,  // Vertex 0
    1.0f, -1.0f, -1.0f,   green.r, green.g, green.b,  // Vertex 1
    1.0f,  1.0f, -1.0f,   green.r, green.g, green.b,  // Vertex 2
    -1.0f,  1.0f, -1.0f,   green.r, green.g, green.b,  // Vertex 3

    // Front face (red)
    -1.0f, -1.0f,  1.0f,   red.r, red.g, red.b,  // Vertex 4
    1.0f, -1.0f,  1.0f,   red.r, red.g, red.b,  // Vertex 5
    1.0f,  1.0f,  1.0f,   red.r, red.g, red.b,  // Vertex 6
    -1.0f,  1.0f,  1.0f,   red.r, red.g, red.b,  // Vertex 7

    // Left face (blue)
    -1.0f, -1.0f,  1.0f,   blue.r, blue.g, blue.b,  // Vertex 8
    -1.0f, -1.0f, -1.0f,   blue.r, blue.g, blue.b,  // Vertex 9
    -1.0f,  1.0f, -1.0f,   blue.r, blue.g, blue.b,  // Vertex 10
    -1.0f,  1.0f,  1.0f,   blue.r, blue.g, blue.b,  // Vertex 11

    // Right face (aqua)
    1.0f, -1.0f, -1.0f,   aqua.r, aqua.g, aqua.b,  // Vertex 12
    1.0f, -1.0f,  1.0f,   aqua.r, aqua.g, aqua.b,  // Vertex 13
    1.0f,  1.0f,  1.0f,   aqua.r, aqua.g, aqua.b,  // Vertex 14
    1.0f,  1.0f, -1.0f,   aqua.r, aqua.g, aqua.b,  // Vertex 15

    // Bottom face (yellow)
    -1.0f, -1.0f,  1.0f,   yellow.r, yellow.g, yellow.b,  // Vertex 16
    1.0f, -1.0f,  1.0f,   yellow.r, yellow.g, yellow.b,  // Vertex 17
    1.0f, -1.0f, -1.0f,   yellow.r, yellow.g, yellow.b,  // Vertex 18
    -1.0f, -1.0f, -1.0f,   yellow.r, yellow.g, yellow.b,  // Vertex 19

    // Top face (futchsia)
    -1.0f,  1.0f, -1.0f,   futchsia.r, futchsia.g, futchsia.b,  // Vertex 20
    1.0f,  1.0f, -1.0f,   futchsia.r, futchsia.g, futchsia.b,  // Vertex 21
    1.0f,  1.0f,  1.0f,   futchsia.r, futchsia.g, futchsia.b,  // Vertex 22
    -1.0f,  1.0f,  1.0f,   futchsia.r, futchsia.g, futchsia.b   // Vertex 23
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