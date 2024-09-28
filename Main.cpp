#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ppm/PPMCapture.h"
#include "buffer/VBO/VBO.hpp"
#include "buffer/EBO/EBO.hpp"
#include "array/VAO.hpp"
#include "shader/ShaderProgram.hpp"
#include "camera/Camera.hpp"
#include "entity/cube/Cube.hpp"

static bool isInDebugMode = false;
bool bKeyPressed = false; // To track the state of the "B" key
PPMCapture capturer;

void handleInput(GLFWwindow* window) {
    // Handle ESC key to close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Handle "B" key toggle
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (!bKeyPressed) {
            if (isInDebugMode) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                isInDebugMode = false;
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                isInDebugMode = true;
            }
            bKeyPressed = true;
        }
    } else {
        bKeyPressed = false; // Reset the state when the key is released
    }

    if(glfwGetKey(window, GLFW_KEY_P) ==GLFW_PRESS) {
        std::cout << "Capture Window " << capturer.getId() << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        capturer.Dump("Assignment0-ss", buffer_width, buffer_height);
    }
}

void handleDebugShader(ShaderProgram& shaderProgram) {
    shaderProgram.setBool("isDebug", isInDebugMode);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

	unsigned int width = 1024;
	unsigned int height = 576;

	GLFWwindow* window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if(window == nullptr) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	} 

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);

	ShaderProgram shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO vao;
	vao.Bind();

	VBO vbo = Cube::InstantiateVBO();
	EBO ebo = Cube::InstantiateEBO();

    Cube::LinkAttribs(vao);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

    Cube cube(glm::vec3(0, 0, 0));

	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 45.0f, (float)width/(float)height, 0.1f, 100.0f);

	while(!glfwWindowShouldClose(window)) {
		handleInput(window);

		glClearColor(0.3, 0.4, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

        handleDebugShader(shaderProgram);
		cube.UpdateShader(shaderProgram);
		camera.Apply(shaderProgram);

		vao.Bind();
		cube.Render();
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();
	glfwTerminate();

	return 0;
}