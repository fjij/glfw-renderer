#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <cmath>

#include "shader.hpp"

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	 -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          Function Declarations                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void handle_input(GLFWwindow* window);

int main();

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          Function Definitions                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handle_input(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Make window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World!", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Window creation failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);



	// define size of viewport
	glViewport(0, 0, 640, 480);

	// VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);

	// Load shaders
	shader::Shader main_shader = shader::Shader("shader.vert", "shader.frag");

	// Creating a VAO to store our state
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// this is the buffer we are gonna write to
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO (you need to bind vbo and ebo together)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Linking vertex attributes
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // 6 stride (color in between)
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
	(void*)(3*sizeof(float))); // 3 float offset
	glEnableVertexAttribArray(1);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while(!glfwWindowShouldClose(window)) {
		// input
		handle_input(window);

		float time_sin = std::sin(glfwGetTime());

		// render
		glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		main_shader.use();
		main_shader.set_float("timeSin", time_sin);
		//glUniform4f(uniform_color, 0.0f, green, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		// rest
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
