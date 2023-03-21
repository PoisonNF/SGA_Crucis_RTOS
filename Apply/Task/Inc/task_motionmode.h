#ifndef __TASK_MOTIONMODE_H_
#define __TASK_MOTIONMODE_H_

#define PI 3.1415926

float *Task_Horizontal_Heading_Calculation(uint16_t P,float ¦È);
void Task_Motion_Process(int L_Diff,int R_Diff);
void Task_Motioncontrol(int PS2_LY,int PS2_RX,int PS2_KEY);

#endif

