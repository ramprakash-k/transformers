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
float armor_angle=0.0f;
int head_pop=0.0f;
float head_angle=0.0f;
float head_angle1=0.0f;
float head_angle2=0.0f;
float right_arm_angle=0.0f;
float left_arm_angle=0.0f;
float right_arm_angle1=0.0f;
float left_arm_angle1=0.0f;
float right_arm_angle2=0.0f;
float left_arm_angle2=0.0f;
float right_forearm_angle=0.0f;
float left_forearm_angle=0.0f;
float left_thigh_angle=0.0f;
float right_thigh_angle=0.0f;
float left_thigh_angle1=0.0f;
float right_thigh_angle1=0.0f;
float left_thigh_angle2=0.0f;
float right_thigh_angle2=0.0f;
float right_leg_angle=0.0f;
float left_leg_angle=0.0f;
float right_foot_angle=90.0f;
float left_foot_angle=90.0f;
float right_wrist_angle=0.0f;
float left_wrist_angle=0.0f;
float right_wrist_angle1=0.0f;
float left_wrist_angle1=0.0f;
float right_wrist_angle2=0.0f;
float left_wrist_angle2=0.0f;
float right_d_leg_angle=0.0f;
float left_d_leg_angle=0.0f;
float lightturn=0.0f,lightturn1=0.0f;
float cam_x=0.0f,cam_z=-0.0f,cam_ay=0.0f;

GLuint armort[1];
GLuint headt[1];
GLuint dinot[1];
GLuint grasst[1];
GLuint skyt[1];

void lights(void)
{
  GLfloat position1[] =  {0.0, 0.0, 14, 1.0};
  GLfloat position2[] =  {0.0, 0.0, -14, 1.0};
  
  GLfloat temp[]={1.0,1.0,1.0,1.0};
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  glDepthFunc(GL_LESS);

  glLightfv(GL_LIGHT0, GL_POSITION, position1);
  glLightfv(GL_LIGHT1, GL_POSITION, position2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, temp);
  glLightfv(GL_LIGHT1, GL_SPECULAR, temp);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
  glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
  glEnable(GL_LIGHTING);
}

