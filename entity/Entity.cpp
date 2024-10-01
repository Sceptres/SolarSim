#include "Entity.hpp"

Entity::Entity(glm::vec3 initPosition, GLfloat scale, GLfloat angle, glm::vec3 rotateAxis) {
    this->position = glm::vec3(0.0);
    this->model = glm::mat4(1.0f);
    this->scale = scale/2;
    this->angle = angle;
    this->rotateAxis = rotateAxis;
    this->setPosition(initPosition);
}

void Entity::setPosition(glm::vec3 newPosition) {
    this->position.x = newPosition.x;
    this->position.y = newPosition.y;
    this->position.z = newPosition.z;
}

glm::vec3 Entity::getPosition() const {
    return this->position;
}

void Entity::MoveTo(glm::vec3 newPosition) {
    this->setPosition(newPosition);
}

void Entity::UpdateShader(ShaderProgram& shaderProgram) {
    this->ApplyTransformations();
    shaderProgram.setMat4("model", this->model);
}

void Entity::Render(ShaderProgram& shaderProgram) {
    this->UpdateShader(shaderProgram);
    this->ApplyTransformations();
    this->Draw();
}

void Entity::ApplyTransformations() {
    this->model = glm::mat4(1.0f);    
    this->model = glm::translate(this->model, this->position);

    if(this->rotateAxis != glm::vec3(0, 0, 0))
        this->model = glm::rotate(this->model, glm::radians(this->angle), this->rotateAxis);
    
    this->model = glm::scale(this->model, glm::vec3(this->scale));
}