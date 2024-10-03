#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ppm/PPMCapture.hpp"
#include "buffer/VBO/VBO.hpp"
#include "buffer/EBO/EBO.hpp"
#include "array/VAO.hpp"
#include "shader/ShaderProgram.hpp"
#include "camera/Camera.hpp"
#include "entity/cube/Cube.hpp"
#include "input/InputHandler.hpp"
#include "debug/DebugFilter.hpp"
#include "window/Window.hpp"
#include "color/Color.hpp"

// Define rotation constants
#define SUN_DAILY_REVOLVE_ANGLE 360.0f/27.0f
#define EARTH_DAILY_REVOLVE_ANGLE 360.0f/1.0f
#define EARTH_DAILY_ORBIT_SUN_ANGLE 360.0f/365.0f
#define MOON_DAILY_REVOLVE_ANGLE 360.0f/28.0f
#define MOON_DAILY_ORBIT_EARTH_ANGLE 360.0f/28.0f

#define SUN_EARTH_DISTANCE 40
#define EARTH_MOON_DISTANCE 12

DebugFilter debug;
PPMCapture capturer;

GLfloat get_sun_rotate_angle_around_itself(float day) {
	return day * SUN_DAILY_REVOLVE_ANGLE;
}
GLfloat get_earth_rotate_angle_around_sun(float day) {
	return -day * EARTH_DAILY_ORBIT_SUN_ANGLE;
}
GLfloat get_earth_rotate_angle_around_itself(float day) {
	return day * EARTH_DAILY_REVOLVE_ANGLE;
}
GLfloat get_moon_rotate_angle_around_earth(float day) {
	return -day * MOON_DAILY_ORBIT_EARTH_ANGLE;
}
GLfloat get_moon_rotate_angle_around_itself(float day) {
	return day * MOON_DAILY_REVOLVE_ANGLE;
}

glm::vec3 get_earth_pos_today(Cube sun, float day) {
	glm::vec3 sunPos = sun.getPosition();
	GLfloat earthSunAngle = glm::radians(get_earth_rotate_angle_around_sun(day));

	GLfloat x = (glm::cos(earthSunAngle) * SUN_EARTH_DISTANCE) + sunPos.x;
	GLfloat z = (glm::sin(earthSunAngle) * SUN_EARTH_DISTANCE) + sunPos.z;
	return glm::vec3(x, sunPos.y, z);
}

glm::vec3 get_moon_pos_today(Cube earth, float day) {
	glm::vec3 earthPos = earth.getPosition();
	GLfloat moonEarthAngle = glm::radians(get_moon_rotate_angle_around_earth(day));

	GLfloat x = (glm::cos(moonEarthAngle) * EARTH_MOON_DISTANCE) + earthPos.x;
	GLfloat z = (glm::sin(moonEarthAngle) * EARTH_MOON_DISTANCE) + earthPos.z;
	return glm::vec3(x, earthPos.y, z);
}

int main() {
	try {
		glfwInit();

		Window window(1024, 576, false, "Solar Simulation");
		window.Launch();

		InputHandler inputHandler(window.getGLWindow());
		window.ApplyCloseWindowToInputHandler(inputHandler);
		debug.ApplyToInputHandler(inputHandler);
		capturer.ApplyToInputHandler(inputHandler);

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
			glm::vec3(sunPos.x + SUN_EARTH_DISTANCE, sunPos.y, sunPos.z),
			8,
			-23.4,
			glm::vec3(0, 0, 1)
		);
		glm::vec3 earthPos = earth.getPosition();

		Cube moon(
			glm::vec3(earthPos.x + EARTH_MOON_DISTANCE, earthPos.y, earthPos.z),
			4,
			0,
			glm::vec3(0, 0, 0)
		);

		Camera camera(glm::vec3(30, 20, 90), 45.0f, 16.0/9.0, 0.1f, 1000.0f);

		Color backgroundColor(0.3, 0.4, 0.5, 1.0f);

		float day = 0, inc = 1.0f/24;

		while(!window.ShouldClose()) {
			inputHandler.ProcessInput();

			window.ClearColor(backgroundColor);

			shaderProgram.Activate();
			debug.HandleDebugShader(shaderProgram);

			camera.LookAt(sun.getPosition());
			camera.Apply(shaderProgram);

			std::cout << "Today is: " << day << std::endl;

			vao.Bind();

			sun.RevolveOnAxis(get_sun_rotate_angle_around_itself(day));
			sun.Render(shaderProgram);

			earth.MoveTo(get_earth_pos_today(sun, day));
			earth.RevolveOnAxis(get_earth_rotate_angle_around_itself(day));
			earth.Render(shaderProgram);

			moon.MoveTo(get_moon_pos_today(earth, day));
			moon.RevolveOnAxis(get_moon_rotate_angle_around_itself(day));
			moon.Render(shaderProgram);

			vao.Unbind();

			day += inc;

			window.SwapBuffers();

			glfwPollEvents();
		}

		vao.Delete();
		vbo.Delete();
		ebo.Delete();
		shaderProgram.Delete();
		glfwTerminate();

		return 0;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}
}