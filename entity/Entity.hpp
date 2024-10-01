#ifndef ENTITY_CLASS

#define ENTITY_CLASS

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../shader/ShaderProgram.hpp"

class Entity {
    public:
        glm::vec3 getPosition() const;
        virtual void MoveTo(glm::vec3 newPosition);
        void Render(ShaderProgram& shaderProgram);

    protected:
        glm::vec3 position;
        GLfloat scale;
        GLfloat angle;
        glm::vec3 rotateAxis;
        glm::mat4 model;
        Entity(glm::vec3 initPosition, GLfloat scale, GLfloat angle, glm::vec3 rotateAxis);
        virtual void setPosition(glm::vec3 newPosition);
        virtual void ApplyTransformations();
        virtual void UpdateShader(ShaderProgram& shaderProgram);
        virtual void Draw() const = 0;
};

#endif