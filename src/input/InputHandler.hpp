#ifndef INPUT_HANDLER_CLASS

#define INPUT_HANDLER_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <functional>

class InputHandler {
    public:
        InputHandler(GLFWwindow* window);
        void AddKeyCallback(int key, std::function<void(GLFWwindow*)> func);
        void ProcessInput();

    private:
        GLFWwindow* window;
        std::map<int, std::function<void(GLFWwindow*)>> keyFuncMap;
        std::map<int, bool> keyPressedMap;
};

#endif