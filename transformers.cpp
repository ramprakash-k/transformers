#include <cmath>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glew.h>

#include "transformers_defs.hpp"
#include "transformers.hpp"
#include "gl_framework.hpp"
#include "render_drawing.hpp"

void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void drawHemisphere(float radius, int longSlices, int latSlices,int p,int q,int in)
{
   int  i, j;
   float PI=3.14159265358979324;
   for(j = 0; j < q; j++)
   {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= p; i++)
      {
		 glTexCoord2f((float)i*1.0/p, (float)(j+1)*1.0/q);
		 glNormal3f( in * radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     in * radius * sin( (float)(j+1)/latSlices * PI/2.0 ),
					 in * radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
         glVertex3f( radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)(j+1)/latSlices * PI/2.0 ),
					 radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
		 glTexCoord2f((float)i*1.0/p, (float)j*1.0/q);
		 glNormal3f( in * radius * cos( (float)j/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     in * radius * sin( (float)j/latSlices * PI/2.0 ),
					 in * radius * cos( (float)j/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
         glVertex3f( radius * cos( (float)j/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)j/latSlices * PI/2.0 ),
					 radius * cos( (float)j/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
	  }
      glEnd();
   }
}

void drawCylinder(float br,float tr, float h,int lon,int lat,int p,int q)
{
	int i,j;
	float PI=3.14159265358979324;
   for(j = 0; j < q; j++)
   {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= p; i++)
      {
		 glTexCoord2f((float)i*1.0/p, (float)(j+1)*1.0/q);
		 glNormal3f( cos( 2.0 * ((float)i)/lon * PI ),
                     (tr-br)/h,
					 sin( 2.0 * ((float)i)/lon * PI ) );
         glVertex3f( (br + (j+1)*(tr-br)/lat) * cos( 2.0 * ((float)i)/lon * PI ),
                     (j+1)*h/lat,
					 (br + (j+1)*(tr-br)/lat) * sin( 2.0 * ((float)i)/lon * PI ) );
		 glTexCoord2f((float)i*1.0/p, (float)j*1.0/q);
		 glNormal3f( cos( 2.0 * ((float)i)/lon * PI ),
                     (tr-br)/h,
					 sin( 2.0 * ((float)i)/lon * PI ) );
         glVertex3f( (br + j*(tr-br)/lat) * cos( 2.0 * ((float)i)/lon * PI ),
                     j*h/lat,
					 (br + j*(tr-br)/lat) * sin( 2.0 * ((float)i)/lon * PI ) );
	  }
      glEnd();
   }
}

void drawCube(float side)
{
	float f=side/2;
	glBegin(GL_QUADS);
		glNormal3f(0,0,-1);glVertex3f(-f,-f ,-f);
		glNormal3f(0,0,-1);glVertex3f(f, -f, -f);
		glNormal3f(0,0,-1);glVertex3f(f, f, -f);
		glNormal3f(0,0,-1);glVertex3f(-f, f, -f);

		glNormal3f(-1,0,0);glVertex3f(-f, -f, -f);
		glNormal3f(-1,0,0);glVertex3f(-f, -f, f);
		glNormal3f(-1,0,0);glVertex3f(-f, f, f);
		glNormal3f(-1,0,0);glVertex3f(-f, f, -f);

		glNormal3f(0,-1,0);glVertex3f(-f, -f, -f);
		glNormal3f(0,-1,0);glVertex3f(-f, -f, f);
		glNormal3f(0,-1,0);glVertex3f(f, -f, f);
		glNormal3f(0,-1,0);glVertex3f(f, -f, -f);

		glNormal3f(0,0,1);glVertex3f(-f, -f, f);
		glNormal3f(0,0,1);glVertex3f(f, -f, f);
		glNormal3f(0,0,1);glVertex3f(f, f, f);
		glNormal3f(0,0,1);glVertex3f(-f, f, f);

		glNormal3f(1,0,0);glVertex3f(f,-f,-f);
		glNormal3f(1,0,0);glVertex3f(f,f,-f);
		glNormal3f(1,0,0);glVertex3f(f,f,f);
		glNormal3f(1,0,0);glVertex3f(f,-f,f);

		glNormal3f(0,1,0);glVertex3f(-f, f, -f);
		glNormal3f(0,1,0);glVertex3f(-f, f, f);
		glNormal3f(0,1,0);glVertex3f(f, f, f);
		glNormal3f(0,1,0);glVertex3f(f, f, -f);
	glEnd();
}

GLfloat mat_specularSILVER[] ={255.0*0.508273,255.0*0.508273,255.0*0.508273,1.0};
GLfloat mat_ambientSILVER[] ={255.0*0.19225,255.0*0.19225,255.0*0.19225,1.0};
GLfloat mat_diffuseSILVER[] ={255.0*0.50754,255.0*0.50754,255.0*0.50754,1.0};
GLfloat mat_shininessSILVER[] ={128.0 * 0.4};

GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={128.0 * 0.4};

GLfloat mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessGRAY[] ={128.0 * 0.6};

GLfloat mat_specularBLACK[] ={0.9,0.9,0.9,1.0};
GLfloat mat_ambientBLACK[] ={0.25,0.25,0.25,1.0};
GLfloat mat_diffuseBLACK[] ={0.25,0.25,0.25,1.0};
GLfloat mat_shininessBLACK[] ={128.0 * 0.6};

GLfloat mat_specularBLUE[] ={0.0225, 0.0225, 0.0225, 1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.0,0.0,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0};

GLfloat mat_specularGREEN[] ={0.633, 0.727811, 0.633,1.0};
GLfloat mat_ambientGREEN[] ={0.0215, 0.1745, 0.0215,1.0};
GLfloat mat_diffuseGREEN[] ={0.07568, 0.61424, 0.07568,1.0};
GLfloat mat_shininessGREEN[] ={128.0};

GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};

GLfloat mat_specularRED[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientRED[] ={1.0,0.0,0.0,1.0};
GLfloat mat_diffuseRED[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessRED[] ={128.0};

GLfloat mat_specularORANGE[] ={0.393548, 0.271906, 0.166721, 1.0};
GLfloat mat_ambientORANGE[] ={0.2125,0.1275,0.054,1.0};
GLfloat mat_diffuseORANGE[] ={0.714, 0.4284, 0.18144, 1.0};
GLfloat mat_shininessORANGE[] ={128.0*0.2};

void struct_torso(void)
{
	float PI=3.14159265358979324;
		// Armor
	glNewList(armor,GL_COMPILE);
	glPushMatrix();
		SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		glColor3ub(255,255,255);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,armort[0]);
		glRotatef(180,0,0,1);
		glScalef(1.6,1.7,0.75);
		drawHemisphere(0.6,20,10,10,8,1);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(64,64,64);
		glTranslatef(0,-0.9,0);
		glRotatef(180,0,0,1);
		glScalef(1.6,1.5,0.75);
		drawCylinder(0.1854,0.1854,0.35,10,5,5,5);
	glPopMatrix();
	glEndList();
		// Torso
	glNewList(torso,GL_COMPILE);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glRotatef(-90,1,0,0);
		GLUquadric* quad=gluNewQuadric();
		glScalef(1.5,0.75,1);
		gluDisk(quad,0.4,0.6,20,5);
	glPopMatrix();
	SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
	glColor3f(1,0.5,0);
	glPushMatrix();
		glRotatef(180,1,0,0);
		glScalef(1.5,1.2,0.75);
		drawHemisphere(0.6,20,5,20,5,1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.6,0);
		glRotatef(90,1,0,0);
		glScalef(1,0.6,1);
		gluCylinder(quad,0.2,0.2,1,10,5);
		glTranslatef(0,0,1);
		gluDisk(quad,0,0.2,10,5);
	glPopMatrix();
	glPushMatrix();
		glScalef(5.0/6.0,1,1);
		glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glVertex3f(0.2,-1.6,0);
			glVertex3f(1.08,0,0);
			glVertex3f(0.2,-.72,0);
			glVertex3f(0.2,-1.6,0);
			glNormal3f(0,0,1);
			glVertex3f(-1.08,0,0);
			glVertex3f(-0.2,-.72,0);
			glVertex3f(-0.2,-1.6,0);
			glVertex3f(-0.2,-1.6,0);
		glEnd();
		glScalef(1,1,0.36);
		glRotatef(180,1,0,0);
		drawCylinder(1.08,0.2,1.6,20,5,10,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.9,-0.13);
		glRotatef(-150,1,0,0);
		glRotatef(180,0,1,0);
		drawCylinder(0.3,0.3,0.8,20,5,10,5);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0.3,0,0);
			glVertex3f(0.3,0.45,0);
			glVertex3f(-0.3,0.45,0);
			glVertex3f(-0.3,0,0);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(64,64,64);
		glTranslatef(0,-0.5,-0.6);
		gluCylinder(quad,0.06,0.06,0.6,10,5);
	glPopMatrix();
	glPushMatrix();
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glTranslatef(0,-1.4,-0.6);
		glScalef(0.6,1.2,0.5);
		glRotatef(80,1,0,0);
		drawHemisphere(0.6,20,7,10,7,1);
		drawHemisphere(0.5,20,7,10,7,-1);
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,-1,0);
			for(float i=0.0f;i<=10.0f;i+=1.0f)
			{
				glVertex3f(0.5f*cos(PI*i/10.0f),0,0.5f*sin(PI*i/10.0f));
				glVertex3f(0.6f*cos(PI*i/10.0f),0,0.6f*sin(PI*i/10.0f));
			}
			glNormal3f(0,0,-1);
			for(float i=0.0f;i<=10.0f;i+=1.0f)
			{
				glVertex3f(0.5f*cos(PI*i/10.0f),0.5f*sin(PI*i/10.0f),0);
				glVertex3f(0.6f*cos(PI*i/10.0f),0.6f*sin(PI*i/10.0f),0);
			}
		glEnd();
		float h[20]={0.24,0.26,0.24,0.22,0.2,0.18,0.2,0.35,0.2,0.15,0.15,0.2,0.35,0.2,0.18,0.2,0.22,0.24,0.26,0.24};
		float s=(PI-19.0/7.0)/2.0;
		for(int i=0;i<20;i++,s+=1.0/7.0)
		{
			glPushMatrix();
				glTranslatef(0.55*cos(s),0,0.55*sin(s));
				glRotatef(100,1,0,0);
				gluCylinder(quad,0.05,0,h[i],10,2);
			glPopMatrix();
		}
	glPopMatrix();
	glEndList();
}

