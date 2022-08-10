#ifndef __TASK_MOTOR_H_
#define	__TASK_MOTOR_H_

void Task_Motor_Init(void);
void Task_Motor_SpeedSet(int index,float _fVal);
void Task_Motor_Start(int index,float _fVal);
void Task_Motor_Stop(int index);

#endif
