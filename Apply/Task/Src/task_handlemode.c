#include "task_handlemode.h"

/**
 * @brief �ֶ�ģʽ������
 * @param HMInfo �ֶ�ģʽ��Ϣ�ṹ��ָ��
 */
void Task_HandleMode_Process(HandleModeInfo *HMInfo)
{
    //��0������ʾ
    if(HMInfo->JoystickInfo[0] != 0.0f && HMInfo->JoystickInfo[1] != 0.0f)
        printf("%f %f\r\n",HMInfo->JoystickInfo[0],HMInfo->JoystickInfo[1]);
    
    //�ֱ��������㣬��ֹ�ظ�ʹ��
    HMInfo->JoystickInfo[0] = 0.0f;
    HMInfo->JoystickInfo[1] = 0.0f;
}