void struct_dino_head(void)
{
		// Dino Head
	float PI=3.14159265358979324;
	GLUquadric* quad=gluNewQuadric();
	glNewList(d_head,GL_COMPILE);
	glPushMatrix();
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3f(1.0,1.0,1.0);
		glRotatef(20,-1,0,0);
		glScalef(0.6,0.5,1.2);
		glRotatef(180,0,0,1);
		SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		glColor3ub(255,255,255);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,dinot[0]);
		drawHemisphere(0.6,20,7,5,7,1);
		glDisable(GL_TEXTURE_2D);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3f(1.0,1.0,1.0);
		drawHemisphere(0.5,20,7,5,7,-1);
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,-1,0);
			for(float i=0.0f;i<=5.0f;i+=1.0f)
			{
				glVertex3f(0.5f*cos(PI*i/10.0f),0,0.5f*sin(PI*i/10.0f));
				glVertex3f(0.6f*cos(PI*i/10.0f),0,0.6f*sin(PI*i/10.0f));
			}
			glNormal3f(0,0,-1);
			for(float i=0.0f;i<=5.0f;i+=1.0f)
			{
				glVertex3f(0,0.5f*sin(PI*i/10.0f),0.5f*cos(PI*i/10.0f));
				glVertex3f(0,0.6f*sin(PI*i/10.0f),0.6f*cos(PI*i/10.0f));
			}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,0,0);
			for(float i=0.0f;i<=5.0f;i+=1.0f)
				glVertex3f(0.6f*cos(PI*i/10.0f),0.6f*sin(PI*i/10.0f),0);
		glEnd();
		float h[10]={0.2,0.19,0.18,0.17,0.18,0.19,0.2,0.35,0.2,0.15};
		float s=(PI-19.0/7.0)/2.0;
		for(int i=0;i<10;i++,s+=1.0/7.0)
		{
			glPushMatrix();
				glTranslatef(0.55*cos(s),0,0.55*sin(s));
				glRotatef(90,1,0,0);
				gluCylinder(quad,0.05,0,h[i],10,2);
			glPopMatrix();
		}
		glTranslatef(0.2,0.47,0.2);
		glRotatef(90,-1,0,0);
		gluCylinder(quad,0.05,0,0.4,10,2);
	glPopMatrix();
	glEndList();

		// Head joining Bar
	glNewList(d_bar,GL_COMPILE);
	glPushMatrix();
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(64,64,64);
		glTranslatef(0,0.06,0.2);
		glScalef(0.2,0.2,0.6);
		glTranslatef(-0.5,0.5,0.5);
		drawCube(1);
	glPopMatrix();
	glEndList();

		// Head Joint
	glNewList(d_joint,GL_COMPILE);
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(64,64,64);
		glRotatef(120,1,0,0);
		gluCylinder(quad,0.06,0.06,0.8,10,5);
	glEndList();
}

