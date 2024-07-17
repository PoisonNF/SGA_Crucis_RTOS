#include "task_ipccmd.h"

/**
 * @brief 上位机命令处理函数
 * @param Null
 */
void Task_IPCcmd_Handle(void)
{
    uint8_t ReceBuf[100];
    uint8_t ReceNum = 0;

    //串口一和串口三都要接收，因为不确定是哪个发送指令
    if(rt_sem_take(CmdFromIPC_Sem,RT_WAITING_FOREVER) == RT_EOK)
    {
        ReceNum = Drv_Uart_Receive_DMA(&Uart1,ReceBuf);
        if(ReceNum != 0)
        {
            printf("u1 %s\r\n",ReceBuf);    //根据通信协议校验
            ReceNum = 0;
        }
        ReceNum = Drv_Uart_Receive_DMA(&Uart3,ReceBuf);
        if(ReceNum != 0)
        {
            printf("u3 %s\r\n",ReceBuf);    //根据通信协议校验
            ReceNum = 0;
        }
    }
}


