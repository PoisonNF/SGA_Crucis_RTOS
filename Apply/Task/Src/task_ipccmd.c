#include "task_ipccmd.h"

/**
 * @brief ��λ���������
 * @param Null
 */
void Task_IPCcmd_Handle(void)
{
    uint8_t IPC_ReceBuf[100];
    uint8_t IPC_ReceNum = 0;

    HandleModeInfo HMInfo = {0};        //�ֶ�ģʽ��Ϣ
    AutoModeInfo AMInfo = {0};          //�Զ�ģʽ��Ϣ

    //����һ�ʹ�������Ҫ���գ���Ϊ��ȷ�����ĸ�����ָ��
    if(rt_sem_take(CmdFromIPC_Sem,RT_WAITING_FOREVER) == RT_EOK)
    {
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart1,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u1 %s\r\n",IPC_ReceBuf);    //����ͨ��Э��У��
            goto CmdAnalysis;
        }
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart3,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            printf("u3 %s\r\n",IPC_ReceBuf);    //����ͨ��Э��У��
            goto CmdAnalysis;
        }

CmdAnalysis:
        /* ֡ͷ֡βУ�� */
        if(IPC_ReceBuf[0] == '@' && IPC_ReceBuf[IPC_ReceNum - 1] == '$')
        {
            /* ģʽ�������� @SM */
            if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'M')
            {
                if(!strncmp((char*)IPC_ReceBuf + 3,"AUTO", 4))
                {
                    printf("AUTO\r\n");     //�л��Զ�ģʽ
                    //�����ֱ�����ģʽ�������Զ�ģʽ
                    HMInfo.ModeChange = 1;
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
                else if(!strncmp((char*)IPC_ReceBuf + 3,"MANU", 4))
                {
                    printf("MANU\r\n");     //�л��ֶ�ģʽ
                    //�����Զ�ģʽ�������ֱ�����ģʽ
                    AMInfo.ModeChange = 1;
                    rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
                }
            }
            /* ʱ��ͬ�� @TS */
            else if(IPC_ReceBuf[1] == 'T' && IPC_ReceBuf[2] == 'S')
            {
                Task_DS1337_SYNC(IPC_ReceBuf);
            }
        }

        IPC_ReceNum = 0;
    }
}


