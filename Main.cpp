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
#include "input/InputHandler.hpp"

static bool isInDebugMode = false;
bool bKeyPressed = false; // To track the state of the "B" key
PPMCapture capturer;

void closeWindow(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, true);
}

void toggleDebugMode(GLFWwindow* window) {
    if (isInDebugMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isInDebugMode = false;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        isInDebugMode = true;
    }
}

void captureIntoPPM(GLFWwindow* window) {
    std::cout << "Capture Window " << capturer.getId() << std::endl;
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    capturer.Dump("Assignment0-ss", buffer_width, buffer_height);
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
	glfwWindowHint(GLFW_SAMPLES, 4);
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
	glEnable(GL_MULTISAMPLE);

    InputHandler inputHandler(window);
    inputHandler.AddKeyCallback(GLFW_KEY_ESCAPE, closeWindow);
    inputHandler.AddKeyCallback(GLFW_KEY_B, toggleDebugMode);
    inputHandler.AddKeyCallback(GLFW_KEY_P, captureIntoPPM);

	ShaderProgram shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO vao;
	vao.Bind();

	VBO vbo = Cube::InstantiateVBO();
	EBO ebo = Cube::InstantiateEBO();

    Cube::LinkAttribs(vao);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

    Cube sun(
        glm::vec3(0, 0, 0),
        20,
        0,
        glm::vec3(0, 0, 0)
    );
	glm::vec3 sunPos = sun.getPosition();

    Cube earth(
        glm::vec3(sunPos.x + 40, sunPos.y, sunPos.z),
        8,
        -23.4,
        glm::vec3(0, 0, 1)
    );
	glm::vec3 earthPos = earth.getPosition();

	Cube moon(
		glm::vec3(earthPos.x + 12, earthPos.y, earthPos.z),
		4,
		0,
		glm::vec3(0, 0, 0)
	);

	Camera camera(glm::vec3(0, 0, 120), 45.0f, 16.0/9.0, 0.1f, 1000.0f);
    camera.LookAt(sun.getPosition());

	while(!glfwWindowShouldClose(window)) {
		inputHandler.ProcessInput();

		glClearColor(0.3, 0.4, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
        handleDebugShader(shaderProgram);

        camera.Apply(shaderProgram);

        vao.Bind();

		sun.UpdateShader(shaderProgram);
        sun.Render();
        earth.UpdateShader(shaderProgram);
		earth.Render();
		moon.UpdateShader(shaderProgram);
		moon.Render();

        vao.Unbind();

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