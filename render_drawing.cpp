#include <math.h>
#include <GL/glew.h>
#include <unistd.h>
#include "gl_framework.hpp"
#include "render_drawing.hpp"
#include "transformers.hpp"
#include "transformers_defs.hpp"
#include "image.hpp"

float bust_angle_y=0.0f;
float bust_angle_x=0.0f;
float right_arm_angle=0.0f;
float left_arm_angle=0.0f;
float right_forearm_angle=0.0f;
float left_forearm_angle=0.0f;
float left_thigh_angle=0.0f;
float right_thigh_angle=0.0f;
float right_leg_angle=0.0f;
float left_leg_angle=0.0f;
float right_d_leg_angle=0.0f;
float left_d_leg_angle=0.0f;
float lightturn=0.0f,lightturn1=0.0f;
float cam_x=0.0f,cam_z=-0.0f,cam_ay=0.0f;

GLuint armort[1];

void lights(void)
{
  GLfloat position[] =  {0.0, 0.0, 3.0, 1.0};
  glRotatef(lightturn1, 1.0, 0.0, 0.0);
  glRotatef(lightturn, 0.0, 1.0, 0.0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glDepthFunc(GL_LESS);

  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);

  glTranslatef(0.0, 0.0, 3.0);
  glDisable(GL_LIGHTING);
  glColor3f(1,1,0);
  GLUquadric* quad=gluNewQuadric();
  gluQuadricDrawStyle(quad,GLU_LINE);
  gluSphere(quad,0.05,4,2);
  glEnable(GL_LIGHTING);
}

void DrawRobot(void)
{
	glPushMatrix();
		glRotatef(bust_angle_y,0,1,0);
		glRotatef(bust_angle_x,1,0,0);
		/*----------------TORSO, NECK & HEAD-------------*/
		glCallList(torso);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,armort[0]);
			//~ glRotatef(180,1,0,0);
			glTranslatef(0,0,0.2);
			glCallList(armor);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
			glCallList(neck);
			glPushMatrix();
				glTranslatef(0,0.1,0);
				glCallList(head);
			glPopMatrix();
		glPopMatrix();
		/*-------------------RIGHT ARM, FOREARM & HAND----------*/
		glPushMatrix();
			glTranslatef(-1.4,0,0);
			glRotatef(right_arm_angle,1,0,0);
			glCallList(upper_arm);
			glPushMatrix();
				glTranslatef(0,-1.55,0);
				glRotatef(right_forearm_angle,1,0,0);
				glCallList(forearm);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glCallList(hand);
					glPushMatrix();
						glTranslatef(-0.5,0,-0.17);
						glRotatef(right_d_leg_angle,0,0,1);
						glCallList(d_leg);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/*------------------LEFT ARM, FOREARM & HAND---------*/
		glPushMatrix();
			glTranslatef(1.4,0,0);
			glScalef(-1,1,1);
			glRotatef(left_arm_angle,1,0,0);
			glCallList(upper_arm);
			glPushMatrix();
				glTranslatef(0,-1.55,0);
				glRotatef(left_forearm_angle,1,0,0);
				glCallList(forearm);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glCallList(hand);
					glPushMatrix();
						glTranslatef(-0.5,0,-0.17);
						glRotatef(left_d_leg_angle,0,0,1);
						glCallList(d_leg);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/*--------------------RIGHT THIGH & LEG----------*/
		glPushMatrix();
			glTranslatef(-0.25,-1.6,0.0);
			glRotatef(right_thigh_angle,1.0,0.0,0.0);
			glCallList(thigh);
			glPushMatrix();
				glTranslatef(-0.3,-2.3,0.0);
				glRotatef(right_leg_angle,1.0,0.0,0.0);
				glTranslatef(0.3,2.3,0.0);
				//~ glCallList(leg);
			glPopMatrix();
		glPopMatrix();
		/*--------------------LEFT THIGH & LEG--------*/
		glPushMatrix();
			glTranslatef(0.25,-1.6,0.0);
			glRotatef(left_thigh_angle,1.0,0.0,0.0);
			glCallList(thigh);
			glPushMatrix();
				glTranslatef(0.3,-2.3,0.0);
				glRotatef(left_leg_angle,1.0,0.0,0.0);
				glTranslatef(-0.3,2.3,0.0);
				//~ glCallList(leg);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void render_drawing(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glRotatef(360-cam_ay,0,1,0);
		glTranslatef(-cam_x,0,-cam_z);
		glPushMatrix();
			lights();
		glPopMatrix();
		DrawRobot();
	glPopMatrix();
}
