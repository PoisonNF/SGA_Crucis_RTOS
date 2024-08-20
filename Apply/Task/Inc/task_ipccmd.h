#ifndef __TASK_IPCCMD_H__
#define __TASK_IPCCMD_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_reportdata.h"
#include "task_ds1337.h"

typedef struct 
{
    uint8_t ModeChange;    //ģʽ�л���־
    float fNum[3];          //��Ÿ���������
    bool keyPressed;
}HandleModeInfo;

typedef struct 
{
    uint8_t ModeChange;    //ģʽ�л���־
}AutoModeInfo;

void Task_IPCcmd_Handle(void);

#endif // !__TASK_IPCCMD_H__

