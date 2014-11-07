#ifndef GL_FRAMEWORK_HPP
#define GL_FRAMEWORK_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace csX75
{
	extern int state;
	//1 -> robot
	//3 -> dino

	//! Initialize GL State
	void initGL(void);

	//!GLFW Error Callback
	void error_callback(int error, const char* description);
	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // GL_FRAMEWORK_HPP
