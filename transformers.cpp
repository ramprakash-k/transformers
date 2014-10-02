#include <cmath>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glew.h>

#include "transformers_defs.hpp"
#include "transformers.hpp"
#include "gl_framework.hpp"

void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void drawHemisphere(float radius, int longSlices, int latSlices,int p,int q)
{
   int  i, j;
   float PI=3.14159265358979324;
   for(j = 0; j < q; j++)
   {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= p; i++)
      {
		 glTexCoord2f((float)i/p, (float)(j+1)/q);
		 glNormal3f( radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)(j+1)/latSlices * PI/2.0 ),
					 radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
         glVertex3f( radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)(j+1)/latSlices * PI/2.0 ),
					 radius * cos( (float)(j+1)/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
		 glTexCoord2f((float)i/p, (float)j/q);
		 glNormal3f( radius * cos( (float)j/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)j/latSlices * PI/2.0 ),
					 radius * cos( (float)j/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
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
		 glNormal3f( (br + (j+1)*(tr-br)/lat) * cos( 2.0 * ((float)i+0.5)/lon * PI ),
                     (j+1)*h/lat,
					 (br + (j+1)*(tr-br)/lat) * sin( 2.0 * ((float)i+0.5)/lon * PI ) );
         glVertex3f( (br + (j+1)*(tr-br)/lat) * cos( 2.0 * ((float)i+0.5)/lon * PI ),
                     (j+1)*h/lat,
					 (br + (j+1)*(tr-br)/lat) * sin( 2.0 * ((float)i+0.5)/lon * PI ) );
		 glNormal3f( (br + j*(tr-br)/lat) * cos( 2.0 * ((float)i+0.5)/lon * PI ),
                     j*h/lat,
					 (br + j*(tr-br)/lat) * sin( 2.0 * ((float)i+0.5)/lon * PI ) );
         glVertex3f( (br + j*(tr-br)/lat) * cos( 2.0 * ((float)i+0.5)/lon * PI ),
                     j*h/lat,
					 (br + j*(tr-br)/lat) * sin( 2.0 * ((float)i+0.5)/lon * PI ) );
	  }
      glEnd();
   }
}

void drawCube(float side)
{
	float f=side/2;
	glBegin(GL_QUADS);
		glNormal3f(0,0,-1);
		glVertex3f(-f,-f ,-f);glNormal3f(0,0,-1);
		glVertex3f(f, -f, -f);glNormal3f(0,0,-1);
		glVertex3f(f, f, -f);glNormal3f(0,0,-1);
		glVertex3f(-f, f, -f);
		glNormal3f(-1,0,0);
		glVertex3f(-f, -f, -f);glNormal3f(-1,0,0);
		glVertex3f(-f, -f, f);glNormal3f(-1,0,0);
		glVertex3f(-f, f, f);glNormal3f(-1,0,0);
		glVertex3f(-f, f, -f);
		glNormal3f(0,-1,0);
		glVertex3f(-f, -f, -f);glNormal3f(0,-1,0);
		glVertex3f(-f, -f, f);glNormal3f(0,-1,0);
		glVertex3f(f, -f, f);glNormal3f(0,-1,0);
		glVertex3f(f, -f, -f);
    glNormal3f(0,0,1);
		glVertex3f(-f, -f, f);glNormal3f(0,0,1);
		glVertex3f(f, -f, f);glNormal3f(0,0,1);
		glVertex3f(f, f, f);glNormal3f(0,0,1);
		glVertex3f(-f, f, f);
    glNormal3f(1,0,0);
		glVertex3f(f,-f,-f);glNormal3f(1,0,0);
		glVertex3f(f,f,-f);glNormal3f(1,0,0);
		glVertex3f(f,f,f);glNormal3f(1,0,0);
		glVertex3f(f,-f,f);
		glNormal3f(0,1,0);
		glVertex3f(-f, f, -f);glNormal3f(0,1,0);
		glVertex3f(-f, f, f);glNormal3f(0,1,0);
		glVertex3f(f, f, f);glNormal3f(0,1,0);
		glVertex3f(f, f, -f);
	glEnd();
}

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

GLfloat mat_specularORANGE[] ={0.0225, 0.0225, 0.0225, 1.0};
GLfloat mat_ambientORANGE[] ={1.0,0.5,0.0,1.0};
GLfloat mat_diffuseORANGE[] ={0.992157, 0.513726, 0.0, 1.0};
GLfloat mat_shininessORANGE[] ={128.0};

