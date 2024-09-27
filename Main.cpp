#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include "ppm/PPMCapture.h"
#include "shader/ShaderProgram.h"
#include "buffer/VBO.h"
#include "array/VAO.h"

PPMCapture capturer;


//key board control
void processInput(GLFWwindow *window) {
    //press escape to exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //press p to capture screen
    if(glfwGetKey(window, GLFW_KEY_P) ==GLFW_PRESS) {
        std::cout << "Capture Window " << capturer.getId() << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        capturer.Dump("Assignment0-ss", buffer_width, buffer_height);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.9f, 0.8f, 0.7f, 1.0f);\n" //triangle color green
    "}\n\0";


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    int windowWidth = 512;
    int windowHeight = 512;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Assignment0", NULL, NULL);

    if (window == NULL) {
        std::cout << "GLFW Window Failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Initialization Failed" << std::endl;
        return -1;
    }
    
    //shaders
    ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);

    
    //triangle vertex positions
    GLfloat tri_verts[] = {
        -1.0f/2, -1.0f/2, 0.0f,  // bottom-left
        1.0f/2, -1.0f/2, 0.0f,  // bottom-right
        -1.0f/2,  1.0f/2, 0.0f,  // top-left

        -1.0f/2,  1.0f/2, 0.0f,  // top-left
        1.0f/2, -1.0f/2, 0.0f,  // bottom-right
        1.0f/2, 1.0f/2, 0.0f,  // top-right
    }; 

    VAO vao;

    VBO vbo(tri_verts, sizeof(tri_verts));

    vao.Bind();
    vao.LinkVBO(vbo);

    vbo.Unbind();
    vao.Unbind();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //background color
        glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw things
        shaderProgram.Activate();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //release resource
    vao.Delete();
    vbo.Delete();
    shaderProgram.Delete();
    glfwTerminate();
    return 0;
}
