#include "task_imx6ull.h"

static uint8_t IMX6ULL_ReceBuf[150];
static uint8_t IMX6ULL_ReceNum = 0;
/**
 * @brief IMX6ULL´¦Àíº¯Êý
 * @param Null
 */
void Task_IMX6ULL_Handle(void)
{
    IMX6ULL_ReceNum = Drv_Uart_Receive_DMA(&Uart4,IMX6ULL_ReceBuf);
    if(IMX6ULL_ReceNum != 0)
    {
        Drv_Uart_Transmit(&Uart1,IMX6ULL_ReceBuf,IMX6ULL_ReceNum);
        //Drv_Uart_Transmit(&Uart4,IMX6ULL_ReceBuf,IMX6ULL_ReceNum);
        IMX6ULL_ReceNum = 0;
    }
}
