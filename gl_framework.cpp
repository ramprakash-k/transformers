#include <math.h>
#include <unistd.h>
#include "gl_framework.hpp"
#include "keyframe.hpp"
#include "render_drawing.hpp"
#include "transformers.hpp"
#include "image.hpp"
#define angle_step 3.0f

namespace csX75
{

	int state=1;
	int win_width;
	int win_height;
	int leg_dir=1;

//! Initialize GL State
void initGL(void)
{
	LoadGLTextures("armor.bmp",armort);
	LoadGLTextures("head.bmp",headt);
	LoadGLTextures("dino.bmp",dinot);
	LoadGLTextures("grass.bmp",grasst);
	LoadGLTextures("sky.bmp",skyt);
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT,GL_FILL);
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
    gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    win_width = width;
    win_height = height;
}

//!GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// if(action ==  GLFW_PRESS || action == GLFW_REPEAT) {
	// 	std::cout<<key<<" "<<(mods & GLFW_MOD_CONTROL)<<" "<<(GLFW_MOD_CONTROL)<<" "<<((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)<<std::endl;
	// }
//!Close the window if the ESC key was pressed
	float piover180 = 3.14159265358979324/180.0;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if ((action ==  GLFW_PRESS || action == GLFW_REPEAT) && (state == 1 || state == 3))
    {
    	// Lights
    	if (key == GLFW_KEY_F1)
		{
			headlight=!headlight;
		}
    	if (key == GLFW_KEY_F2)
		{
			light0=!light0;
		}
		if (key == GLFW_KEY_F3)
		{
			light1=!light1;
		}
		if (key == GLFW_KEY_F4)
		{
			light2=!light2;
		}

		// Right Arm
		if (key == GLFW_KEY_1 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			if(right_arm_angle==0.0f)right_arm_angle=360.0f;
			right_arm_angle-=angle_step;
		}
		else if (key == GLFW_KEY_1 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_arm_angle+=angle_step;
			if(right_arm_angle==360.0f)right_arm_angle=0.0f;
		}

		if (key == GLFW_KEY_Q && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_arm_angle2-=angle_step;
			if(right_arm_angle2<0.0f)right_arm_angle2=0.0f;
		}
		else if (key == GLFW_KEY_Q && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_arm_angle2+=angle_step;
			if(right_arm_angle2>180.0f)right_arm_angle2=180.0f;
		}

		// Right forearm
		if (key == GLFW_KEY_2 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_forearm_angle-=angle_step;
			if (right_forearm_angle<-99.0f) right_forearm_angle=-99.0f;
		}
		if (key == GLFW_KEY_2 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_forearm_angle+=angle_step;
			if (right_forearm_angle>99.0f) right_forearm_angle=99.0f;
		}

		// Left Arm
		if (key == GLFW_KEY_3 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			if(left_arm_angle==0.0f)left_arm_angle=360.0f;
			left_arm_angle-=angle_step;
		}
		else if (key == GLFW_KEY_3 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_arm_angle+=angle_step;
			if(left_arm_angle==360.0f)left_arm_angle=0.0f;
		}

		if (key == GLFW_KEY_E && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_arm_angle2-=angle_step;
			if(left_arm_angle2<0.0f)left_arm_angle2=0.0f;
		}
		else if (key == GLFW_KEY_E && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_arm_angle2+=angle_step;
			if(left_arm_angle2>180.0f)left_arm_angle2=180.0f;
		}

		// Left forearm
		if (key == GLFW_KEY_4 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_forearm_angle-=angle_step;
			if (left_forearm_angle<-99.0f) left_forearm_angle=-99.0f;
		}
		if (key == GLFW_KEY_4 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_forearm_angle+=angle_step;
			if (left_forearm_angle>99.0f) left_forearm_angle=99.0f;
		}

		if (key == GLFW_KEY_H)
		{
			head_pop+=angle_step;
			if(head_pop>180)head_pop=-180;
		}
		if (key == GLFW_KEY_D)
		{
			armor_angle+=angle_step;
			if(armor_angle>180.0f)armor_angle=180.0f;
		}
		if (key == GLFW_KEY_F)
		{
			armor_angle-=angle_step;
			if(armor_angle<0.0f)armor_angle=0.0f;
		}

		// Left thigh
		if (key == GLFW_KEY_7 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_thigh_angle-=angle_step;
			if (left_thigh_angle<-159.0f) left_thigh_angle=-159.0f;
		}
		if (key == GLFW_KEY_7 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_thigh_angle+=angle_step;
			if (left_thigh_angle>150.0f) left_thigh_angle=150.0f;
		}

		// Left leg
		if (key == GLFW_KEY_8 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_leg_angle+=angle_step;
			if (left_leg_angle>99.0f) left_leg_angle=99.0f;
		}
		if (key == GLFW_KEY_8 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_leg_angle-=angle_step;
			if (left_leg_angle<-99.0f) left_leg_angle=-99.0f;
		}

		// Right thigh
		if (key == GLFW_KEY_5 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_thigh_angle-=angle_step;
			if (right_thigh_angle<-159.0f) right_thigh_angle=-159.0f;
		}
		if (key == GLFW_KEY_5 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_thigh_angle+=angle_step;
			if (right_thigh_angle>150.0f) right_thigh_angle=150.0f;
		}

		// Left leg
		if (key == GLFW_KEY_6 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_leg_angle+=angle_step;
			if (right_leg_angle>99.0f) right_leg_angle=99.0f;
		}
		if (key == GLFW_KEY_6 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_leg_angle-=angle_step;
			if (right_leg_angle<-99.0f) right_leg_angle=-99.0f;
		}

		// Right foot
		if (key == GLFW_KEY_9 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_foot_angle+=angle_step;
			if(right_foot_angle>99.0f)right_foot_angle=99.0f;
		}
		if (key == GLFW_KEY_9 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_foot_angle-=angle_step;
			if(right_foot_angle<0.0f)right_foot_angle=0.0f;
		}

		// Left foot
		if (key == GLFW_KEY_0 && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_foot_angle+=angle_step;
			if(left_foot_angle>99.0f)left_foot_angle=99.0f;
		}
		if (key == GLFW_KEY_0 && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_foot_angle-=angle_step;
			if(left_foot_angle<0.0f)left_foot_angle=0.0f;
		}

		// Right wrist
		if (key == GLFW_KEY_W && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			if(right_wrist_angle==0.0f)right_wrist_angle=360.0f;
			right_wrist_angle-=angle_step;
		}
		if (key == GLFW_KEY_W && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_wrist_angle+=angle_step;
			if(right_wrist_angle==360.0f)right_wrist_angle=0.0f;
		}

		// Left wrist
		if (key == GLFW_KEY_R && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			if(left_wrist_angle==0.0f)left_wrist_angle=360.0f;
			left_wrist_angle-=angle_step;
		}
		if (key == GLFW_KEY_R && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_wrist_angle+=angle_step;
			if(left_wrist_angle==360.0f)left_wrist_angle=0.0f;
		}

		// Right dino leg
		if (key == GLFW_KEY_A && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			right_d_leg_angle+=angle_step;
			if(right_d_leg_angle>240.0f)right_d_leg_angle=240.0f;
		}
		if (key == GLFW_KEY_A && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			right_d_leg_angle-=angle_step;
			if(right_d_leg_angle<0.0f)right_d_leg_angle=0.0f;
		}

		// Left dino leg
		if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL) != GLFW_MOD_CONTROL)
		{
			left_d_leg_angle+=angle_step;
			if(left_d_leg_angle>240.0f)left_d_leg_angle=240.0f;
		}
		if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			left_d_leg_angle-=angle_step;
			if(left_d_leg_angle<0.0f)left_d_leg_angle=0.0f;
		}

		if (key == GLFW_KEY_SPACE)
		{
			if(state==1)
			{
				transform_dino(window);
				state=3;
			}
			else
			{
				transform_robot(window);
				state=1;
			}
		}
	}
	if (action ==  GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
		{
			if(dir==360.0f)dir=0.0f;
			dir+=2*angle_step;

			if(state == 3)
			{
				if(right_arm_angle>285)
				{
					right_arm_angle -= 3;
					left_arm_angle += 3;
				}
			}

			if(state == 1)
			{
				if(right_thigh_angle>-15)
				{
					right_arm_angle += 3;
					left_arm_angle -= 3;
					right_thigh_angle -= 3;
					left_thigh_angle += 3;
				}
			}
		}
		if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
		{
			dir-=2*angle_step;
			if(dir==-6.0f)dir=354.0f;

			if(state == 3)
			{
				if(right_arm_angle<315)
				{
					right_arm_angle += 3;
					left_arm_angle -= 3;
				}
			}

			if(state == 1)
			{
				if(right_thigh_angle<15)
				{
					right_arm_angle -= 3;
					left_arm_angle += 3;
					right_thigh_angle += 3;
					left_thigh_angle -= 3;
				}
			}
		}
		if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
		{
			pos_x+=cos(dir*piover180)/2;
			pos_z-=sin(dir*piover180)/2;

			if(state == 3) {
				right_arm_angle += 3*leg_dir;
				left_arm_angle -= 3*leg_dir;

				if(right_arm_angle>315) { leg_dir=-1; }
				if(left_arm_angle>315) { leg_dir=1; }
			}

			if(state == 1) {
				right_arm_angle -= 3*leg_dir;
				left_arm_angle += 3*leg_dir;

				right_thigh_angle += 3*leg_dir;
				left_thigh_angle -= 3*leg_dir;

				if(right_thigh_angle>15) { leg_dir=-1; }
				if(left_thigh_angle>15) { leg_dir=1; }
			}

			if(pos_x*pos_x+pos_z*pos_z>8100)
			{
				pos_x-=2*cos(dir*piover180);
				pos_z+=2*sin(dir*piover180);
			}
		}
		if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
		{
			pos_x-=cos(dir*piover180)/2;
			pos_z+=sin(dir*piover180)/2;

			if(state == 3) {
				right_arm_angle -= 3*leg_dir;
				left_arm_angle += 3*leg_dir;

				if(right_arm_angle>315) { leg_dir=1; }
				if(left_arm_angle>315) { leg_dir=-1; }
			}

			if(state == 1) {
				right_arm_angle += 3*leg_dir;
				left_arm_angle -= 3*leg_dir;

				right_thigh_angle -= 3*leg_dir;
				left_thigh_angle += 3*leg_dir;

				if(right_thigh_angle>15) { leg_dir=1; }
				if(left_thigh_angle>15) { leg_dir=-1; }
			}

			if(pos_x*pos_x+pos_z*pos_z>8100)
			{
				pos_x+=2*cos(dir*piover180);
				pos_z-=2*sin(dir*piover180);
			}
		}
		if (key == GLFW_KEY_V)
			camera=(camera+1)%3;
		if (key == GLFW_KEY_B && camera==1)
		{
			cam_ay+=3;
			if(cam_ay>360)cam_ay=0;
		}
		if (key == GLFW_KEY_N && camera==1)
		{
			cam_z+=3;
			if(cam_z>90)cam_z=90;
		}
		if (key == GLFW_KEY_M && camera==1)
		{
			cam_z-=3;
			if(cam_z<-90)cam_z=-90;
		}
	}
}
};
