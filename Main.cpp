#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ppm/PPMCapture.h"
#include "buffer/VBO/VBO.hpp"
#include "buffer/EBO/EBO.hpp"
#include "array/VAO.hpp"
#include "shader/ShaderProgram.hpp"
#include "camera/Camera.hpp"

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

GLfloat verts[] = {
    // Positions          // Colors (R, G, B)
    -1.0f, -1.0f, -1.0f,  0.2f, 0.3f, 0.8f,  // Vertex 0
     1.0f, -1.0f, -1.0f,  0.2f, 0.3f, 0.8f,  // Vertex 1
     1.0f,  1.0f, -1.0f,  0.9f, 0.2f, 0.5f,  // Vertex 2
    -1.0f,  1.0f, -1.0f,  0.9f, 0.2f, 0.5f,  // Vertex 3
    -1.0f, -1.0f,  1.0f,  0.6f, 0.1f, 0.9f,  // Vertex 4
     1.0f, -1.0f,  1.0f,  0.6f, 0.1f, 0.9f,  // Vertex 5
     1.0f,  1.0f,  1.0f,  0.3f, 0.6f, 0.7f,  // Vertex 6
    -1.0f,  1.0f,  1.0f,  0.3f, 0.6f, 0.7f   // Vertex 7
};

GLuint indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,

    // Front face
    4, 5, 6,
    6, 7, 4,

    // Left face
    4, 0, 3,
    3, 7, 4,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Bottom face
    4, 5, 1,
    1, 0, 4,

    // Top face
    3, 2, 6,
    6, 7, 3
}; 

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

	unsigned int width = 512;
	unsigned int height = 512;

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

	VBO vbo(verts, sizeof(verts));
	EBO ebo(indices, sizeof(indices));

	GLuint stride = 6 * sizeof(float);
	vao.LinkBuffers(0, stride, (void*) 0);
	vao.LinkBuffers(1, stride, (void*) (3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f)); 

	Camera camera(glm::vec3(0.0f, 0.0f, -3.0f), 45.0f, (float)width/(float)height, 0.1f, 100.0f);

	while(!glfwWindowShouldClose(window)) {
		handleInput(window);

		glClearColor(0.3, 0.4, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

        handleDebugShader(shaderProgram);
		shaderProgram.setMat4("model", model);
		camera.Apply(shaderProgram);

		vao.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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