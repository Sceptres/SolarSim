#ifndef VAO_CLASS

#define VAO_CLASS

#include <glad/glad.h>
#include "../buffer/VBO.h"

class VAO {
    public:
        VAO();
        void Bind();
        void Unbind();
        void Delete();
        void LinkVBO(VBO vbo);
        GLuint getId();

    private:
        GLuint id;
};

#endif