void struct_torso(void)
{
		// Torso
	glNewList(torso,GL_COMPILE);
	SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glRotatef(-90,1,0,0);
		glScalef(1.8,0.75,1);
		GLUquadric* quad=gluNewQuadric();
		gluDisk(quad,0,0.6,20,5);
	glPopMatrix();
	glPushMatrix();
		glRotatef(180,1,0,0);
		glScalef(1.8,1.2,0.75);
		drawHemisphere(0.6,20,5,20,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.6,0);
		glRotatef(90,1,0,0);
		glScalef(1,0.6,1);
		gluCylinder(quad,0.4,0.2,1,10,5);
		glTranslatef(0,0,1);
		gluDisk(quad,0,0.2,10,5);
	glPopMatrix();
	glEndList();
		// Armor
	glNewList(armor,GL_COMPILE);
	glPushMatrix();
		glRotatef(180,0,0,1);
		glScalef(1.9,1.2,0.75);
		drawHemisphere(0.6,20,8,10,5);
	glPopMatrix();
	glEndList();
}

void struct_neck(void)
{
	glNewList(neck,GL_COMPILE);
	SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
		glRotatef(-90,1,0,0);
		GLUquadric* quad=gluNewQuadric();
		gluCylinder(quad,0.15,0.15,0.2,10,5);
	glPopMatrix();
	glEndList();
}

void struct_head(void)
{
	glNewList(head,GL_COMPILE);
	glPushMatrix();
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(255,255,255);
		glScalef(1.5,1.5,1.5);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			GLUquadric* quad=gluNewQuadric();
			gluCylinder(quad,0.2,0.1,0.2,10,5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.18,0.07);
			glRotatef(-120,1,0,0);
			glScalef(0.2,0.8,2.3);
			gluCylinder(quad,0.1,0,0.2,3,5);
		glPopMatrix();
		glPushMatrix();
				SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
				glColor3f(1,0.5,0);
				glTranslatef(0,0.2,0);
				drawHemisphere(0.1,10,5,10,5);
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
}

void struct_upper_arm(void)
{
	glNewList(upper_arm,GL_COMPILE);
	SetMaterial(mat_specularORANGE, mat_ambientORANGE, mat_diffuseORANGE, mat_shininessORANGE);
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glRotatef(-20,0,0,1);
		GLUquadric* quad=gluNewQuadric();
		drawHemisphere(0.35,10,5,10,5);
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
	glColor3ub(255,255,255);
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
	glNewList(thigh,GL_COMPILE);
	SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
	glColor3ub(64,64,64);
	glPushMatrix();
		glTranslatef(-0.05,0,0);
		glRotatef(90,0,1,0);
		GLUquadric* quad=gluNewQuadric();
		gluCylinder(quad,0.2,0.2,0.1,10,5);
		glPushMatrix();
			glTranslatef(0,0,0.1);
			gluDisk(quad,0,0.2,10,5);
		glPopMatrix();
		glRotatef(180,1,0,0);
		gluDisk(quad,0,0.2,10,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.2,0);
		glRotatef(90,1,0,0);
		gluCylinder(quad,0.2,0.22,0.8,10,5);
		glRotatef(180,1,0,0);
		gluDisk(quad,0,0.2,10,5);
		glRotatef(180,1,0,0);
		glTranslatef(0,0,0.8);
		gluCylinder(quad,0.22,0.22,0.58,10,5);
		glTranslatef(0,0,0.58);
		glRotatef(90,1,0,0);
		drawHemisphere(0.22,10,5,10,5);
	glPopMatrix();
	glEndList();
}

void struct_leg(void)
{
	GLUquadric* quad=gluNewQuadric();
	glNewList(leg,GL_COMPILE);
		glTranslatef(-0.3,-2.3,0.0);
		glScalef(2.0,1.3,2.0);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(128,128,128);
		gluSphere(quad,0.1,20,20);
		glTranslatef(0.0,-0.5,0.0);
		glScalef(0.5,2.0,0.5);
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glColor3ub(0,0,255);
		drawCube(0.5);
	glEndList();
	//foot
	glNewList(foot,GL_COMPILE);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(128,128,128);
		drawHemisphere(0.2,10,5,10,5);
		glScalef(1,0.1,2.5);
		drawHemisphere(0.2,10,5,10,5);
	glEndList();
}

void struct_hand(void)
{
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
  struct_head();
  struct_torso();
  struct_neck();
  struct_thigh();
  struct_upper_arm();
  struct_forearm();
  struct_leg();
  struct_hand();
  struct_dino_leg();
}
