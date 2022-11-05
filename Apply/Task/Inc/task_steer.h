#ifndef __TASK_STEER_H_
#define __TASK_STEER_H_


void Task_Steer_Init(void);
void Task_Steer_Angle_Set(int index,int ang);
void Task_Steer_0Angle(int index);
void Task_AllSteer_0Angle(void);
void Task_Steer_90Angle(int index);
void Task_AllSteer_90Angle(void);
void Task_Steer_180Angle(int index);
void Task_AllSteer_180Angle(void);

#endif


