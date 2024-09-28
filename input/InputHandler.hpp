#ifndef INPUT_HANDLER_CLASS

#define INPUT_HANDLER_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

class InputHandler {
    public:
        InputHandler(GLFWwindow* window);
        void AddKeyCallback(int key, void (*func)(GLFWwindow*));
        void ProcessInput();

    private:
        GLFWwindow* window;
        std::map<int, void (*)(GLFWwindow*)> keyFuncMap;
        std::map<int, bool> keyPressedMap;
};

#endif