#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

/* 线程句柄 */
rt_thread_t Testthread_t = RT_NULL;

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	/* 创建线程 */
	Testthread_t = rt_thread_create("DataFromIPC",TestThread,NULL,1024,15,20);
	rt_thread_startup(Testthread_t);		//测试线程
}
