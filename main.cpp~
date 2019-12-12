#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

//#include "glad/glad.h"
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void handle_input(GLFWwindow* window);

//GLuint load_shader(std::string shader_filename, GLenum shader_type);

//GLuint make_shader_program(GLuint vertex_shader, GLuint fragment_shader);



void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handle_input(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
/*
GLuint load_shader(std::string shader_filename, GLenum shader_type) {
	std::ifstream in(shader_filename);
	std::string shader_text(
		(std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>()
	);
	const char* shader_chars = shader_text.c_str();
	std::cout << "Shader File \"" + shader_filename + "\" Loaded. \n Contents: \n" + shader_chars << std::endl;

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cerr << "Shader did not compile. Error log:" << std::endl;
		std::cerr << buffer << std::endl;
	}

	return shader;
}

GLuint make_shader_program(GLuint vertex_shader, GLuint fragment_shader) {
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	GLint status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetProgramInfoLog(shader_program, 512, NULL, buffer);
		std::cerr << "Shaders could not link. Error log:" << std::endl;
		std::cerr << buffer << std::endl;
	}

	return shader_program;
};*/

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

	// GLAD
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "GLAD initialization failed. " << std::endl;
		return -1;
	}*/

	// define size of viewport
	glViewport(0, 0, 640, 480);

	// VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);

	/*// Load shaders
	GLuint vertex_shader = load_shader("shader.vert", GL_VERTEX_SHADER);
	GLuint fragment_shader = load_shader("shader.frag", GL_FRAGMENT_SHADER);

	// Make shader program
	GLuint shader_program = make_shader_program(vertex_shader, fragment_shader);
	//GLint uniform_color = glGetUniformLocation(shader_program, "ourColor");
	//glUseProgram(shader_program); // AV

	// Delete shaders (they're no longer needed)
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);*/

	Shader main_shader = Shader("shader.vert", "shader.frag");

	// Creating a VAO to store our state
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // this is the buffer we are gonna write to
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
