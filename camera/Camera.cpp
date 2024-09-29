#include "Camera.hpp"

Camera::Camera(const glm::vec3 startPos, GLfloat fov, GLfloat aspectRatio, GLfloat nearPlaneDistance, GLfloat farPlaneDistance) {
    this->position = glm::vec3(startPos.x, startPos.y, startPos.z);
    this->target = glm::vec3(0);
    this->up = glm::vec3(0);
    this->UpdateStates(this->position, this->target);
    this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlaneDistance, farPlaneDistance);
}

void Camera::Apply(ShaderProgram& shaderProgram) {
    shaderProgram.setMat4("view", this->view);
    shaderProgram.setMat4("projection", this->projection);
}

void Camera::MoveTo(glm::vec3 newPosition) {
    this->position.x = newPosition.x;
    this->position.y = newPosition.y;
    this->position.z = newPosition.z;
    this->UpdateStates(this->position, this->target);
}

void Camera::LookAt(glm::vec3 target) {
    this->UpdateStates(this->position, target);
}

void Camera::UpdateStates(glm::vec3 pos, glm::vec3 target) {
    this->target.x = target.x;
    this->target.y = target.y;
    this->target.z = target.z;
    
    glm::vec3 camDirection = glm::normalize(this->position - this->target);
    glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(upVec, camDirection));
    glm::vec3 cameraUp = glm::normalize(glm::cross(camDirection, cameraRight));
    
    this->up.x = cameraUp.x;
    this->up.y = cameraUp.y;
    this->up.z = cameraUp.z;

    this->view = glm::lookAt(this->position, this->target, this->up);
}

glm::vec3 Camera::getPosition() {
    return this->position;
}