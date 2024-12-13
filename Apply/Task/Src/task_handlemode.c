#include "task_handlemode.h"

/**
 * @brief 手动模式处理函数
 * @param HMInfo 手动模式信息结构体指针
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
    //非0数据显示
    if(HMInfo->JoystickInfo[0] != 0.0f && HMInfo->JoystickInfo[1] != 0.0f)
        printf("%f %f\r\n",HMInfo->JoystickInfo[0],HMInfo->JoystickInfo[1]);
    
    //手柄数据清零，防止重复使用
    HMInfo->JoystickInfo[0] = 0.0f;
    HMInfo->JoystickInfo[1] = 0.0f;
}
