#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

/* 线程句柄 */
rt_thread_t TestThread_t = RT_NULL;
rt_thread_t ReportDataThread_t = RT_NULL;
rt_thread_t JY901Thread_t = RT_NULL;

/* 信号量句柄*/
rt_sem_t JY901S_Sem = RT_NULL;		//JY901S数据信号量

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	/* 创建信号量 */
	JY901S_Sem = rt_sem_create("JY901Sem",0,RT_IPC_FLAG_FIFO);

	/* 创建线程 */
	TestThread_t 		= rt_thread_create("DataFromIPC",TestThread,NULL,512,15,20);
	ReportDataThread_t  = rt_thread_create("ReportDataThread",ReportDataThread,NULL,512,2,20);
	JY901Thread_t 		= rt_thread_create("JY901Thread",JY901Thread,NULL,512,7,20);

	//rt_thread_startup(TestThread_t);			//测试线程
	rt_thread_startup(ReportDataThread_t);		//报告数据线程
	rt_thread_startup(JY901Thread_t);			//JY901线程
}
