#ifndef __TASK_HANDLEMODE_H_
#define __TASK_HANDLEMODE_H_

#include "drv_hal_conf.h"

/* �ֶ�ģʽ��Ϣ�ṹ�� */
typedef struct 
{
    uint8_t ModeChange;             //ģʽ�л���־
    float JoystickInfo[2];          //����ֱ�����
    bool keyPressed;
}HandleModeInfo;

void Task_HandleMode_Process(HandleModeInfo *HMInfo);

#endif
