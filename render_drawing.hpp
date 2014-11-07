#ifndef RENDER_DRAWING_HPP
#define RENDER_DRAWING_HPP

extern float bust_angle_y;
extern float bust_angle_x;
extern float armor_angle;
extern int head_pop;
extern float head_angle;
extern float right_arm_angle;
extern float left_arm_angle;
extern float right_arm_angle2;
extern float left_arm_angle2;
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
extern float height;
extern float cam_x,cam_z,cam_ay;
extern float pos_x,pos_z,dir;

extern int camera;

extern bool light0;
extern bool light1;
extern bool light2;
extern bool headlight;

extern GLuint armort[1];
extern GLuint headt[1];
extern GLuint dinot[1];
extern GLuint grasst[1];
extern GLuint skyt[1];

void render_drawing(GLFWwindow* window);
void transform_robot(GLFWwindow* window);
void transform_dino(GLFWwindow* window);

#endif // RENDER_DRAWING_HPP