void DrawRobot(void)
{
	glPushMatrix();
		glRotatef(bust_angle_y,0,1,0);
		glRotatef(bust_angle_x,1,0,0);
		/*----------------TORSO, BACK, & ARMOR-----------------*/
		glCallList(torso);
		glPushMatrix();
			glTranslatef(0,-0.5,-0.6);
			glRotatef((180-((head_pop<0)?-head_pop:head_pop))*5/6,1,0,0);
			glCallList(d_joint);
			glPushMatrix();
				glRotatef((180-((head_pop<0)?-head_pop:head_pop))/2,0,0,1);
				glCallList(d_bar);
				glPushMatrix();
					glTranslatef(0,0.26,0.8);
					glRotatef((180-((head_pop<0)?-head_pop:head_pop))*7/18,-1,0,0);
					glCallList(d_head);
				glPopMatrix();
			glPopMatrix();
			glScalef(-1,1,1);
			glPushMatrix();
				glRotatef((180-((head_pop<0)?-head_pop:head_pop))/2,0,0,1);
				glCallList(d_bar);
				glPushMatrix();
					glTranslatef(0,0.26,0.8);
					glRotatef((180-((head_pop<0)?-head_pop:head_pop))*7/18,-1,0,0);
					glCallList(d_head);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-armor_angle,1,0,0);
			glTranslatef(0,0,0.2);
			glCallList(armor);
		glPopMatrix();
		/*-----------------------NECK & HEAD-------------------*/
		glPushMatrix();
			glRotatef(head_pop,0,0,1);
			glCallList(neck);
			glPushMatrix();
				glTranslatef(0,0.1,0);
				glRotatef(head_angle,1,0,0);
				glRotatef(head_angle1,0,1,0);
				glRotatef(head_angle2,0,0,1);
				glCallList(head);
				float fac=1.0;
				if(head_pop<-90)fac=0;
				else if(head_pop<=0)fac=(1.0*head_pop+90.0)/90.0;
				else if(head_pop<90)fac=(90.0-1.0*head_pop)/90.0;
				else fac=0.0;
				glScalef(1.0+fac/2,1.0+fac/2,1.0+fac/2);
				glTranslatef(0,fac*0.18,fac*0.07);
				glRotatef(fac*30,-1,0,0);
				glCallList(head_horn);
			glPopMatrix();
		glPopMatrix();
		/*-------------------RIGHT ARM, FOREARM & HAND----------*/
		glPushMatrix();
			glTranslatef(-1.4*5.0/6.0,0,0);
			glRotatef(right_arm_angle1,0,0,1);
			glRotatef(right_arm_angle,1,0,0);
			glRotatef(right_arm_angle2,0,1,0);
			glCallList(upper_arm);
			glPushMatrix();
				glTranslatef(0,-1.55,0);
				glRotatef(right_forearm_angle,1,0,0);
				glCallList(forearm);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glRotatef(right_wrist_angle,0,1,0);
					glRotatef(right_wrist_angle1,0,0,1);
					glRotatef(right_wrist_angle2,1,0,1);
					glCallList(hand);
					glPushMatrix();
						glRotatef(right_d_leg_angle,0,0,1);
						glTranslatef(-0.5,0,-0.17);
						glCallList(d_leg);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/*------------------LEFT ARM, FOREARM & HAND---------*/
		glPushMatrix();
			glTranslatef(1.4*5.0/6.0,0,0);
			glRotatef(left_arm_angle1,0,0,1);
			glScalef(-1,1,1);
			glRotatef(left_arm_angle,1,0,0);
			glRotatef(left_arm_angle2,0,1,0);
			glCallList(upper_arm);
			glPushMatrix();
				glTranslatef(0,-1.55,0);
				glRotatef(left_forearm_angle,1,0,0);
				glCallList(forearm);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glRotatef(left_wrist_angle,0,1,0);
					glRotatef(left_wrist_angle1,0,0,1);
					glRotatef(left_wrist_angle2,1,0,0);
					glCallList(hand);
					glPushMatrix();
						glRotatef(left_d_leg_angle,0,0,1);
						glTranslatef(-0.5,0,-0.17);
						glCallList(d_leg);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		/*--------------------RIGHT THIGH & LEG----------*/
		glPushMatrix();
			glTranslatef(-0.3,-1.6,0.1);
			glRotatef(right_thigh_angle1,0,0,1);
			glRotatef(right_thigh_angle,1.0,0.0,0.0);
			glRotatef(right_thigh_angle2,0,1,0);
			glCallList(thigh);
			glPushMatrix();
				glTranslatef(0,-1.7,0);
				glRotatef(right_leg_angle,1.0,0.0,0.0);
				glCallList(leg);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glRotatef(right_foot_angle,-1,0,0);
					glCallList(foot);
				glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		/*--------------------LEFT THIGH & LEG--------*/
		glPushMatrix();
			glTranslatef(0.3,-1.6,0.1);
			glRotatef(left_thigh_angle1,0,0,1);
			glScalef(-1,1,1);
			glRotatef(left_thigh_angle,1.0,0.0,0.0);
			glRotatef(left_thigh_angle2,0,1,0);
			glCallList(thigh);
			glPushMatrix();
				glTranslatef(0,-1.7,0);
				glRotatef(left_leg_angle,1.0,0.0,0.0);
				glCallList(leg);
				glPushMatrix();
					glTranslatef(0,-1.55,0);
					glRotatef(left_foot_angle,-1,0,0);
					glCallList(foot);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void render_drawing(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0,0,-10);
		glTranslatef(-cam_x,0,-cam_z);
		glRotatef(360-cam_ay,0,1,0);
		SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		glColor3ub(255,255,255);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,skyt[0]);
		glPushMatrix();
			glTranslatef(0,-5,0);
			drawCylinder(100,0,200,30,30,30,30,-1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,grasst[0]);
		glPushMatrix();
			glTranslatef(0,-5,0);
			glRotatef(180,1,0,0);
			GLUquadric* quad=gluNewQuadric();
			drawCylinder(100,0,0.1,30,30,30,30,1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			lights();
		glPopMatrix();
		glTranslatef(0,1,0);
		DrawRobot();
	glPopMatrix();
}

