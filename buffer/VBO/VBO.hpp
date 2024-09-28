#ifndef VBO_CLASS

#define VBO_CLASS

#include <glad/glad.h>
#include "../Buffer.hpp"

class VBO : public Buffer {
    public:
        VBO(GLfloat verticies[], GLsizeiptr size);
        void Bind() const override;
        void Unbind() const override;
        void Delete() override;

    private:
        GLuint id;
};

#endif