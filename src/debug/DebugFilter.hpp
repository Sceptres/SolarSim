#ifndef DEBUG_FILTER_CLASS

#define DEBUG_FILTER_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../input/InputHandler.hpp"
#include "../shader/ShaderProgram.hpp"

class DebugFilter {
    public:
        DebugFilter();
        bool IsInDebugMode();
        void ApplyToInputHandler(InputHandler& inputHandler);
        void HandleDebugShader(ShaderProgram& shaderProgram);

    private:
        bool isInDebugMode;
        void ToggleDebugMode(GLFWwindow* window);
};

#endif