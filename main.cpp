#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

#include "gl_framework.hpp"
#include "render_drawing.hpp"
#include "transformers.hpp"

int main (int argc, char *argv[])
{
	//! The pointer to the GLFW window
	GLFWwindow* window;
	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);
	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	int win_width=640;
	int win_height=640;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(win_width, win_height, "Transformers", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
    }

	//! Make the window's context current
	glfwMakeContextCurrent(window);

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwGetFramebufferSize(window, &win_width, &win_height);
	csX75::framebuffer_size_callback(window, win_width, win_height);
	//Initialize GL state
	csX75::initGL();

	glfwSetTime(0);

	while (glfwWindowShouldClose(window) == 0)
	{
		// Render here
		render_drawing(window);
		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
    }
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