void struct_neck(void)
{
		// Neck
	glNewList(neck,GL_COMPILE);
	SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
		glScalef(5.0/6.0,1,1);
		glRotatef(-90,1,0,0);
		GLUquadric* quad=gluNewQuadric();
		gluCylinder(quad,0.15,0.15,0.2,10,5);
		glScalef(1.8,0.75,1);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3f(1.0,1.0,1.0);
		gluDisk(quad,0,0.4,20,5);
		glTranslatef(0,0,-0.001);
		glRotatef(180,1,0,0);
		gluDisk(quad,0,0.4,20,5);
	glPopMatrix();
	glEndList();
}

void struct_head(void)
{
		// Head
	GLUquadric* quad=gluNewQuadric();
	glNewList(head,GL_COMPILE);
	glPushMatrix();
		glScalef(5.0/6.0,1,1);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(255,255,255);
		glScalef(1.5,1.5,1.5);
		glPushMatrix();
			SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
			glColor3ub(255,255,255);
			glEnable(GL_TEXTURE_2D);
			glRotatef(-90,0,1,0);
			glBindTexture(GL_TEXTURE_2D,headt[0]);
			drawCylinder(0.2,0.1,0.2,10,5,10,5);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
			SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
			glColor3f(1,0.5,0);
			glTranslatef(0,0.2,0);
			drawHemisphere(0.1,10,5,10,5,1);
		glPopMatrix();
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glColor3ub(0,0,255);
		glPushMatrix();
			glTranslatef(0.0,0.17,0.05);
			glScalef(0.18,0.1,0.1);
			drawCube(1);
		glPopMatrix();
	glPopMatrix();
	glEndList();
		// Horn
	glNewList(head_horn,GL_COMPILE);
	glPushMatrix();
		glScalef(5.0/6.0,1,1);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(255,255,255);
		glRotatef(-90,1,0,0);
		glScalef(0.2,0.8,2.3);
		gluCylinder(quad,0.1,0,0.2,3,5);
	glPopMatrix();
	glEndList();
}

