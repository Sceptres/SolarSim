#include "InputHandler.hpp"

InputHandler::InputHandler(GLFWwindow* window) {
    this->window = window;
}

void InputHandler::AddKeyCallback(int key, void (*func)(GLFWwindow*)) {
    this->keyFuncMap[key] = func;
    this->keyPressedMap[key] = false;
}

void InputHandler::ProcessInput() {
    for(auto const& [key, func] : this->keyFuncMap) {
        if(glfwGetKey(this->window, key) == GLFW_PRESS) {
            if(!this->keyPressedMap[key]) {
                func(this->window);
                this->keyPressedMap[key] = true;
            }
        } else {
            this->keyPressedMap[key] = false;
        }
    }
}