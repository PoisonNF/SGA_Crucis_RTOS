#include "usercode.h"
#include "drv_hal_conf.h"   //SGA库头文件配置
#include "task_conf.h"      //task层头文件配置
#include "ocd_conf.h"       //OCD层头文件配置
#include "bsp_io.h"			//I/O头文件配置

int PS2_LX=128,PS2_LY=127,PS2_RX=128,PS2_RY=127,PS2_KEY=0; 	//PS2摇杆数据接收变量

/* 主机控制线程 */
void Order(void* paramenter)
{
	char buf[20];
	while(1)
	{	
		if(rt_sem_take(Order_sem,RT_WAITING_FOREVER) == RT_EOK)
		{	
			if(Uart1.tUartDMA.DMARxCplt)
			{
				memcpy(buf,Uart1.tRxInfo.ucpRxCache,Uart1.tRxInfo.usRxLenth);
				printf("buf = %s",buf);
				if(strcmp(buf,"Shutdown\r\n")==0)
				{
					Drv_Uart_Transmit(&Uart3,"ok",sizeof("ok"));
					printf("shutting down!\r\n");
					Drv_Delay_Ms(1000);
					Drv_Uart_Transmit(&Uart3,"ok",sizeof("ok"));
					printf("shutting down!!\r\n");
				}
				else
				{
					printf("Invalid instruction\r\n");
				}
			}
			Uart1.tUartDMA.DMARxCplt = 0;
		}
		rt_thread_yield();
	}
}

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

			if(PS2_RedLight(&PS2) == 0) //读取手柄模式，红灯模式开始运动控制
			{
				Task_Motioncontrol(PS2_LY,PS2_RX,PS2_KEY);//运动控制函数
			}
			Drv_Delay_Ms(1000);//执行时间
			rt_mutex_release(ps2_mutex);//完成读取,释放互斥量
		}
	}
}


/*JY901S数据读取线程*/
void JY901S_thread(void* paramenter)
{
	while(1)
	{
		if(rt_sem_take(JY901_sem,RT_WAITING_FOREVER) == RT_EOK)
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
		
			rt_mutex_release(ps2_mutex);//完成修改,释放互斥量
		}
		rt_thread_yield();
	}

}

/* Huba511接收线程*/
void Huba511_thread(void* paramenter)
{
	char buf[50];
	//int i = 0;
	while(1)
	{
		if(rt_mq_recv(msgqueue,buf,sizeof(buf),RT_WAITING_FOREVER) == RT_EOK)
		{
			rt_kprintf("%s\r\n",buf);
            Drv_GPIO_Write(&GPIO[1],GPIO_PIN_RESET);
            Drv_Delay_Ms(1000);
            Drv_GPIO_Write(&GPIO[1],GPIO_PIN_SET);
			//OCD_OLED_ShowNum(&OLED,0,0,i,2,16);
			//i++;
		}
		rt_thread_yield();
	}
}

/* Rm3100接收线程*/
void Rm3100_thread(void* paramenter)
{
	//MagData_t buffer1,buffer2,buffer3,buffer4;
	while(1)
	{
		/*需要安装所有的RM3100才解开注释*/
		//OCD_ThreeD3100_magic_GetData(&buffer1,&SPI[0]);
		//OCD_ThreeD3100_magic_GetData(&buffer2,&SPI[1]);
		//OCD_ThreeD3100_magic_GetData_soft(&buffer3,&SPI_soft[1]);
		//OCD_ThreeD3100_magic_GetData_soft(&buffer4,&SPI_soft[0]);
		//printf("mag_x1=%d mag_y1=%d  mag_z1=%d \r\nmag_x2=%d mag_y2=%d  mag_z2=%d \r\nmag_x3=%d mag_y3=%d  mag_z3=%d \r\nmag_x4=%d mag_y4=%d  mag_z4=%d \r\n\r\n",buffer1.MAG_X,buffer1.MAG_Y,buffer1.MAG_Z,buffer2.MAG_X,buffer2.MAG_Y,buffer2.MAG_Z,buffer3.MAG_X,buffer3.MAG_Y,buffer3.MAG_Z,buffer4.MAG_X,buffer4.MAG_Y,buffer4.MAG_Z);

		//printf("mag_x3=%d mag_y3=%d  mag_z3=%d \r\n",buffer3.MAG_X,buffer3.MAG_Y,buffer3.MAG_Z);
		//printf("mag_x4=%d mag_y4=%d  mag_z4=%d \r\n",buffer4.MAG_X,buffer4.MAG_Y,buffer4.MAG_Z);
		//OCD_ThreeD3100_magic_init(&SPI[0]);
		//OCD_ThreeD3100_magic_init(&SPI[1]);
		//OCD_ThreeD3100_magic_init_soft(&SPI_soft[0]);
		//OCD_ThreeD3100_magic_init_soft(&SPI_soft[1]);

		Drv_Delay_Ms(2000);
	}
}

/* Jetson接收线程 */
void Jetson_thread(void* paramenter)
{
	while(1)
	{
		//获取jetson信号量
		if(rt_sem_take(Jetson_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			//如果接收完成标志位为1
			if(Uart3.tUartDMA.DMARxCplt)
			{
				Drv_Uart_Transmit(&Uart1,Uart3.tRxInfo.ucpRxCache,Uart3.tRxInfo.usRxLenth);
				memset(Uart3.tRxInfo.ucpRxCache,0,Uart3.tRxInfo.usRxLenth);
			}
		 	Uart3.tUartDMA.DMARxCplt = 0;	//标志位清0
		}	
		rt_thread_yield();
	}
}

extern uint8_t rData[100];
/* OpenMV接收线程 */
void OpenMV_thread(void* paramenter)
{
	while(1)
	{
		//获取OpenMV信号量
		if(rt_sem_take(OpenMV_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			//测试判断帧头代码
			if(rData[0] == 'a' && rData[1] == 'b')
			printf("OK!\r\n");
		}
		rt_thread_yield();
	}
}

/* 测试线程*/
void Test_thread(void* paramenter)
{
	while(1)
	{
		Drv_GPIO_Write(&GPIO[1],GPIO_PIN_RESET);
		Drv_Delay_Ms(1000);
		Drv_GPIO_Write(&GPIO[1],GPIO_PIN_SET);
		rt_thread_yield();
	}
}


