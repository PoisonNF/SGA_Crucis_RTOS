#include "usercode.h"		/* usercode头文件 */
#include "threadpool.h"		/* 线程池头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

int PS2_LX=128,PS2_LY=127,PS2_RX=128,PS2_RY=127,PS2_KEY=0; 	//PS2摇杆数据接收变量

/* 主机控制线程 */
void Order(void* paramenter)
{
	char buf[20];
	while(1)
	{	
		if(rt_sem_take(Order_sem,RT_WAITING_FOREVER) == RT_EOK)
		{	
			if(Uart1.tRxInfo.ucDMARxCplt)
			{
				memcpy(buf,Uart1.tRxInfo.ucpDMARxCache,Uart1.tRxInfo.usDMARxLength);
				printf("buf = %s",buf);
				if(strcmp(buf,"Shutdown\r\n")==0)
				{
					Drv_Uart_Transmit(&Uart3,"ok\r\n",sizeof("ok\r\n"));
					printf("shutting down!\r\n");
					Drv_Delay_Ms(1000);
					Drv_Uart_Transmit(&Uart3,"ok\r\n",sizeof("ok\r\n"));
					printf("shutting down!!\r\n");
				}
				else
				{
					printf("Invalid instruction\r\n");
				}
			}
			Uart1.tRxInfo.ucDMARxCplt = 0;
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
			printf("M PS2_LY:%d  PS2_RX:%d  PS2_KEY:%d\r\n",PS2_LY,PS2_RX,PS2_KEY);

			//Task_Motor_AllSpeedSet(1550);
			//Task_Motioncontrol(200,128,0);
			if(Dev_PS2_RedLight(&PS2) == 0) //读取手柄模式，红灯模式开始运动控制
			{
			 	Task_Motioncontrol(PS2_LY,PS2_RX,PS2_KEY);//运动控制函数
			}
			Drv_Delay_Ms(1000);//执行时间
            //Task_Motor_AllSpeedSet(1500);
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
			/* 打印加速度 */
            if(JY901S.tConfig.usType & JY901_OUTPUT_ACCEL)	    printf("J 1 Acc %.3f %.3f %.3f\r\n",JY901S.stcAcc.ConAccX,JY901S.stcAcc.ConAccY,JY901S.stcAcc.ConAccZ);
            /* 打印角速度 */
            if(JY901S.tConfig.usType & JY901_OUTPUT_GYRO)		printf("J 2 Gyro %.3f %.3f %.3f\r\n",JY901S.stcGyro.ConGyroX,JY901S.stcGyro.ConGyroY,JY901S.stcGyro.ConGyroZ);
            /* 打印欧拉角 */
            if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    printf("J 3 Angle %.3f %.3f %.3f\r\n",JY901S.stcAngle.ConRoll,JY901S.stcAngle.ConPitch,JY901S.stcAngle.ConYaw);
            /* 打印磁场 */
            if(JY901S.tConfig.usType & JY901_OUTPUT_MAG)		printf("J 4 Mag %.3f %.3f %.3f\r\n",JY901S.stcMag.ConMagX,JY901S.stcMag.ConMagY,JY901S.stcMag.ConMagZ);
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
			PS2_KEY = Dev_PS2_DataKey(&PS2);	
			//PS2_LX=PS2_AnologData(PSS_LX);
			PS2_LY =  Dev_PS2_AnologData(PSS_LY);
			PS2_RX =  Dev_PS2_AnologData(PSS_RX);
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
			printf("%s\r\n",buf);
            Drv_GPIO_Write(&GPIO[0],GPIO_PIN_RESET);
            Drv_Delay_Ms(500);
            Drv_GPIO_Write(&GPIO[0],GPIO_PIN_SET);
			//OCD_OLED_ShowNum(&OLED,0,0,i,2,16);
			//i++;
		}
		rt_thread_yield();
	}
}

/* Rm3100接收线程*/
void Rm3100_thread(void* paramenter)
{
	int i;
	while(1)
	{
		/*需要安装所有的RM3100才解开注释*/

		for(i = 0;i < 4;i++)
			OCD_RM3100_GetData(&RM3100[i]);

        printf("R 1 %d %d %d\r\n",RM3100[0].tMagData.MAG_X,RM3100[0].tMagData.MAG_Y,RM3100[0].tMagData.MAG_Z);
		printf("R 2 %d %d %d\r\n",RM3100[1].tMagData.MAG_X,RM3100[1].tMagData.MAG_Y,RM3100[1].tMagData.MAG_Z);
		printf("R 3 %d %d %d\r\n",RM3100[2].tMagData.MAG_X,RM3100[2].tMagData.MAG_Y,RM3100[2].tMagData.MAG_Z);
		printf("R 4 %d %d %d\r\n",RM3100[3].tMagData.MAG_X,RM3100[3].tMagData.MAG_Y,RM3100[3].tMagData.MAG_Z);

		for(i = 0;i < 4;i++)
			OCD_RM3100_ModeConfig(&RM3100[i]);

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
			if(Uart3.tRxInfo.ucDMARxCplt)
			{
				Drv_Uart_Transmit(&Uart1,Uart3.tRxInfo.ucpDMARxCache,Uart3.tRxInfo.usDMARxLength);
				memset(Uart3.tRxInfo.ucpDMARxCache,0,Uart3.tRxInfo.usDMARxLength);
			}
		 	Uart3.tRxInfo.ucDMARxCplt = 0;	//标志位清0
		}	
		rt_thread_yield();
	}
}

extern uint8_t rData[10];
/* OpenMV接收线程 */
void OpenMV_thread(void* paramenter)
{
	while(1)
	{
		//获取OpenMV信号量
		if(rt_sem_take(OpenMV_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			printf("OPENMV %x %x %x %x\r\n",rData[2],rData[3],rData[4],rData[5]);
		}
		rt_thread_yield();
	}
}

/* 测试线程*/
void Test_thread(void* paramenter)
{
	while(1)
	{
		// Drv_GPIO_Write(&GPIO[1],GPIO_PIN_RESET);
		// Drv_Delay_Ms(1000);
		// Drv_GPIO_Write(&GPIO[1],GPIO_PIN_SET);
		// Drv_Delay_Ms(1000);
		// printf("test\r\n");
		// Drv_Delay_Ms(1000);
		// rt_thread_yield();
        
        Task_AllSteer_0Angle();
		Drv_Delay_Ms(1000);
        
        Task_AllSteer_90Angle();
		Drv_Delay_Ms(1000);
        
        
	}
}


