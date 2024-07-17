#include "task_reportdata.h"

uint8_t ReportDataBuffer[FRAMEEND_BASE + 1] = {0};      //�������ݻ�����

/**
 * @brief ���ⲿ�������ݴ�����
 * @param Null
 */
void Task_ReportData_Handle(void)
{
    ReportDataBuffer[FRAMESTART_BASE] = '@';
    ReportDataBuffer[FRAMESTART_BASE + 1] = 'D';
    ReportDataBuffer[FRAMESTART_BASE + 2] = 'U';
    ReportDataBuffer[FRAMESTART_BASE + 3] = 'P';
    ReportDataBuffer[FRAMEEND_BASE] = '$';

    while(1)
    {
        Drv_Uart_Transmit_DMA(&Uart3,ReportDataBuffer,FRAMEEND_BASE + 1);
        Drv_Delay_Ms(500);
    }
}



