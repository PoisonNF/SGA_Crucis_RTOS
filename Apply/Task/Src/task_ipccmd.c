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
            //printf("u1 %s\r\n",IPC_ReceBuf);    //����ͨ��Э��У��
            goto CmdAnalysis;
        }
        IPC_ReceNum = Drv_Uart_Receive_DMA(&Uart3,IPC_ReceBuf);
        if(IPC_ReceNum != 0)
        {
            //printf("u3 %s\r\n",IPC_ReceBuf);    //����ͨ��Э��У��
            goto CmdAnalysis;
        }

CmdAnalysis:
        /* ֡ͷ֡βУ�� */
        if(IPC_ReceBuf[0] == '@' && IPC_ReceBuf[IPC_ReceNum - 1] == '$')
        {
            /* ʱ��ͬ�� @TS */
            if(IPC_ReceBuf[1] == 'T' && IPC_ReceBuf[2] == 'S')
            {
                Task_DS1337_SYNC(IPC_ReceBuf);
            }
            /* PID���� @AP */
            else if(IPC_ReceBuf[1] == 'A' && IPC_ReceBuf[2] == 'P')
            {
                // �������
                int PID_NO;
                float P,I,D;
                char *token;

                // ʹ��strtok()�������зָ�
                token = strtok((char *)IPC_ReceBuf, " "); // ��ȡ��һ�� "@AP"
                token = strtok(NULL, " "); // ��ȡ PID_NO
                PID_NO = atoi(token); // ת��Ϊ��������ֵ�� PID_NO
                token = strtok(NULL, " "); // ��ȡ P
                P = atof(token); // ת��Ϊ����������ֵ�� P
                token = strtok(NULL, " "); // ��ȡ I
                I = atof(token); // ת��Ϊ����������ֵ�� I
                token = strtok(NULL, " "); // ��ȡ D
                D = atof(token); // ת��Ϊ����������ֵ�� D
#ifdef DEBUG_PRINTF 
                // ��ӡ���
                printf("PID_NO: %d", PID_NO);
                printf("P: %f", P);
                printf("I: %f", I);
                printf("D: %f", D);
#endif
                UNUSED(PID_NO);UNUSED(P);UNUSED(I);UNUSED(D);
                //����PID��Ÿ���
                if(PID_NO == 1){
                    //�޸����PID
                }else if(PID_NO == 2){
                    //�޸�����PID
                }
            }
            /* ģʽ�������� @SM */
            else if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'M')
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
            /* �ֱ���Ϣ @HCV��@HCB */
            else if(IPC_ReceBuf[1] == 'H' && IPC_ReceBuf[2] == 'C')
            {
                char *token;
                // ʹ��strtok()�������зָ�
                token = strtok((char *)IPC_ReceBuf, " "); // ��ȡ��һ�� "@HCV"����"@HCB"
                if(IPC_ReceBuf[3] == 'V')
                {
                    token = strtok(NULL, " "); // ��ȡҡ�˽Ƕ�
                    HMInfo.JoystickInfo[0] = atof(token); // �Ƕ�
                    token = strtok(NULL, " "); // ��ȡҡ������
                    HMInfo.JoystickInfo[1] = atof(token); // ����
                    printf("Joystick %f %f\r\n",HMInfo.JoystickInfo[0],HMInfo.JoystickInfo[1]);
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
                else if(IPC_ReceBuf[3] == 'B')
                {
                    token = strtok(NULL, " "); // ��ȡ�������
                    uint8_t key = strtod(token,NULL); // �������
                    printf("NO.%d",key);
                    token = strtok(NULL, " "); // ��ȡ����״̬
                    if(!rt_strcmp(token,"Press")){
                        printf("Press\r\n");
                        HMInfo.keyPressed = true;
                    }else{
                        printf("Release\r\n");
                        HMInfo.keyPressed = false;
                    }
                    rt_mq_send(HandleModemq,&HMInfo,sizeof(HandleModeInfo));
                }
            }
            /* �������� @FY */
            else if(IPC_ReceBuf[1] == 'F' && IPC_ReceBuf[2] == 'Y')
            {
                float ProposedYaw;      //�ⶨ�ĺ����
                char *token;

                // ʹ��strtok()�������зָ�
                token = strtok((char *)IPC_ReceBuf, " "); // ��ȡ��һ�� "@FY"
                token = strtok(NULL, " "); // ��ȡ�ⶨ�����
                ProposedYaw = atof(token); // ת��Ϊ����������ֵ��ProposedYaw
#ifdef DEBUG_PRINTF
                // ��ӡ���
                printf("ProposedYaw: %f\r\n", ProposedYaw);
#endif
                AMInfo.Yaw = ProposedYaw;
                rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
            }            
            /* ������� @FD */
            else if(IPC_ReceBuf[1] == 'F' && IPC_ReceBuf[2] == 'D')
            {
                float ProposedDepth;      //�ⶨ�ĺ����
                char *token;

                // ʹ��strtok()�������зָ�
                token = strtok((char *)IPC_ReceBuf, " "); // ��ȡ��һ�� "@FD"
                token = strtok(NULL, " "); // ��ȡ�ⶨ�����
                ProposedDepth = atof(token); // ת��Ϊ����������ֵ��ProposedDepth
#ifdef DEBUG_PRINTF
                // ��ӡ���
                printf("ProposedDepth: %f\r\n", ProposedDepth);
#endif
                AMInfo.Depth = ProposedDepth;
                rt_mq_send(AutoModemq,&AMInfo,sizeof(AutoModeInfo));
            }
            /* ֹͣ���� @STOP */
            else if(IPC_ReceBuf[1] == 'S' && IPC_ReceBuf[2] == 'T' && IPC_ReceBuf[3] == 'O' && IPC_ReceBuf[4] == 'P')
            {
                printf("STOP!\r\n");
            }
        }

        IPC_ReceNum = 0;
    }
}


