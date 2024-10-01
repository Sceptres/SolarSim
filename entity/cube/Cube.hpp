#ifndef CUBE_CLASS

#define CUBE_CLASS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../buffer/VBO/VBO.hpp"
#include "../../buffer/EBO/EBO.hpp"
#include "../../array/VAO.hpp"
#include "../../shader/ShaderProgram.hpp"
#include "../Entity.hpp"

class Cube : public Entity {
    public:
        static VBO InstantiateVBO();
        static EBO InstantiateEBO();
        static void LinkAttribs(VAO& vao);
        Cube(glm::vec3 initPosition, GLfloat scale, GLfloat angle, glm::vec3 rotateAxis);
        void RevolveOnAxis(GLfloat angle);

    private:
        GLfloat revolveAngle;
        glm::vec3 revolveAxis;
        static GLfloat verts[];
        static GLuint indices[];
        virtual void Draw() const override;
        virtual void ApplyTransformations() override;
};

#endif