#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

/* �߳̾�� */
rt_thread_t Testthread_t = RT_NULL;

/* �û��߼����� */
void UserLogic_Code(void)
{
	/* �����߳� */
	Testthread_t = rt_thread_create("DataFromIPC",TestThread,NULL,1024,15,20);
	rt_thread_startup(Testthread_t);		//�����߳�
}
