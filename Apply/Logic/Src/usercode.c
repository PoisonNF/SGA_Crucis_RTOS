#include "usercode.h"
#include "threadpool.h"
#include "drv_hal_conf.h"   //SGA库头文件配置
#include "task_conf.h"      //task层头文件配置
#include "ocd_conf.h"       //OCD层头文件配置
#include "config.h"			//I/O头文件配置

/* 线程句柄 */
rt_thread_t thread1 = RT_NULL;
rt_thread_t thread2 = RT_NULL;
rt_thread_t thread3 = RT_NULL;
rt_thread_t thread4 = RT_NULL;
rt_thread_t thread5 = RT_NULL;
rt_thread_t thread6 = RT_NULL;
rt_thread_t thread7 = RT_NULL;
rt_thread_t thread8 = RT_NULL;
rt_thread_t thread9 = RT_NULL;

/* 信号量句柄*/
rt_sem_t JY901_sem = RT_NULL;
rt_sem_t Jetson_sem = RT_NULL;
rt_sem_t OpenMV_sem = RT_NULL;
rt_sem_t Order_sem = RT_NULL;

/* 互斥量句柄 */
rt_mutex_t ps2_mutex = RT_NULL;

/*消息队列句柄*/
rt_mq_t msgqueue = RT_NULL;

ALIGN(RT_ALIGN_SIZE)
/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	//创建信号量
	JY901_sem = rt_sem_create("JY901_sem",0,RT_IPC_FLAG_FIFO);
	if(RT_NULL != JY901_sem)	rt_kprintf("RT-Thread create semaphore successful\r\n");
	else 						rt_kprintf("RT-Thread create semaphore failed\r\n");
	//创建Jetson信号量
	Jetson_sem = rt_sem_create("Jetson_sem",0,RT_IPC_FLAG_FIFO);
	if(RT_NULL != Jetson_sem)	rt_kprintf("RT-Thread create semaphoreJ successful\r\n");
	else 						rt_kprintf("RT-Thread create semaphoreJ failed\r\n");
	//创建OpenMV信号量
	OpenMV_sem = rt_sem_create("OpenMV_sem",0,RT_IPC_FLAG_FIFO);
	if(RT_NULL != OpenMV_sem)	rt_kprintf("RT-Thread create semaphoreJ successful\r\n");
	else 						rt_kprintf("RT-Thread create semaphoreJ failed\r\n");
	//创建Order信号量
	Order_sem = rt_sem_create("Order_sem",0,RT_IPC_FLAG_FIFO);
	if(RT_NULL != Order_sem)	rt_kprintf("RT-Thread create semaphoreO successful\r\n");
	else 						rt_kprintf("RT-Thread create semaphoreO failed\r\n");

	//创建互斥量
	ps2_mutex = rt_mutex_create("ps2_mutex",RT_IPC_FLAG_FIFO);
	if(RT_NULL != ps2_mutex)	rt_kprintf("RT-Thread create mutex successful\r\n");
	else						rt_kprintf("RT-Thread create mutex failed\r\n");
	//创建消息队列
	msgqueue = rt_mq_create("msgqueue",50,10,RT_IPC_FLAG_FIFO);
	if(RT_NULL != msgqueue)		rt_kprintf("RT-Thread create msgqueue successful\r\n");
	else						rt_kprintf("RT-Thread create msgqueue failed\r\n");

	//创建线程
	thread1 = rt_thread_create("Order",Order,NULL,512,1,20);
	if(RT_NULL != thread1)
	{
		rt_kprintf("RT-Thread create thread1 successful\r\n");
		rt_thread_startup(thread1);
	}
	else rt_kprintf("RT-Thread create thread1 failed\r\n");

	thread2 = rt_thread_create("Motioncontrol",Motioncontrol,NULL,512,3,20);
	if(RT_NULL != thread2)
	{
		rt_kprintf("RT-Thread create thread2 successful\r\n");
		rt_thread_startup(thread2);
	}
	else rt_kprintf("RT-Thread create thread2 failed\r\n");

	thread3 = rt_thread_create("JY901S",JY901S_thread,NULL,512,4,20);
	if(RT_NULL != thread3)
	{
		rt_kprintf("RT-Thread create thread3 successful\r\n");
		rt_thread_startup(thread3);
	}
	else rt_kprintf("RT-Thread create thread3 failed\r\n");

	thread4 = rt_thread_create("PS2",PS2_thread,NULL,512,3,20);
	if(RT_NULL != thread4)
	{
		rt_kprintf("RT-Thread create thread4 successful\r\n");
		rt_thread_startup(thread4);
	}
	else rt_kprintf("RT-Thread create thread4 failed\r\n");

	thread5 = rt_thread_create("Huba511",Huba511_thread,NULL,512,4,20);
	if(RT_NULL != thread5)
	{
		rt_kprintf("RT-Thread create thread5 successful\r\n");
		//rt_thread_startup(thread5);
	}
	else rt_kprintf("RT-Thread create thread5 failed\r\n");

	thread6 = rt_thread_create("Rm3100",Rm3100_thread,NULL,512,5,20);
	if(RT_NULL != thread6)
	{
		rt_kprintf("RT-Thread create thread6 successful\r\n");
		rt_thread_startup(thread6);
	}
	else rt_kprintf("RT-Thread create thread6 failed\r\n");

	thread7 = rt_thread_create("Jetson",Jetson_thread,NULL,1024,2,20);
	if(RT_NULL != thread7)
	{
		rt_kprintf("RT-Thread create thread7 successful\r\n");
		rt_thread_startup(thread7);
	}
	else rt_kprintf("RT-Thread create thread7 failed\r\n");

	thread8 = rt_thread_create("OpenMV",OpenMV_thread,NULL,512,4,20);
	if(RT_NULL != thread8)
	{
		rt_kprintf("RT-Thread create thread8 successful\r\n");
		rt_thread_startup(thread8);
	}
	else rt_kprintf("RT-Thread create thread8 failed\r\n");

	thread9 = rt_thread_create("Test",Test_thread,NULL,512,6,20);
	if(RT_NULL != thread9)
	{
		rt_kprintf("RT-Thread create thread9 successful\r\n");
		//rt_thread_startup(thread9);
	}
	else rt_kprintf("RT-Thread create thread9 failed\r\n");

}