void transform_dino(GLFWwindow* window)
{
	bust_angle_y=0.0f;
	bust_angle_x=0.0f;
	armor_angle=0.0f;
	head_pop=0.0f;
	head_angle=0.0f;
	head_angle1=0.0f;
	head_angle2=0.0f;
	right_arm_angle=0.0f;
	left_arm_angle=0.0f;
	right_arm_angle1=0.0f;
	left_arm_angle1=0.0f;
	right_arm_angle2=0.0f;
	left_arm_angle2=0.0f;
	right_forearm_angle=0.0f;
	left_forearm_angle=0.0f;
	left_thigh_angle=0.0f;
	right_thigh_angle=0.0f;
	left_thigh_angle1=0.0f;
	right_thigh_angle1=0.0f;
	left_thigh_angle2=0.0f;
	right_thigh_angle2=0.0f;
	right_leg_angle=0.0f;
	left_leg_angle=0.0f;
	right_foot_angle=90.0f;
	left_foot_angle=90.0f;
	right_wrist_angle=0.0f;
	left_wrist_angle=0.0f;
	right_wrist_angle1=0.0f;
	left_wrist_angle1=0.0f;
	right_wrist_angle2=0.0f;
	left_wrist_angle2=0.0f;
	right_d_leg_angle=0.0f;
	left_d_leg_angle=0.0f;
	render_drawing(window);
	glfwSwapBuffers(window);
	bool flag=true;
	while(flag)
	{
		flag=false;
		if(bust_angle_x>45){bust_angle_x-=1;flag=true;}
		if(bust_angle_x<45){bust_angle_x+=1;flag=true;}
		if(bust_angle_y>135){bust_angle_y-=3;flag=true;}
		if(bust_angle_y<135){bust_angle_y+=3;flag=true;}
		if(armor_angle>135){armor_angle-=3;flag=true;}
		if(armor_angle<135){armor_angle+=3;flag=true;}
		if(head_pop>=0&&head_pop<180){head_pop+=3;flag=true;}
		if(head_pop<0&&head_pop>-180){head_pop-=3;flag=true;}
		if(right_arm_angle<300){right_arm_angle+=3;flag=true;}
		if(right_arm_angle>300){right_arm_angle-=3;flag=true;}
		if(right_forearm_angle<-15){right_forearm_angle+=3;flag=true;}
		if(right_forearm_angle>-15){right_forearm_angle-=3;flag=true;}
		if(left_arm_angle<300){left_arm_angle+=3;flag=true;}
		if(left_arm_angle>300){left_arm_angle-=3;flag=true;}
		if(left_forearm_angle<-15){left_forearm_angle+=3;flag=true;}
		if(left_forearm_angle>-15){left_forearm_angle-=3;flag=true;}
		if(left_thigh_angle>-159){left_thigh_angle-=3;flag=true;}
		if(right_thigh_angle>-159){right_thigh_angle-=3;flag=true;}
		if(left_leg_angle<-3){left_leg_angle+=3;flag=true;}
		if(left_leg_angle>-3){left_leg_angle-=3;flag=true;}
		if(right_leg_angle<-3){right_leg_angle+=3;flag=true;}
		if(right_leg_angle>-3){right_leg_angle-=3;flag=true;}
		if(right_wrist_angle<90){right_wrist_angle+=3;flag=true;}
		if(right_wrist_angle>90){right_wrist_angle-=3;flag=true;}
		if(left_wrist_angle<90){left_wrist_angle+=3;flag=true;}
		if(left_wrist_angle>90){left_wrist_angle-=3;flag=true;}
		if(right_d_leg_angle<222){right_d_leg_angle+=3;flag=true;}
		if(right_d_leg_angle>222){right_d_leg_angle-=3;flag=true;}
		if(left_d_leg_angle<222){left_d_leg_angle+=3;flag=true;}
		if(left_d_leg_angle>222){left_d_leg_angle-=3;flag=true;}
		if(right_foot_angle>0){right_foot_angle-=3;flag=true;}
		if(left_foot_angle>0){left_foot_angle-=3;flag=true;}
		render_drawing(window);
		glfwSwapBuffers(window);
	}
}

void transform_robot(GLFWwindow* window)
{
	bust_angle_y=0.0f;
	bust_angle_x=0.0f;
	armor_angle=0.0f;
	head_pop=0.0f;
	head_angle=0.0f;
	head_angle1=0.0f;
	head_angle2=0.0f;
	right_arm_angle=0.0f;
	left_arm_angle=0.0f;
	right_arm_angle1=0.0f;
	left_arm_angle1=0.0f;
	right_arm_angle2=0.0f;
	left_arm_angle2=0.0f;
	right_forearm_angle=0.0f;
	left_forearm_angle=0.0f;
	left_thigh_angle=0.0f;
	right_thigh_angle=0.0f;
	left_thigh_angle1=0.0f;
	right_thigh_angle1=0.0f;
	left_thigh_angle2=0.0f;
	right_thigh_angle2=0.0f;
	right_leg_angle=0.0f;
	left_leg_angle=0.0f;
	right_foot_angle=90.0f;
	left_foot_angle=90.0f;
	right_wrist_angle=0.0f;
	left_wrist_angle=0.0f;
	right_wrist_angle1=0.0f;
	left_wrist_angle1=0.0f;
	right_wrist_angle2=0.0f;
	left_wrist_angle2=0.0f;
	right_d_leg_angle=0.0f;
	left_d_leg_angle=0.0f;
	render_drawing(window);
	glfwSwapBuffers(window);
}