void struct_upper_arm(void)
{
		// Upper Arm
	glNewList(upper_arm,GL_COMPILE);
	SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glRotatef(-20,0,0,1);
		GLUquadric* quad=gluNewQuadric();
		drawHemisphere(0.35,10,5,10,5,1);
		glRotatef(90,1,0,0);
		gluDisk(quad,0,0.35,10,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0.15,0);
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.3,0.28,0.75,30,5);
		glTranslatef(0,0,0.75);
		gluDisk(quad,0,0.28,30,5);
	glPopMatrix();
	SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
	glColor3ub(64,64,64);
	glPushMatrix();
		glTranslatef(0,-0.6,0);
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.25,0.22,0.75,30,5);
		glTranslatef(0,0,0.75);
		gluDisk(quad,0,0.22,30,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.05,-1.55,0);
		glRotatef(90,0,1,0);
		gluCylinder(quad,0.2,0.2,0.1,8,5);
	glPopMatrix();
	glEndList();
}

void struct_forearm(void)
{
		// Forearm
	glNewList(forearm,GL_COMPILE);
	SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		GLUquadric* quad=gluNewQuadric();
		glTranslatef(-0.15,0,0);
		glRotatef(90,0,1,0);
		gluCylinder(quad,0.2,0.2,0.1,8,5);
		glRotatef(180,0,1,0);
		gluDisk(quad,0,0.2,8,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.15,0,0);
		glRotatef(-90,0,1,0);
		gluCylinder(quad,0.2,0.2,0.1,8,5);
		glRotatef(180,0,1,0);
		gluDisk(quad,0,0.2,8,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.2,0);
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.2,0.17,1.2,10,5);
		glRotatef(180,1,0,0);
		gluDisk(quad,0,0.2,10,5);
		glTranslatef(0,0,-1.2);
		glRotatef(180,1,0,0);
		gluDisk(quad,0,0.17,10,5);
	glPopMatrix();
	glEndList();
}

