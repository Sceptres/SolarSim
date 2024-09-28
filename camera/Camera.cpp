#include "Camera.hpp"

Camera::Camera(const glm::vec3 startPos, GLfloat fov, GLfloat aspectRatio, GLfloat nearPlaneDistance, GLfloat farPlaneDistance) {
    this->position = glm::vec3(startPos.x, startPos.y, startPos.z);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, this->position);
    this->projection = glm::perspective(fov, aspectRatio, nearPlaneDistance, farPlaneDistance);
}

void Camera::Apply(ShaderProgram& shaderProgram) {
    shaderProgram.setMat4("view", this->view);
    shaderProgram.setMat4("projection", this->projection);
}