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

/* �ź������*/
rt_sem_t JY901S_Sem = RT_NULL;		//JY901S�����ź���

/* �û��߼����� */
void UserLogic_Code(void)
{
	/* �����ź��� */
	JY901S_Sem = rt_sem_create("JY901Sem",0,RT_IPC_FLAG_FIFO);

	/* �����߳� */
	TestThread_t 		= rt_thread_create("DataFromIPC",TestThread,NULL,512,15,20);
	ReportDataThread_t  = rt_thread_create("ReportDataThread",ReportDataThread,NULL,512,2,20);
	JY901Thread_t 		= rt_thread_create("JY901Thread",JY901Thread,NULL,512,7,20);

	//rt_thread_startup(TestThread_t);			//�����߳�
	rt_thread_startup(ReportDataThread_t);		//���������߳�
	rt_thread_startup(JY901Thread_t);			//JY901�߳�
}
