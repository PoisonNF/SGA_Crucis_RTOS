#include "usercode.h"
#include "drv_hal_conf.h"   //SGA库头文件配置
#include "task_conf.h"      //task层头文件配置
#include "ocd_conf.h"       //OCD层头文件配置
#include "bsp_io.h"			//I/O头文件配置

int PS2_LX=128,PS2_LY=127,PS2_RX=128,PS2_RY=127,PS2_KEY=0; 	//PS2摇杆数据接收变量

/*运动控制线程*/
void Motioncontrol(void* paramenter)
{
	while(1)
	{
		if(rt_mutex_take(ps2_mutex,RT_WAITING_FOREVER) == RT_EOK)
		{
			printf("PS2_LY:%d  ",PS2_LY);
			printf("PS2_RX:%d  ",PS2_RX);
			printf("PS2_KEY:%d\r\n",PS2_KEY);
			Drv_Delay_Ms(1000);
			rt_mutex_release(ps2_mutex);//完成读取,释放互斥量
		}
	}
}


/*JY901S数据读取线程*/
void JY901S_thread(void* paramenter)
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

/* PS2接收线程*/
void PS2_thread(void* paramenter)
{
	while(1)
	{	
		//尝试获取互斥量
		if(rt_mutex_take(ps2_mutex,RT_WAITING_FOREVER) == RT_EOK)
		{
			PS2_KEY=PS2_DataKey(&PS2);	
			//PS2_LX=PS2_AnologData(PSS_LX);
			PS2_LY=PS2_AnologData(PSS_LY);
			PS2_RX=PS2_AnologData(PSS_RX);
			//PS2_RY=PS2_AnologData(PSS_RY);
			//printf("PS2_LX:%d  ",PS2_LX);
			//printf("PS2_LY:%d  ",PS2_LY);
			//printf("PS2_RX:%d  ",PS2_RX);
			//printf("PS2_RY:%d  ",PS2_RY);
			//printf("PS2_KEY:%d\r\n",PS2_KEY);
			
			rt_mutex_release(ps2_mutex);//完成修改,释放互斥量
		}
		rt_thread_yield();
	}

}

/* Huba511接收线程*/
void Huba511_thread(void* paramenter)
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

/* Rm3100接收线程*/
void Rm3100_thread(void* paramenter)
{

}

/* 测试线程*/
void Test_thread(void* paramenter)
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