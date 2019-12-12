#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef __APPLE__
#	define __gl_h_
#	define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <iostream>
#include <fstream>
#include <cmath>

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "lib_ext/glfw3.h"
#include "lib_ext/stb_image.h"

#include "shader.hpp"

float vertices[] = {
//	positions					colors						textures
	 -0.5f,	-0.5f,	0.0f,		1.0f,	0.0f,	0.0f,		//1.0f, 1.0f,
	 0.5f,	-0.5f,	0.0f,		0.0f,	1.0f,	0.0f,		//1.0f, 0.0f,
	 0.5f, 	0.5f,	0.0f,		0.0f,	0.0f,	1.0f,		//0.0f, 0.0f,
	 -0.5f,	0.5f,	0.0f,		1.0f,	1.0f,	1.0f//,		0.0f, 1.0f
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



		// Load shaders
		shader::Shader main_shader = shader::Shader("shader.vert", "shader.frag");

	// -----------------------------------------------------------
	// VBO
	GLuint VBO;
	glGenBuffers(1, &VBO); // Generates 1 VBO and stores it's ID at (&VBO)[0]

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// this is the buffer we are gonna write to
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// -----------------------------------------------------------
	// EBO -- for indexed drawing.
	GLuint EBO;
	glGenBuffers(1, &EBO);

	// Bind EBO (you need to bind vbo and ebo together)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//  Textures -----------------------------------------------------------
	/*
	// <<< Texture Wrap >>>
	// S, T = x, y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// <<< Texture Filtering >>>
	// minify/magnify, nearest (pixelate) and linear (blur)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// <<< Texture Filtering With Mipmaps >>>
	// GL_X_MIPMAP_Y where X is the type of interpolation to use on the mipmap
	// selected using method Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// * Note -- this overwrites the first call in the previous section

	// <<< Load image data using STBI >>>
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	// <<< Create and bind texture object >>>
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (data) {

		// <<< Use image data to generate texture and mipmap >>
		// args:
		//	target -- GL_TEXTURE_2D -- target the currently bound GL_TEXTURE_2D (not 1D or 3D, 2D.)
		//	mipmap level -- 0 -- automatic (we dont want to mipmap manually)
		//	format to store image as -- GL_RGB
		//	width and height
		//	always put 0 here?
		//	data format, data type -- we used rgb and bytes (chars)
		//	actual image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	} else {
		std::cerr << "error: failed to load texture :((((";
	}
	// <<< Free image >>>
	stbi_image_free(data);
	*/
	// VAO -----------------------------------------------------------
	// Creating a VAO to store our state
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Linking vertex attributes

	GLint size;
	GLsizei stride = sizeof(float)*6;

	// << position >>
	size = 3;
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, stride, (GLvoid *)(sizeof(float)*0));
	glEnableVertexAttribArray(0);

	// << color >>
	size = 3;
	glVertexAttribPointer(1, size, GL_FLOAT, GL_FALSE, stride, (GLvoid *)(sizeof(float)*3));
	glEnableVertexAttribArray(1);

	// << texture >>
	/*size = 2;
	glVertexAttribPointer(2, size, GL_FLOAT, GL_FALSE, stride, (GLvoid *)(sizeof(float)*6));
	glEnableVertexAttribArray(2);*/



	// Main loop -----------------------------------------------------------

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

		//glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		// rest
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
