#ifndef __TASK_MOTOR_H_
#define	__TASK_MOTOR_H_

void Task_Motor_Init(void);
void Task_Motor_SpeedSet(int index,uint16_t freq);
void Task_Motor_AllSpeedSet(uint16_t _freq);
void Task_Motor_Start(int index,uint16_t freq);
void Task_Motor_AllStart(float *adress);
void Task_Motor_Stop(int index);
void Task_Motor_AllStop(void);

#endif
