#include "keyframe.hpp"
#include "render_drawing.hpp"

#include <iostream>
#include <fstream>

void saveKeyframe() {
	ofstream file;
	file.open("keyframes.txt", ios::app);
	file<<
		bust_angle_y<<" "<<
		bust_angle_x<<" "<<
		armor_angle<<" "<<
		head_pop<<" "<<
		right_arm_angle<<" "<<
		left_arm_angle<<" "<<
		right_forearm_angle<<" "<<
		left_forearm_angle<<" "<<
		left_thigh_angle<<" "<<
		right_thigh_angle<<" "<<
		right_leg_angle<<" "<<
		left_leg_angle<<" "<<
		right_foot_angle<<" "<<
		left_foot_angle<<" "<<
		left_d_leg_angle<<" "<<
		right_wrist_angle<<" "<<
		left_wrist_angle<<" "<<
		right_d_leg_angle<<" "<<
		height<<" "<<
		cam_x<<" "<<
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
	file<<endl;
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
