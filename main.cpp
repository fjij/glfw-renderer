#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.5f,  0.5f,  1.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f,  0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f,  0.0f, 1.0f, 0.0f }
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void debug_text(std::string message) {
	std::cout << message << '\n';
}
void debug_error(std::string message) {
	std::cerr << message << '\n';
}

GLuint load_shader(std::string shader_filename, GLenum shader_type) {
	std::ifstream in(shader_filename);
	std::string shader_text(
		(std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>()
	);
	const char* shader_chars = shader_text.c_str();
	debug_text("Shader File \"" + shader_filename + "\" Loaded. \n Contents: \n" + shader_chars);

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		debug_error("Shader did not compile. Error log:");
		std::cerr << buffer << std::endl;
	}

	return shader;
}

int main(void)
{
	/*std::ifstream in_vert("shader.vert");
	std::string vertex_shader_string((std::istreambuf_iterator<char>(in_vert)),
	    std::istreambuf_iterator<char>());
	std::ifstream in_frag("shader.frag");
	std::string fragment_shader_string((std::istreambuf_iterator<char>(in_frag)),
	    std::istreambuf_iterator<char>());
	const char* vertex_shader_text1 = vertex_shader_string.c_str();
	const char* fragment_shader_text1 = fragment_shader_string.c_str();

	std::cout << fragment_shader_string.c_str() << '\n';*/

    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    //gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
    // NOTE: OpenGL error checks have been omitted for brevity
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = load_shader("shader.vert", GL_VERTEX_SHADER);
    fragment_shader = load_shader("shader.frag", GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        mat4x4_identity(m); // [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
