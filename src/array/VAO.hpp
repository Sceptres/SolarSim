#ifndef VAO_CLASS

#define VAO_CLASS

#include <glad/glad.h>
#include "../buffer/Buffer.hpp"

class VAO {
    public:
        VAO();
        GLuint getId();
        void LinkBuffers(GLuint layout, GLuint stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();

    private:
        GLuint id;

};

#endif