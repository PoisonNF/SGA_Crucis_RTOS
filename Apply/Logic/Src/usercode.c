#include "usercode.h"
#include "drv_hal_conf.h"   //SGA库头文件配置
#include "task_conf.h"      //task层头文件配置
#include "ocd_conf.h"       //OCD层头文件配置
#include "bsp_io.h"			//I/O头文件配置

/* 线程句柄 */
rt_thread_t thread1 = RT_NULL;
rt_thread_t thread2 = RT_NULL;
rt_thread_t thread3 = RT_NULL;

/* 信号量句柄*/
rt_sem_t binary_sem = RT_NULL;

/*消息队列句柄*/
rt_mq_t msgqueue = RT_NULL;

/*thread1处理数据线程*/
void thread1_entry(void* paramenter)
{
	
	while(1)
	{

		if(rt_sem_take(binary_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			OCD_JY901_DataProcess(&JY901S);
			OCD_JY901_DataConversion(&JY901S);
			OCD_JY901_Printf(&JY901S);
		}
		rt_thread_yield();
	}
}
/*thread2 led线程*/
void thread2_entry(void* paramenter)
{
	while(1)
	{
		Drv_GPIO_Write(&demoGPIO[0],GPIO_PIN_RESET);
		Drv_Delay_Ms(1000);
		Drv_GPIO_Write(&demoGPIO[0],GPIO_PIN_SET);

		Drv_GPIO_Write(&demoGPIO[1],GPIO_PIN_RESET);
		Drv_Delay_Ms(1000);
		Drv_GPIO_Write(&demoGPIO[1],GPIO_PIN_SET);
		rt_thread_yield();
	}
}

/* thread3 消息队列线程*/
void thread3_entry(void* paramenter)
{
	char buf[50];
	int i = 0;
	while(1)
	{
		if(rt_mq_recv(msgqueue,buf,sizeof(buf),RT_WAITING_FOREVER) == RT_EOK)
		{
			rt_kprintf("%s\r\n",buf);
			OCD_OLED_ShowNum(&tOLED,0,0,i,2,16);
			i++;
		}
		rt_thread_yield();
	}
}

ALIGN(RT_ALIGN_SIZE)
//static char thread2_stack[128];
/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	//创建信号量
	binary_sem = rt_sem_create("binary_sem",
								0,
								RT_IPC_FLAG_FIFO);
	if(RT_NULL != binary_sem)
	{
		rt_kprintf("RT-Thread create semaphore successful\r\n");
	}
	else
	{
		rt_kprintf("RT-Thread create semaphore failed\r\n");
	}

	//创建消息队列
	msgqueue = rt_mq_create("msgqueue",50,10,RT_IPC_FLAG_FIFO);
	if(RT_NULL != msgqueue)
	{
		rt_kprintf("RT-Thread create msgqueue successful\r\n");
	}
	else
	{
		rt_kprintf("RT-Thread create msgqueue failed\r\n");
	}

	//创建线程
	thread1 = rt_thread_create("thread1",
									thread1_entry,
									NULL,
									512,
									1,
									20);
	if(RT_NULL != thread1)
	{
		rt_kprintf("RT-Thread create thread1 successful\r\n");
		rt_thread_startup(thread1);
	}
	else
	{
		rt_kprintf("RT-Thread create thread1 failed\r\n");
	}

	// rt_err_t res;
	// res = rt_thread_init(thread2,
	// 					"thread2",
	// 					thread2_entry,
	// 					NULL,&thread2_stack[0],
	// 					sizeof(thread2_stack),3,20);
	// if(res != RT_ERROR)
	// {
	// 	rt_kprintf("RT-Thread create thread2 successful\r\n");
	// 	rt_thread_startup(thread2);
	// }
	// else
	// {
	// 	rt_kprintf("RT-Thread create thread2 failed\r\n");
	// }
	thread2 = rt_thread_create("thread2",
									thread2_entry,
									NULL,
									512,
									2,
									20);
	if(RT_NULL != thread2)
	{
		rt_kprintf("RT-Thread create thread2 successful\r\n");
		rt_thread_startup(thread2);
	}
	else
	{
		rt_kprintf("RT-Thread create thread2 failed\r\n");
	}
	
	thread3 = rt_thread_create("thread3",
									thread3_entry,
									NULL,
									512,
									2,
									20);
	if(RT_NULL != thread3)
	{
		rt_kprintf("RT-Thread create thread3 successful\r\n");
		rt_thread_startup(thread3);
	}
	else
	{
		rt_kprintf("RT-Thread create thread3 failed\r\n");
	}
		
}
