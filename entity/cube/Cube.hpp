#ifndef CUBE_CLASS

#define CUBE_CLASS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../buffer/VBO/VBO.hpp"
#include "../../buffer/EBO/EBO.hpp"
#include "../../array/VAO.hpp"
#include "../../shader/ShaderProgram.hpp"

class Cube {
    public:
        static VBO InstantiateVBO();
        static EBO InstantiateEBO();
        static void LinkAttribs(VAO& vao);
        Cube(glm::vec3 initPosition);
        glm::vec3 getPosition();
        void MoveTo(glm::vec3 newPosition);
        void UpdateShader(ShaderProgram& shaderProgram);
        void Render();

    private:
        glm::vec3 position;
        glm::mat4 model;
        static GLfloat verts[];
        static GLuint indices[];
        void setPosition(glm::vec3 newPosition);
};

#endif