#include <math.h>
#include "gl_framework.hpp"
#include "render_drawing.hpp"
#include "transformers.hpp"

namespace csX75
{
int win_width;
int win_height;

//! Initialize GL State
void initGL(void)
{
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT,GL_FILL);
	//~ glEnable(GL_CULL_FACE);
	//~ glCullFace(GL_BACK);
	init_structures();
}

//!GLFW Error Callback
void error_callback(int error, const char* description)
{
    std::cerr<<description<<std::endl;
}

//!GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if  ( height == 0 ) height = 1;
	glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,50.0f);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,1,-10);
    win_width = width;
    win_height = height;
}

#define angle_step 3.0f

//!GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//!Close the window if the ESC key was pressed
	float piover180 = 3.14159265358979324/180;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (action ==  GLFW_PRESS || action == GLFW_REPEAT)
    {
		if (key == GLFW_KEY_LEFT)
			bust_angle_y-=angle_step;
		if (key == GLFW_KEY_RIGHT)
			bust_angle_y+=angle_step;
		if (key == GLFW_KEY_UP)
			bust_angle_x-=angle_step;
		if (key == GLFW_KEY_DOWN)
			bust_angle_x+=angle_step;
		if (key == GLFW_KEY_1)
			right_arm_angle-=angle_step;
		if (key == GLFW_KEY_Q)
			right_arm_angle+=angle_step;
		if (key == GLFW_KEY_2)
		{
			right_forearm_angle-=angle_step;
			if (right_forearm_angle<-100.0f) right_forearm_angle=-100.0f;
		}
		if (key == GLFW_KEY_W)
		{
			right_forearm_angle+=angle_step;
			if (right_forearm_angle>100.0f) right_forearm_angle=100.0f;
		}
		if (key == GLFW_KEY_3)
			left_arm_angle+=angle_step;
		if (key == GLFW_KEY_E)
			left_arm_angle-=angle_step;
		if (key == GLFW_KEY_4)
		{
			left_forearm_angle+=angle_step;
			if (left_forearm_angle>100.0f) left_forearm_angle=100.0f;
		}
		if (key == GLFW_KEY_R)
		{
			left_forearm_angle-=angle_step;
			if (left_forearm_angle<-100.0f) left_forearm_angle=-100.0f;
		}
		if (key == GLFW_KEY_5)
		{
			left_thigh_angle-=angle_step;
			if (left_thigh_angle<-150.0f) left_thigh_angle=-150.0f;
		}
		if (key == GLFW_KEY_T)
		{
			left_thigh_angle+=angle_step;
			if (left_thigh_angle>150.0f) left_thigh_angle=150.0f;
		}
		if (key == GLFW_KEY_6)
		{
			left_leg_angle+=angle_step;
			if (left_leg_angle>100.0f) left_leg_angle=100.0f;
		}
		if (key == GLFW_KEY_Y)
		{
			left_leg_angle-=angle_step;
			if (left_leg_angle<-100.0f) left_leg_angle=-100.0f;
		}
		if (key == GLFW_KEY_7)
		{
			right_thigh_angle-=angle_step;
			if (right_thigh_angle<-150.0f) right_thigh_angle=-150.0f;
		}
		if (key == GLFW_KEY_U)
		{
			right_thigh_angle+=angle_step;
			if (right_thigh_angle>150.0f) right_thigh_angle=150.0f;
		}
		if (key == GLFW_KEY_8)
		{
			right_leg_angle+=angle_step;
			if (right_leg_angle>100.0f) right_leg_angle=100.0f;
		}
		if (key == GLFW_KEY_I)
		{
			right_leg_angle-=angle_step;
			if (right_leg_angle<-100.0f) right_leg_angle=-100.0f;
		}
		if (key == GLFW_KEY_Z)
			lightturn+=5 % 360;
		if (key == GLFW_KEY_X)
			lightturn1+=5 % 360;
		if (key == GLFW_KEY_N)
		{
			cam_x-=(float)sin(cam_ay*piover180) * 0.15f;
			cam_z-=(float)cos(cam_ay*piover180) * 0.15f;
		}
		if (key == GLFW_KEY_M)
		{
			cam_x+=(float)sin(cam_ay*piover180) * 0.15f;
			cam_z+=(float)cos(cam_ay*piover180) * 0.15f;
		}
		if (key == GLFW_KEY_V)
			cam_ay-=1.0f;
		if (key == GLFW_KEY_B)
			cam_ay+=1.0f;
	}
}
};



