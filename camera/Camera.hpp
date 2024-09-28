#ifndef CAMERA_CLASS

#define CAMERA_CLASS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader/ShaderProgram.hpp"

class Camera {
    public:
        Camera(const glm::vec3 startPos, GLfloat fov, GLfloat aspectRatio, GLfloat nearPlaneDistance, GLfloat farPlaneDistance);
        void Apply(ShaderProgram& shaderProgram);

    private:
        glm::vec3 position;
        glm::mat4 view;
        glm::mat4 projection;
};

#endif