#ifndef VBO_CLASS

#define VBO_CLASS

#include <glad/glad.h>

class VBO {
    public:
        VBO(GLfloat verticies[], GLsizeiptr size);
        void Bind();
        void Unbind();
        void Delete();
        GLuint getId();

    private:
        GLuint id;
};

#endif