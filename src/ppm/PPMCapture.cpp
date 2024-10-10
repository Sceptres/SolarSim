#include "PPMCapture.hpp"

PPMCapture::PPMCapture() {
    this->idCounter = 0;
}

void PPMCapture::Dump(std::string prefix, unsigned int width, unsigned int height) {
    int pixelChannel = 3;
    int totalPixelSize = pixelChannel * width * height * sizeof(GLubyte);
    GLubyte * pixels = new GLubyte [totalPixelSize];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    std::string file_name = prefix + std::to_string(this->idCounter) + ".ppm";
    std::ofstream fout(file_name);
    fout << "P3\n" << width << " " << height << "\n" << 255 << std::endl;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            size_t cur = pixelChannel * ((height - i - 1) * width + j);
            fout << (int)pixels[cur] << " " << (int)pixels[cur + 1] << " " << (int)pixels[cur + 2] << " ";
        }
        fout << std::endl;
    }
    this->idCounter++;
    delete [] pixels;
    fout.flush();
    fout.close();
}

unsigned int PPMCapture::getId() {
    return this->idCounter;
}

void PPMCapture::ApplyToInputHandler(InputHandler& inputHandler) {
    inputHandler.AddKeyCallback(GLFW_KEY_P, [this](GLFWwindow* window) {
        this->Capture(window);
    });
}

void PPMCapture::Capture(GLFWwindow* window) {
    std::cout << "Capture Window " << this->idCounter << std::endl;
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    this->Dump("Assignment0-ss", buffer_width, buffer_height);
}