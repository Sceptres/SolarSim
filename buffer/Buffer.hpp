#ifndef BUFFER_CLASS

#define BUFFER_CLASS

#include <glad/glad.h>

class Buffer {
    protected:
        Buffer() {};
        GLuint id;

    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void Delete() = 0;
        GLuint getId();
};

#endif