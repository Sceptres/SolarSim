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
#include "debug/DebugFilter.hpp"

// Define rotation constants
#define SUN_DAILY_REVOLVE_ANGLE 360.0f/27
#define EARTH_DAILY_REVOLVE_ANGLE 360.0f/1
#define EARTH_DAILY_ORBIT_SUN_ANGLE 360.f/365
#define MOON_DAILY_REVOLVE_ANGLE 360.0f/28
#define MOON_DAILY_ORBIT_EARTH_ANGLE 360.0f/28

DebugFilter debug;
PPMCapture capturer;

void closeWindow(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, true);
}

void captureIntoPPM(GLFWwindow* window) {
    std::cout << "Capture Window " << capturer.getId() << std::endl;
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    capturer.Dump("Assignment0-ss", buffer_width, buffer_height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLfloat get_sun_rotate_angle_around_itself(float day) {
	return day * SUN_DAILY_REVOLVE_ANGLE;
}
GLfloat get_earth_rotate_angle_around_sun(float day) {
	return day * EARTH_DAILY_ORBIT_SUN_ANGLE;
}
GLfloat get_earth_rotate_angle_around_itself(float day) {
	return day * EARTH_DAILY_REVOLVE_ANGLE;
}
GLfloat get_moon_rotate_angle_around_earth(float day) {
	return day * MOON_DAILY_ORBIT_EARTH_ANGLE;
}
GLfloat get_moon_rotate_angle_around_itself(float day) {
	return day * MOON_DAILY_REVOLVE_ANGLE;
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
    debug.ApplyToInputHandler(inputHandler);
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

	Camera camera(glm::vec3(60, 30, 80), 45.0f, 16.0/9.0, 0.1f, 1000.0f);
    camera.LookAt(sun.getPosition());

	float day = 8.7;

	while(!glfwWindowShouldClose(window)) {
		inputHandler.ProcessInput();

		glClearColor(0.3, 0.4, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
        debug.HandleDebugShader(shaderProgram);

        camera.Apply(shaderProgram);

        vao.Bind();

		sun.RevolveOnAxis(get_sun_rotate_angle_around_itself(day));
		sun.UpdateShader(shaderProgram);
        sun.Render();

		earth.RevolveOnAxis(get_earth_rotate_angle_around_itself(day));
        earth.UpdateShader(shaderProgram);
		earth.Render();

		moon.RevolveOnAxis(get_moon_rotate_angle_around_itself(day));
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