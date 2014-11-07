#include <iostream>
#include <math.h>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "keyframe.hpp"
#include "render_drawing.hpp"
#include "gl_framework.hpp"

float abso(float a)
{
	if(a>0)return a;
	return -a;
}

void saveKeyframe()
{
	std::ofstream file;
	file.open("keyframes.txt", std::ios::app);
	file<<
		csX75::state<<" "<<
		mirror<<" "<<
		right_arm_angle<<" "<<
		left_arm_angle<<" "<<
		right_forearm_angle<<" "<<
		left_forearm_angle<<" "<<
		left_thigh_angle<<" "<<
		right_thigh_angle<<" "<<
		right_leg_angle<<" "<<
		left_leg_angle<<" "<<
		cam_z<<" "<<
		cam_ay<<" "<<
		pos_x<<" "<<
		pos_z<<" "<<
		dir<<" "<<
		camera<<" "<<
		light0<<" "<<
		light1<<" "<<
		light2<<" "<<
		headlight;
	file<<std::endl;
	file.close();

}

void loadKeyframe(GLFWwindow* window)
{
	std::ifstream file("keyframes.txt");
	file>>
		csX75::state>>
		mirror>>
		right_arm_angle>>
		left_arm_angle>>
		right_forearm_angle>>
		left_forearm_angle>>
		left_thigh_angle>>
		right_thigh_angle>>
		right_leg_angle>>
		left_leg_angle>>
		cam_z>>
		cam_ay>>
		pos_x>>
		pos_z>>
		dir>>
		camera>>
		light0>>
		light1>>
		light2>>
		headlight;
	int fps=60;
	float piover180 = 3.14159265358979324/180.0;
	double targetTime=0.0;
	if(csX75::state==1)transform_robot(window,0,fps,targetTime);
	else transform_dino(window,0,fps,targetTime);
	targetTime=0.0;
	glfwSetTime(0);
	render_drawing(window);
	glfwSwapBuffers(window);
	int st,cam;
	float ra,rf,la,lf,rt,lt,rl,ll,cx,cz,cy,px,pz,d;
	bool l0,l1,l2,h,m;
	while(!file.eof())
	{
		file>>st>>m>>ra>>la>>rf>>lf>>lt>>rt>>rl>>ll>>cz>>cy>>px>>pz>>d>>cam>>l0>>l1>>l2>>h;
		bool flag=true,move=true,rot=true;
		while(flag)
		{
			if(mirror!=m&&!m)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				mirror=false;
				for(int t=0;t<fps/2;t++)
				{
					while(glfwGetTime()<targetTime);
					targetTime = targetTime+1.0/fps;
					glfwSwapBuffers(window);
				}
			}
			flag=false;move=false;rot=false;
			if(cam!=camera){camera=cam;flag=true;}
			if(l0!=light0){light0=l0;flag=true;}
			if(l1!=light1){light1=l1;flag=true;}
			if(l2!=light2){light2=l2;flag=true;}
			if(h!=headlight){headlight=h;flag=true;}
			if(st!=csX75::state){if(csX75::state==1){transform_dino(window,1,fps,targetTime);csX75::state=3;}else{transform_robot(window,1,fps,targetTime);csX75::state=1;}}
			if(d>dir)
			{
				if(dir==360.0f)dir=0.0f;
				dir+=6;
				if(csX75::state == 3)
				{
					if(right_arm_angle>285)
					{
						right_arm_angle -= 3;
						left_arm_angle += 3;
					}
				}
				if(csX75::state == 1)
				{
					if(right_thigh_angle>-15)
					{
						right_arm_angle += 3;
						left_arm_angle -= 3;
						right_thigh_angle -= 3;
						left_thigh_angle += 3;
					}
				}
				rot=true;
				flag=true;
			}
			else if(d<dir)
			{
				dir-=6;
				if(dir==-6.0f)dir=354.0f;
				if(csX75::state == 3)
				{
					if(right_arm_angle<315)
					{
						right_arm_angle += 3;
						left_arm_angle -= 3;
					}
				}
				if(csX75::state == 1)
				{
					if(right_thigh_angle<15)
					{
						right_arm_angle -= 3;
						left_arm_angle += 3;
						right_thigh_angle += 3;
						left_thigh_angle -= 3;
					}
				}
				flag=true;
			}
			else
			{
				if(abso(pos_x-px)>0.0001||abso(pos_z-pz)>0.0001)
				{
					flag=true;
					if(cos(dir*piover180)*(px-pos_x)>0.0001||sin(dir*piover180)*(pos_z-pz)>0.0001)
					{
						pos_x+=cos(dir*piover180)/2;
						pos_z-=sin(dir*piover180)/2;
						if(csX75::state == 3) {
							right_arm_angle += 3*csX75::leg_dir;
							left_arm_angle -= 3*csX75::leg_dir;

							if(right_arm_angle>315) { csX75::leg_dir=-1; }
							if(left_arm_angle>315) { csX75::leg_dir=1; }
						}
						if(csX75::state == 1) {
							right_arm_angle -= 3*csX75::leg_dir;
							left_arm_angle += 3*csX75::leg_dir;

							right_thigh_angle += 3*csX75::leg_dir;
							left_thigh_angle -= 3*csX75::leg_dir;

							if(right_thigh_angle>15) { csX75::leg_dir=-1; }
							if(left_thigh_angle>15) { csX75::leg_dir=1; }
						}
						if(pos_x*pos_x+pos_z*pos_z>8100)
						{
							pos_x-=2*cos(dir*piover180);
							pos_z+=2*sin(dir*piover180);
						}
					}
					else
					{
						pos_x-=cos(dir*piover180)/2;
						pos_z+=sin(dir*piover180)/2;
						if(csX75::state == 3) {
							right_arm_angle -= 3*csX75::leg_dir;
							left_arm_angle += 3*csX75::leg_dir;

							if(right_arm_angle>315) { csX75::leg_dir=1; }
							if(left_arm_angle>315) { csX75::leg_dir=-1; }
						}
						if(csX75::state == 1) {
							right_arm_angle += 3*csX75::leg_dir;
							left_arm_angle -= 3*csX75::leg_dir;

							right_thigh_angle -= 3*csX75::leg_dir;
							left_thigh_angle += 3*csX75::leg_dir;

							if(right_thigh_angle>15) { csX75::leg_dir=1; }
							if(left_thigh_angle>15) { csX75::leg_dir=-1; }
						}
						if(pos_x*pos_x+pos_z*pos_z>8100)
						{
							pos_x+=2*cos(dir*piover180);
							pos_z-=2*sin(dir*piover180);
						}
					}
				}
				else
				{
					if(right_arm_angle>ra){right_arm_angle-=3;flag=true;}
					if(right_arm_angle<ra){right_arm_angle+=3;flag=true;}
					if(right_forearm_angle<rf){right_forearm_angle+=3;flag=true;}
					if(right_forearm_angle>rf){right_forearm_angle-=3;flag=true;}
					if(left_arm_angle>la){left_arm_angle-=3;flag=true;}
					if(left_arm_angle<la){left_arm_angle+=3;flag=true;}
					if(left_forearm_angle<lf){left_forearm_angle+=3;flag=true;}
					if(left_forearm_angle>lf){left_forearm_angle-=3;flag=true;}
					if(left_thigh_angle>lt){left_thigh_angle-=3;flag=true;}
					if(left_thigh_angle<lt){left_thigh_angle+=3;flag=true;}
					if(right_thigh_angle>rt){right_thigh_angle-=3;flag=true;}
					if(right_thigh_angle<rt){right_thigh_angle+=3;flag=true;}
					if(left_leg_angle<ll){left_leg_angle+=3;flag=true;}
					if(left_leg_angle>ll){left_leg_angle-=3;flag=true;}
					if(right_leg_angle<rl){right_leg_angle+=3;flag=true;}
					if(right_leg_angle>rl){right_leg_angle-=3;flag=true;}
					if(cam_ay>cy){cam_ay-=3;flag=true;}
					if(cam_ay<cy){cam_ay+=3;flag=true;}
					if(cam_z>cz){cam_z-=3;flag=true;}
					if(cam_z>cz){cam_z+=3;flag=true;}
				}
			}
			if(flag)
			{
				render_drawing(window);
				while(glfwGetTime()<targetTime);
				targetTime = targetTime+1.0/fps;
				glfwSwapBuffers(window);
			}
		}
	}
	file.close();
}

void capture_frame(unsigned int framenum)
{
	int SCREEN_WIDTH=640;
	int SCREEN_HEIGHT=640;
	unsigned char *pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];
	// set the framebuffer to read
	// default for double buffered
	glReadBuffer(GL_BACK);
	glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
	glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
	char filename[200];
	sprintf(filename,"frame_%04d.ppm",framenum);
	std::ofstream out(filename, std::ios::out);
	out<<"P6"<<std::endl;
	out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
	out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
	out.close();
	//function to store pRGB in a file named count
	delete pRGB;
}