void struct_thigh(void)
{
		// Thigh
	GLUquadric* quad=gluNewQuadric();
	glNewList(thigh,GL_COMPILE);
	SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
	glColor3ub(64,64,64);
	glPushMatrix();
		gluSphere(quad,0.2,20,20);
		SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
		glColor3f(1.0,0.5,0.0);
		glRotatef(-180,0,1,0);
		drawHemisphere(0.25,20,20,5,20,1);
		drawCylinder(0.25,0.25,-1,20,20,5,20);
		glPushMatrix();
			glTranslatef(0,0,0.25);
			glBegin(GL_QUADS);
				glNormal3f(1,0,3);
				glVertex3f(0,0,0);
				glVertex3f(-0.3,0,0.1);
				glVertex3f(-0.3,-1,0.1);
				glVertex3f(0,-1,0);
			glEnd();
		glPopMatrix();
		glTranslatef(0.25,0,0);
		glRotatef(-30,1,0,0);
		glRotatef(-30,0,0,1);
		gluSphere(quad,0.1,20,20);
		gluCylinder(quad,0.1,0.05,0.4,20,20);
		glTranslatef(0,0,0.4);
		gluSphere(quad,0.05,20,20);
		glPushMatrix();
			glRotatef(20,0,1,0);
			gluCylinder(quad,0.05,0,0.3,20,20);
		glPopMatrix();
		gluCylinder(quad,0.05,0,0.3,20,20);
		glPushMatrix();
			glRotatef(-20,0,1,0);
			gluCylinder(quad,0.05,0,0.3,20,20);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(64,64,64);
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.2,0.25,1.5,20,5);
		glTranslatef(0,0,1.5);
		gluDisk(quad,0,0.25,10,10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-1.7,0);
		glRotatef(90,0,1,0);
		glTranslatef(0,0,-0.075);
		gluCylinder(quad,0.2,0.2,0.15,20,5);
		glPushMatrix();
			glTranslatef(0,0,0.15);
			gluDisk(quad,0,0.2,10,10);
		glPopMatrix();
		glRotatef(180,0,1,0);
		gluDisk(quad,0,0.2,10,10);
	glPopMatrix();
	glEndList();
}

void struct_leg(void)
{
		// Leg
	GLUquadric* quad=gluNewQuadric();
	glNewList(leg,GL_COMPILE);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
	glColor3ub(255,255,255);
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(0,0,0.05);
		gluCylinder(quad,0.2,0.2,0.1,20,5);
		glPushMatrix();
			glTranslatef(0,0,0.1);
			gluDisk(quad,0,0.2,10,10);
		glPopMatrix();
		glRotatef(180,0,1,0);
		gluDisk(quad,0,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90,0,1,0);
		glTranslatef(0,0,0.05);
		gluCylinder(quad,0.2,0.2,0.1,20,5);
		glPushMatrix();
			glTranslatef(0,0,0.1);
			gluDisk(quad,0,0.2,10,10);
		glPopMatrix();
		glRotatef(180,0,1,0);
		gluDisk(quad,0,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
		drawCylinder(0.25,0.25,-1,30,30,30,30);
		drawCylinder(0.25,0.25,-1.3,30,30,15,30);
		glTranslatef(0,-1.3,0);
		drawCylinder(0.25,0.25,-0.2,20,20,2,25);
		glRotatef(216,0,1,0);
		drawCylinder(0.25,0.25,-0.2,20,20,2,25);
	glPopMatrix();
	glEndList();
}

void struct_foot(void)
{
		// Foot
	float PI=3.14159265358979324;
	GLUquadric* quad=gluNewQuadric();
	glNewList(foot,GL_COMPILE);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
	glColor3ub(64,64,64);
	glPushMatrix();
		glRotatef(90,1,0,0);
		drawHemisphere(0.25,20,20,20,20,1);
		glRotatef(90,1,0,0);
		gluDisk(quad,0,0.25,20,20);
	glPopMatrix();
	glPushMatrix();
		drawCylinder(0.2,0.15,0.4,20,20,10,20);
		glPushMatrix();
			glTranslatef(0,0.4,0);
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0,1,0);
				glVertex3f(0,0,0);
				for (int i = -90; i < 90; i=i+2)
				{
					glVertex3f(0.15 * sin(i*PI/180),0,0.15 * cos(i*PI/180));
				}
			glEnd();
		glPopMatrix();
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0.2,0,0);
			glVertex3f(0.15,0.4,0);
			glVertex3f(-0.15,0.4,0);
			glVertex3f(-0.2,0,0);
		glEnd();
		glScalef(1,-1,1);
		drawCylinder(0.2,0.15,0.4,20,20,10,20);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0.2,0,0);
			glVertex3f(0.15,0.4,0);
			glVertex3f(-0.15,0.4,0);
			glVertex3f(-0.2,0,0);
		glEnd();
		glPushMatrix();
			glTranslatef(0,0.4,0);
			drawCylinder(0.15,0,0.2,20,20,10,20);
			glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0,0,-1);
				glVertex3f(0.15,0,0);
				glVertex3f(0,0.2,0);
				glVertex3f(-0.15,0,0);
			glEnd();
			glTranslatef(0,0.1,0.05);
			glRotatef(70,1,0,0);
			drawCylinder(0.05,0,0.15,20,20,20,20);
		glPopMatrix();
	glPopMatrix();
	glEndList();
}

