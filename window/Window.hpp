#ifndef WINDOW_CLASS

#define WINDOW_CLASS

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "exception/WindoNotCreatedException.hpp"
#include "exception/GladInitFailedException.hpp"
#include "../input/InputHandler.hpp"

class Window {
    public:
        Window(unsigned int width, unsigned int height, bool isResizable, std::string title);
        ~Window();
        GLFWwindow* getGLWindow();
        bool ShouldClose();
        void Launch();
        void ApplyCloseWindowToInputHandler(InputHandler& inputHandler); 
        void SwapBuffers();

    private:
        GLFWwindow* window;
        unsigned int width;
        unsigned int height;
        static void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
};

#endif