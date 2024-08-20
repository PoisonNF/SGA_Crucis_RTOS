#ifndef __TASK_IPCCMD_H__
#define __TASK_IPCCMD_H__

#include "drv_hal_conf.h"
#include "config.h"
#include "usercode.h"
#include "task_reportdata.h"
#include "task_ds1337.h"

typedef struct 
{
    uint8_t ModeChange;    //模式切换标志
    float fNum[3];          //存放浮点数数据
    bool keyPressed;
}HandleModeInfo;

typedef struct 
{
    uint8_t ModeChange;    //模式切换标志
}AutoModeInfo;

void Task_IPCcmd_Handle(void);

#endif // !__TASK_IPCCMD_H__

