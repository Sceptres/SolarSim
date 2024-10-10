#ifndef PPM_CAPTURE_CLASS
#define PPM_CAPTURE_CLASS

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include "../input/InputHandler.hpp"

class PPMCapture {
    public:
        PPMCapture();
        void Dump(std::string prefix, unsigned int width, unsigned int height);
        unsigned int getId();
        void ApplyToInputHandler(InputHandler& inputHandler);

    private:
        unsigned int idCounter;
        void Capture(GLFWwindow* window);
};

#endif