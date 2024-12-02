#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

/* �߳̾�� */
rt_thread_t TestThread_t = RT_NULL;
rt_thread_t ReportDataThread_t = RT_NULL;
rt_thread_t JY901Thread_t = RT_NULL;
rt_thread_t MS5837Thread_t = RT_NULL;
rt_thread_t AD4111Thread_t = RT_NULL;
rt_thread_t IPCcmdThread_t = RT_NULL;
rt_thread_t IMX6ULLThread_t = RT_NULL;
rt_thread_t DS1337Thread_t = RT_NULL;
rt_thread_t AutoModeThread_t = RT_NULL;
rt_thread_t HandleModeThread_t = RT_NULL;

/* �ź������ */
rt_sem_t JY901S_Sem = RT_NULL;			//JY901S�����ź���
rt_sem_t CmdFromIPC_Sem = RT_NULL;		//��λ�������ź���

/*��Ϣ���о��*/
rt_mq_t AutoModemq = RT_NULL;		//�Զ�ģʽ��Ϣ����
rt_mq_t HandleModemq = RT_NULL;		//�ֶ�ģʽ��Ϣ����

/* �û��߼����� */
void UserLogic_Code(void)
{
	/* �����ź��� */
	JY901S_Sem = rt_sem_create("JY901Sem",0,RT_IPC_FLAG_FIFO);
	CmdFromIPC_Sem = rt_sem_create("CmdFromIPC_Sem",0,RT_IPC_FLAG_FIFO);

	/* ������Ϣ���� */
	AutoModemq = rt_mq_create("AutoModemq",50,50,RT_IPC_FLAG_FIFO);
	HandleModemq = rt_mq_create("HandleModemq",50,50,RT_IPC_FLAG_FIFO);

	/* �����߳� */
	TestThread_t 		= rt_thread_create("DataFromIPC",TestThread,NULL,1024,15,20);
	ReportDataThread_t  = rt_thread_create("ReportDataThread",ReportDataThread,NULL,512,2,20);
	JY901Thread_t 		= rt_thread_create("JY901Thread",JY901Thread,NULL,512,7,20);
	MS5837Thread_t 		= rt_thread_create("MS5837Thread",MS5837Thread,NULL,512,8,20);
	AD4111Thread_t 		= rt_thread_create("AD4111Thread",AD4111Thread,NULL,512,8,20);
	IPCcmdThread_t 		= rt_thread_create("IPCcmdThread",IPCcmdThread,NULL,512,1,20);
	IMX6ULLThread_t 	= rt_thread_create("IMX6ULLThread",IMX6ULLThread,NULL,1024,4,20);
	DS1337Thread_t 		= rt_thread_create("DS1337Thread",DS1337Thread,NULL,512,9,20);
	HandleModeThread_t 	= rt_thread_create("HandleModeThread",HandleModeThread,NULL,512,5,20);
	AutoModeThread_t 	= rt_thread_create("AutoModeThread",AutoModeThread,NULL,512,5,20);

#define TEST

#ifdef TEST
	rt_thread_startup(TestThread_t);			//�����߳�

#else
	rt_thread_startup(ReportDataThread_t);		//���������߳�
	rt_thread_startup(JY901Thread_t);			//JY901�߳�
	rt_thread_startup(MS5837Thread_t);			//MS5837�߳�
	rt_thread_startup(AD4111Thread_t);			//AD4111�߳�
	rt_thread_startup(IPCcmdThread_t);			//��λ�������߳�
	rt_thread_startup(IMX6ULLThread_t);			//I.MX6ull�߳�
	rt_thread_startup(DS1337Thread_t);			//DS1337�߳�
	rt_thread_startup(HandleModeThread_t);		//�ֶ��߳�
	rt_thread_startup(AutoModeThread_t);		//�Զ��߳�
#endif // TEST
}
