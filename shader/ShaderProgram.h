#ifndef SHADER_PROGRAM_CLASS

#define SHADER_PROGRAM_CLASS

#include <glad/glad.h>
#include <iostream>

class ShaderProgram {
    public:
        ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
        void Activate();
        void Delete();
        GLuint getId();

    private:
        GLuint id;
};

#endif