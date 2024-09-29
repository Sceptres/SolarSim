#include "DebugFilter.hpp"

DebugFilter::DebugFilter() {
    this->isInDebugMode = false;
}

bool DebugFilter::IsInDebugMode() {
    return this->isInDebugMode;
}

void DebugFilter::ApplyToInputHandler(InputHandler& inputHandler) {
    inputHandler.AddKeyCallback(GLFW_KEY_B, [this](GLFWwindow* window) {
        this->ToggleDebugMode(window);
    });
}

void DebugFilter::HandleDebugShader(ShaderProgram& shaderProgram) {
    shaderProgram.setBool("isDebug", isInDebugMode);
}

void DebugFilter::ToggleDebugMode(GLFWwindow* window) {
    if (this->isInDebugMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isInDebugMode = false;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        this->isInDebugMode = true;
    }
}