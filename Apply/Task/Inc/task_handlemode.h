#ifndef __TASK_HANDLEMODE_H_
#define __TASK_HANDLEMODE_H_

#include "drv_hal_conf.h"

/* 手动模式信息结构体 */
typedef struct 
{
    uint8_t ModeChange;     //模式切换标志
    float fNum[3];          //存放浮点数数据
    bool keyPressed;
}HandleModeInfo;

void Task_HandleMode_Process(HandleModeInfo *HMInfo);

#endif
