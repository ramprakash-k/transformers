#ifndef _RENDER_DRAWING_HPP_
#define _RENDER_DRAWING_HPP_

extern float bust_angle_y;
extern float bust_angle_x;
extern float armor_angle;
extern int head_pop;
extern float right_arm_angle;
extern float left_arm_angle;
extern float right_forearm_angle;
extern float left_forearm_angle;
extern float left_thigh_angle;
extern float right_thigh_angle;
extern float right_leg_angle;
extern float left_leg_angle;
extern float right_foot_angle;
extern float left_foot_angle;
extern float left_d_leg_angle;
extern float right_wrist_angle;
extern float left_wrist_angle;
extern float right_d_leg_angle;
extern float lightturn,lightturn1;
extern float cam_x,cam_z,cam_ay;

extern GLuint armort[1];
extern GLuint headt[1];
extern GLuint dinot[1];

void render_drawing(GLFWwindow* window);

#endif
