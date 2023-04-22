#include "usercode.h"		/* usercode头文件 */
#include "threadpool.h"		/* 线程池头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

/* 线程句柄 */
osThreadId_t thread1;
const osThreadAttr_t thread1_attributes = {
  .name = "Order",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal3,
};

osThreadId_t thread2;
const osThreadAttr_t thread2_attributes = {
  .name = "Motioncontrol",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal1,
};

osThreadId_t thread3;
const osThreadAttr_t thread3_attributes = {
  .name = "JY901S",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t thread4;
const osThreadAttr_t thread4_attributes = {
  .name = "PS2",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal1,
};

osThreadId_t thread5;
const osThreadAttr_t thread5_attributes = {
  .name = "Huba511",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal,
};
osThreadId_t thread6;
const osThreadAttr_t thread6_attributes = {
  .name = "Rm3100",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityBelowNormal7,
};
osThreadId_t thread7;
const osThreadAttr_t thread7_attributes = {
  .name = "Jetson",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t thread8;
const osThreadAttr_t thread8_attributes = {
  .name = "OpenMV",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t thread9;
const osThreadAttr_t thread9_attributes = {
  .name = "Test",
  .stack_size = 512,
  .priority = (osPriority_t) osPriorityNormal6,
};

/* 信号量句柄*/
osSemaphoreId JY901_sem;
osSemaphoreDef(JY901_sem_def);

osSemaphoreId Jetson_sem;
osSemaphoreDef(Jetson_sem_def);

osSemaphoreId OpenMV_sem;
osSemaphoreDef(OpenMV_sem_def);

osSemaphoreId Order_sem;
osSemaphoreDef(Order_sem_def);

/* 互斥量句柄 */
osMutexId ps2_mutex;
osMutexDef(ps2_mutex_def);

/*消息队列句柄*/
osMessageQId msgqueue;
osMessageQDef(msgqueue_def,10,uint32_t);

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	//创建信号量
	osSemaphoreCreate(osSemaphore(JY901_sem_def),0);
	osSemaphoreCreate(osSemaphore(Jetson_sem_def),0);
	osSemaphoreCreate(osSemaphore(OpenMV_sem_def),0);
	osSemaphoreCreate(osSemaphore(Order_sem_def),0);

	//创建互斥量
	osMutexCreate(osMutex(ps2_mutex_def));

	//创建消息队列
	osMessageCreate(osMessageQ(msgqueue_def),msgqueue);

	//创建线程
	thread1 = osThreadNew(Order, NULL, &thread1_attributes);
  if(thread1 != NULL) printf("FreeRTOS create thread1 successful\r\n");

	thread2 = osThreadNew(Motioncontrol, NULL, &thread2_attributes);
  if(thread2 != NULL) printf("FreeRTOS create thread2 successful\r\n");

	thread3 = osThreadNew(JY901S_thread, NULL, &thread3_attributes);
  if(thread3 != NULL) printf("FreeRTOS create thread3 successful\r\n");

	thread4 = osThreadNew(PS2_thread, NULL, &thread4_attributes);
  if(thread4 != NULL) printf("FreeRTOS create thread4 successful\r\n");

	thread5 = osThreadNew(Huba511_thread, NULL, &thread5_attributes);
  if(thread5 != NULL) printf("FreeRTOS create thread5 successful\r\n");

	thread6 = osThreadNew(Rm3100_thread, NULL, &thread6_attributes);
  if(thread6 != NULL) printf("FreeRTOS create thread6 successful\r\n");

	thread7 = osThreadNew(Jetson_thread, NULL, &thread7_attributes);
  if(thread7 != NULL) printf("FreeRTOS create thread7 successful\r\n");

	thread8 = osThreadNew(OpenMV_thread, NULL, &thread8_attributes);
  if(thread8 != NULL) printf("FreeRTOS create thread8 successful\r\n");

	thread9 = osThreadNew(Test_thread, NULL, &thread9_attributes);
  if(thread9 != NULL) printf("FreeRTOS create thread9 successful\r\n");

	printf("Thread Start!\r\n");
	osKernelStart();
	
}
