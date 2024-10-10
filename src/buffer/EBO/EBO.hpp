#ifndef EBO_CLASS 

#define EBO_CLASS

#include <glad/glad.h>
#include "../Buffer.hpp"

class EBO : public Buffer {
    public:
        EBO(GLuint indices[], GLsizeiptr size);
        void Bind() const override;
        void Unbind() const override;
        void Delete() override;
};

#endif