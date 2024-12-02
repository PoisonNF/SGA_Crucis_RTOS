#include "usercode.h"		/* usercodeͷ�ļ� */
#include "threadpool.h"		/* threadpoolͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */


/* �߳���ں�����ʹ��������Դ��ļ��� */
/* �Զ��߳� */
void AutoModeThread(void* paramenter)
{
    AutoModeInfo AMInfo;
    HandleModeInfo ClearBuf;

    //Ĭ�Ϲ����Զ�ģʽ
    rt_thread_suspend(rt_thread_self());
    rt_schedule();

    while(1)
    {
        if(rt_mq_recv(AutoModemq,&AMInfo,sizeof(AutoModeInfo),RT_WAITING_NO) == RT_EOK)
        {
            //�Զ�������Ϣ���н��յ����ݣ����л����ֱ�ģʽ
            if(AMInfo.ModeChange)
            {
                AMInfo.ModeChange = 0;
                //��HandleModemq�����������������
                while(1)
                {
                    if(rt_mq_recv(HandleModemq,&ClearBuf,sizeof(HandleModeInfo),RT_WAITING_NO) != RT_EOK)
                        break;
                }

                printf("Switch to HANDLE Mode\r\n");
                rt_enter_critical();                    //����������
                rt_thread_suspend(rt_thread_self());    //�����߳�
                rt_thread_resume(HandleModeThread_t);   //�ָ��ֶ������߳�
                rt_exit_critical();                     //����������
                rt_schedule();                          //����ִ��һ�ε���
            }
        }
        printf("AutoMode\r\n");
        Drv_Delay_Ms(1000);
        rt_thread_yield();
    }
}
/* �ֶ��߳� */
void HandleModeThread(void* paramenter)
{
    HandleModeInfo HMInfo;
    AutoModeInfo ClearBuf;

    while(1)
    {
        if(rt_mq_recv(HandleModemq,&HMInfo,sizeof(HandleModeInfo),RT_WAITING_NO) == RT_EOK)
        {
            //�ֱ�������Ϣ���н��յ����ݣ����л����Զ�ģʽ
            if(HMInfo.ModeChange)
            {
                HMInfo.ModeChange = 0;
                //��AutoModemq��Ϣ�����������������
                while(1)
                {
                    if(rt_mq_recv(AutoModemq,&ClearBuf,sizeof(AutoModeInfo),RT_WAITING_NO) != RT_EOK)
                        break;
                }
                
                printf("Switch to AUTO Mode\r\n");
                rt_enter_critical();                    //����������
                rt_thread_suspend(rt_thread_self());    //�����߳�
                rt_thread_resume(AutoModeThread_t);     //�ָ��Զ������߳�
                rt_exit_critical();                     //����������
                rt_schedule();                          //����ִ��һ�ε���
            }
        }
        
        printf("HandleMode\r\n");
        Drv_Delay_Ms(500);  //ִ��ʱ������λ���ֱ�����һ֡����ʱ����ͬ
        rt_thread_yield();
    }
}

/* �����߳� */
void TestThread(void* paramenter)
{
//    while(1)
//    {
        Task_Test_Handle();
//        rt_thread_yield();
//    }
}

/* ���������߳� */
void ReportDataThread(void* paramenter)
{
    Task_ReportData_Handle();
}

/* ��ȡJY901S�����߳� */
void JY901Thread(void* paramenter)
{
    while(1)
    {
        Task_JY901_Handle();
        Drv_Delay_Ms(400);
    }
}

/* ��ȡMS5837�����߳� */
void MS5837Thread(void* paramenter)
{
    while(1)
    {
        Task_MS5837_Handle();
        Drv_Delay_Ms(600);
    }    
}

/* ��ȡAD4111�����߳� */
void AD4111Thread(void* paramenter)
{
    Task_AD4111_Sync();
    while(1)
    {
        Task_AD4111_Handle();
        Drv_Delay_Ms(500);
    }
}

/* ��λ����������߳� */
void IPCcmdThread(void* paramenter)
{
    while(1)
    {
        Task_IPCcmd_Handle();
        Drv_Delay_Ms(1);
    }
}

/* I.MX6ull�����߳� */
void IMX6ULLThread(void* paramenter)
{
    while(1)
    {
        Task_IMX6ULL_Handle();
        Drv_Delay_Ms(1);     
    }
}

/* DS1337�����߳� */
void DS1337Thread(void* paramenter)
{
    while(1)
    {
        Task_DS1337_Handle();
        Drv_Delay_Ms(1000);     
    }
}