void struct_hand(void)
{
		// Hand
	glNewList(hand,GL_COMPILE);
	SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
	glColor3ub(64,64,64);
	glPushMatrix();
		glTranslatef(-0.08,0,0);
		glPushMatrix();
			glScalef(0.1,0.3,0.34);
			drawCube(1);
		glPopMatrix();
		glTranslatef(0.075,-0.1,0);
		glPushMatrix();
			glScalef(0.25,0.1,0.34);
			drawCube(1);
		glPopMatrix();
	glPopMatrix();
	glEndList();
}

void struct_dino_leg(void)
{
		// Dino Leg
	GLUquadric* quad=gluNewQuadric();
	glNewList(d_leg,GL_COMPILE);
	SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glTranslatef(-0.05,0,0);
		glScalef(1.5,1,1);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0,0,0);
			glVertex3f(0.1,0,0);
			glVertex3f(0.1,0.5,0);
			glVertex3f(0,0.5,0);
			glNormal3f(-1,0,0);
			glVertex3f(0,0,0);
			glVertex3f(0,0,0.34);
			glVertex3f(0,0.5,0.34);
			glVertex3f(0,0.5,0);
			glNormal3f(0,0,1);
			glVertex3f(0,0,0.34);
			glVertex3f(0.1,0,0.34);
			glVertex3f(0.1,0.5,0.34);
			glVertex3f(0,0.5,0.34);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.1,-0.2,0);
		glRotatef(30,0,0,1);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0.2,0,0);
			glVertex3f(0.4,0,0);
			glVertex3f(0.4,0.8,0);
			glVertex3f(0.2,0.8,0);
			glNormal3f(0,0,1);
			glVertex3f(0.2,0,0.34);
			glVertex3f(0.4,0,0.34);
			glVertex3f(0.4,0.8,0.34);
			glVertex3f(0.2,0.8,0.34);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0.5,0);
		gluCylinder(quad,0.2,0.2,0.34,6,6);
		glPushMatrix();
			glRotatef(180,0,1,0);
			gluDisk(quad,0,0.2,6,6);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,0.34);
			gluDisk(quad,0,0.2,6,6);
		glPopMatrix();
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glColor3ub(255,255,255);
		glTranslatef(-0.1,0.1,0);
		glRotatef(-45,0,0,1);
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0,0,0.24);
			glVertex3f(0,-0.1,0.24);
			glVertex3f(-0.4,-0.15,0.23);
			glVertex3f(-0.45,0,0.23);
			glNormal3f(0,0,1);
			glVertex3f(0,0,0.34);
			glVertex3f(0,-0.1,0.34);
			glVertex3f(-0.4,-0.15,0.39);
			glVertex3f(-0.45,0,0.39);
			glNormal3f(0,0,1);
			glVertex3f(-0.45,0,0.39);
			glVertex3f(-0.6,0.1,0.29);
			glVertex3f(-0.5,-0.1,0.29);
			glVertex3f(-0.4,-0.15,0.39);
			glNormal3f(0,0,-1);
			glVertex3f(-0.45,0,0.23);
			glVertex3f(-0.6,0.1,0.29);
			glVertex3f(-0.5,-0.1,0.29);
			glVertex3f(-0.4,-0.15,0.23);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,1,0);
			glVertex3f(0,0,0.24);
			glVertex3f(0,0,0.34);
			glVertex3f(-0.45,0,0.23);
			glVertex3f(-0.45,0,0.39);
			glVertex3f(-0.6,0.1,0.29);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,-1,0);
			glVertex3f(0,-0.1,0.24);
			glVertex3f(0,-0.1,0.34);
			glVertex3f(-0.4,-0.15,0.23);
			glVertex3f(-0.4,-0.15,0.39);
			glVertex3f(-0.5,-0.1,0.29);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0,0,0.11);
			glVertex3f(0,-0.1,0.11);
			glVertex3f(-0.4,-0.15,0.11);
			glVertex3f(-0.5,0,0.11);
			glNormal3f(0,0,1);
			glVertex3f(0,0,0.23);
			glVertex3f(0,-0.1,0.23);
			glVertex3f(-0.4,-0.15,0.23);
			glVertex3f(-0.5,0,0.23);
			glNormal3f(0,0,1);
			glVertex3f(-0.5,0,0.23);
			glVertex3f(-0.65,0.1,0.17);
			glVertex3f(-0.5,-0.1,0.17);
			glVertex3f(-0.4,-0.15,0.23);
			glNormal3f(0,0,-1);
			glVertex3f(-0.5,0,0.11);
			glVertex3f(-0.65,0.1,0.17);
			glVertex3f(-0.5,-0.1,0.17);
			glVertex3f(-0.4,-0.15,0.11);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,1,0);
			glVertex3f(0,0,0.11);
			glVertex3f(0,0,0.23);
			glVertex3f(-0.5,0,0.11);
			glVertex3f(-0.5,0,0.23);
			glVertex3f(-0.65,0.1,0.17);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,-1,0);
			glVertex3f(0,-0.1,0.11);
			glVertex3f(0,-0.1,0.23);
			glVertex3f(-0.4,-0.15,0.11);
			glVertex3f(-0.4,-0.15,0.23);
			glVertex3f(-0.5,-0.1,0.17);
		glEnd();
		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glVertex3f(0,0,0.0);
			glVertex3f(0,-0.1,0.0);
			glVertex3f(-0.4,-0.15,-0.04);
			glVertex3f(-0.45,0,-0.04);
			glNormal3f(0,0,1);
			glVertex3f(0,0,0.10);
			glVertex3f(0,-0.1,0.10);
			glVertex3f(-0.4,-0.15,0.11);
			glVertex3f(-0.45,0,0.11);
			glNormal3f(0,0,1);
			glVertex3f(-0.45,0,0.11);
			glVertex3f(-0.6,0.1,0.05);
			glVertex3f(-0.5,-0.1,0.05);
			glVertex3f(-0.4,-0.15,0.11);
			glNormal3f(0,0,-1);
			glVertex3f(-0.45,0,-0.04);
			glVertex3f(-0.6,0.1,0.05);
			glVertex3f(-0.5,-0.1,0.05);
			glVertex3f(-0.4,-0.15,-0.04);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,1,0);
			glVertex3f(0,0,0.0);
			glVertex3f(0,0,0.10);
			glVertex3f(-0.45,0,-0.04);
			glVertex3f(-0.45,0,0.11);
			glVertex3f(-0.6,0.1,0.05);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0,-1,0);
			glVertex3f(0,-0.1,0.0);
			glVertex3f(0,-0.1,0.10);
			glVertex3f(-0.4,-0.15,-0.04);
			glVertex3f(-0.4,-0.15,0.11);
			glVertex3f(-0.5,-0.1,0.05);
		glEnd();
	glPopMatrix();
	glEndList();
}

void init_structures(void)
{
	struct_torso();
	struct_head();
	struct_neck();
	struct_thigh();
	struct_upper_arm();
	struct_forearm();
	struct_leg();
	struct_hand();
	struct_dino_leg();
	struct_dino_head();
	struct_foot();
}
