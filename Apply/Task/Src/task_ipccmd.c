#include "task_ipccmd.h"

/**
 * @brief 上位机命令处理函数
 * @param Null
 */
void Task_IPCcmd_Handle(void)
{
    uint8_t IPC_ReceBuf[100];
    uint8_t IPC_ReceNum = 0;

    //串口一和串口三都要接收，因为不确定是哪个发送指令
    if(rt_sem_take(CmdFromIPC_Sem,RT_WAITING_FOREVER) == RT_EOK)
    {
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart1,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u1 %s\r\n",IPC_ReceBuf);    //根据通信协议校验
            goto CmdAnalysis;
        }
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart3,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u3 %s\r\n",IPC_ReceBuf);    //根据通信协议校验
            goto CmdAnalysis;
        }

CmdAnalysis:
        /* 帧头帧尾校验 */
        if(IPC_ReceBuf[0] == '@' && IPC_ReceBuf[IPC_ReceNum - 1] == '$')
        {
            /* 模式控制命令 @SM */
            if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'M')
            {
                if(!strncmp((char*)IPC_ReceBuf + 3,"AUTO", 4))
                {
                    printf("AUTO\r\n");     //切换自动模式
                }
                else if(!strncmp((char*)IPC_ReceBuf + 3,"MANU", 4))
                {
                    printf("MANU\r\n");     //切换手动模式
                }
            }
            /* 时间同步 @TS */
            else if(IPC_ReceBuf[1] == 'T' && IPC_ReceBuf[2] == 'S')
            {
                Task_DS1337_SYNC(IPC_ReceBuf);
            }
        }

        IPC_ReceNum = 0;
    }
}


