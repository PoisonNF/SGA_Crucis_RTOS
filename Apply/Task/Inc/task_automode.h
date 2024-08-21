#ifndef __TASK_AUTOMODE_H_
#define __TASK_AUTOMODE_H_

#include "drv_hal_conf.h"

/* 自动模式信息结构体 */
typedef struct 
{
    uint8_t ModeChange;    //模式切换标志
}AutoModeInfo;

void Task_AutoMode_Process(AutoModeInfo *AMInfo);

#endif
