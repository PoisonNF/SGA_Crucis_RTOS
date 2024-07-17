#include "task_ipccmd.h"

/**
 * @brief ��λ���������
 * @param Null
 */
void Task_IPCcmd_Handle(void)
{
    uint8_t ReceBuf[100];
    uint8_t ReceNum = 0;

    //����һ�ʹ�������Ҫ���գ���Ϊ��ȷ�����ĸ�����ָ��
    if(rt_sem_take(CmdFromIPC_Sem,RT_WAITING_FOREVER) == RT_EOK)
    {
        ReceNum = Drv_Uart_Receive_DMA(&Uart1,ReceBuf);
        if(ReceNum != 0)
        {
            printf("u1 %s\r\n",ReceBuf);    //����ͨ��Э��У��
            ReceNum = 0;
        }
        ReceNum = Drv_Uart_Receive_DMA(&Uart3,ReceBuf);
        if(ReceNum != 0)
        {
            printf("u3 %s\r\n",ReceBuf);    //����ͨ��Э��У��
            ReceNum = 0;
        }
    }
}


