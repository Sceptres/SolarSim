#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, bool isResizable, std::string title) {
    this->width = width;
    this->height = height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, isResizable ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    this->window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
    if(this->window == nullptr) {
        throw WindowNotCreatedException();
    }
}

Window::~Window() {
    if(this->window != nullptr)
        glfwDestroyWindow(this->window);
}

GLFWwindow* Window::getGLWindow() {
    return this->window;
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(this->window);
}

void Window::Launch() {
    glfwMakeContextCurrent(this->window);
    glfwSetWindowUserPointer(this->window, this);
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw GladInitFailedException();
	} 
    
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
    glViewport(0, 0, this->width, this->height);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

void Window::ApplyCloseWindowToInputHandler(InputHandler& inputHandler) {
    inputHandler.AddKeyCallback(GLFW_KEY_ESCAPE, [this](GLFWwindow*) {
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    });
}

void Window::framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);

    if(window) {
        window->width = width;
        window->height = height;
        glViewport(0, 0, window->width, window->height);
    }
}