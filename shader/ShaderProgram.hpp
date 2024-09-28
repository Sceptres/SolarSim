#ifndef SHADER_PROGRAM_CLASS

#define SHADER_PROGRAM_CLASS

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
    public:
        ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
        GLuint getId();
        void Activate();
        void Delete();
        void setMat4(const std::string& name, glm::mat4 value);

    private:
        GLuint id;
        static std::string get_shader_content(const char* file);
};

#endif