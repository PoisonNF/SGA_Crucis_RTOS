#include "usercode.h"
#include "drv_hal_conf.h"   //SGA��ͷ�ļ�����
#include "task_conf.h"      //task��ͷ�ļ�����
#include "ocd_conf.h"       //OCD��ͷ�ļ�����
#include "config.h"			//I/Oͷ�ļ�����

int PS2_LX=128,PS2_LY=127,PS2_RX=128,PS2_RY=127,PS2_KEY=0; 	//PS2ҡ�����ݽ��ձ���

/* ���������߳� */
void Order(void* paramenter)
{
	char buf[20];
	while(1)
	{	
		if(rt_sem_take(Order_sem,RT_WAITING_FOREVER) == RT_EOK)
		{	
			if(Uart1.tUartDMA.ucDMARxCplt)
			{
				memcpy(buf,Uart1.tRxInfo.ucpRxCache,Uart1.tRxInfo.usRxLenth);
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
			Uart1.tUartDMA.ucDMARxCplt = 0;
		}
		rt_thread_yield();
	}
}

/*�˶������߳�*/
void Motioncontrol(void* paramenter)
{

	while(1)
	{
		if(rt_mutex_take(ps2_mutex,RT_WAITING_FOREVER) == RT_EOK)
		{
			printf("M PS2_LY:%d  PS2_RX:%d  PS2_KEY:%d\r\n",PS2_LY,PS2_RX,PS2_KEY);

			if(OCD_PS2_RedLight(&PS2) == 0) //��ȡ�ֱ�ģʽ�����ģʽ��ʼ�˶�����
			{
				Task_Motioncontrol(PS2_LY,PS2_RX,PS2_KEY);//�˶����ƺ���
			}
			Drv_Delay_Ms(1000);//ִ��ʱ��
			rt_mutex_release(ps2_mutex);//��ɶ�ȡ,�ͷŻ�����
		}
	}
}


/*JY901S���ݶ�ȡ�߳�*/
void JY901S_thread(void* paramenter)
{
	while(1)
	{
		if(rt_sem_take(JY901_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			OCD_JY901_DataProcess(&JY901S);
			OCD_JY901_DataConversion(&JY901S);
			/* ��ӡ���ٶ� */
            if(JY901S.tConfig.usType & JY901_OUTPUT_ACCEL)	    printf("J 1 Acc %.3f %.3f %.3f\r\n",JY901S.stcAcc.ConAccX,JY901S.stcAcc.ConAccY,JY901S.stcAcc.ConAccZ);
            /* ��ӡ���ٶ� */
            if(JY901S.tConfig.usType & JY901_OUTPUT_GYRO)		printf("J 2 Gyro %.3f %.3f %.3f\r\n",JY901S.stcGyro.ConGyroX,JY901S.stcGyro.ConGyroY,JY901S.stcGyro.ConGyroZ);
            /* ��ӡŷ���� */
            if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    printf("J 3 Angle %.3f %.3f %.3f\r\n",JY901S.stcAngle.ConRoll,JY901S.stcAngle.ConPitch,JY901S.stcAngle.ConYaw);
            /* ��ӡ�ų� */
            if(JY901S.tConfig.usType & JY901_OUTPUT_MAG)		printf("J 4 Mag %.3f %.3f %.3f\r\n",JY901S.stcMag.ConMagX,JY901S.stcMag.ConMagY,JY901S.stcMag.ConMagZ);
		}
		rt_thread_yield();
	}
}

/* PS2�����߳�*/
void PS2_thread(void* paramenter)
{
	while(1)
	{	
		//���Ի�ȡ������
		if(rt_mutex_take(ps2_mutex,RT_WAITING_FOREVER) == RT_EOK)
		{
			PS2_KEY=OCD_PS2_DataKey(&PS2);	
			//PS2_LX=PS2_AnologData(PSS_LX);
			PS2_LY=OCD_PS2_AnologData(PSS_LY);
			PS2_RX=OCD_PS2_AnologData(PSS_RX);
			//PS2_RY=PS2_AnologData(PSS_RY);
		
			rt_mutex_release(ps2_mutex);//����޸�,�ͷŻ�����
		}
		rt_thread_yield();
	}

}

/* Huba511�����߳�*/
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

/* Rm3100�����߳�*/
void Rm3100_thread(void* paramenter)
{
	MagData_t buffer1,buffer2,buffer3,buffer4;
	while(1)
	{
		/*��Ҫ��װ���е�RM3100�Ž⿪ע��*/
		OCD_ThreeD3100_Magic_GetData(&SPI[0],&buffer1);
		OCD_ThreeD3100_Magic_GetData(&SPI[1],&buffer2);
		OCD_ThreeD3100_Magic_GetData(&SPI[2],&buffer3);
		OCD_ThreeD3100_Magic_GetData_Soft(&SPI_soft[0],&buffer4);

        printf("R 1 %d %d %d\r\n",buffer1.MAG_X,buffer1.MAG_Y,buffer1.MAG_Z);
		printf("R 2 %d %d %d\r\n",buffer2.MAG_X,buffer2.MAG_Y,buffer2.MAG_Z);
		printf("R 3 %d %d %d\r\n",buffer3.MAG_X,buffer3.MAG_Y,buffer3.MAG_Z);
		printf("R 4 %d %d %d\r\n",buffer4.MAG_X,buffer4.MAG_Y,buffer4.MAG_Z);

		OCD_ThreeD3100_Magic_Init(&SPI[0]);
		OCD_ThreeD3100_Magic_Init(&SPI[1]);
		OCD_ThreeD3100_Magic_Init(&SPI[2]);
		OCD_ThreeD3100_Magic_Init_Soft(&SPI_soft[0]);

		Drv_Delay_Ms(2000);
	}
}

/* Jetson�����߳� */
void Jetson_thread(void* paramenter)
{
	while(1)
	{
		//��ȡjetson�ź���
		if(rt_sem_take(Jetson_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			//���������ɱ�־λΪ1
			if(Uart3.tUartDMA.ucDMARxCplt)
			{
				Drv_Uart_Transmit(&Uart1,Uart3.tRxInfo.ucpRxCache,Uart3.tRxInfo.usRxLenth);
				memset(Uart3.tRxInfo.ucpRxCache,0,Uart3.tRxInfo.usRxLenth);
			}
		 	Uart3.tUartDMA.ucDMARxCplt = 0;	//��־λ��0
		}	
		rt_thread_yield();
	}
}

extern uint8_t rData[10];
/* OpenMV�����߳� */
void OpenMV_thread(void* paramenter)
{
	while(1)
	{
		//��ȡOpenMV�ź���
		if(rt_sem_take(OpenMV_sem,RT_WAITING_FOREVER) == RT_EOK)
		{
			printf("OPENMV %x %x %x %x\r\n",rData[2],rData[3],rData[4],rData[5]);
		}
		rt_thread_yield();
	}
}

/* �����߳�*/
void Test_thread(void* paramenter)
{
	while(1)
	{
		// Drv_GPIO_Write(&GPIO[1],GPIO_PIN_RESET);
		// Drv_Delay_Ms(1000);
		// Drv_GPIO_Write(&GPIO[1],GPIO_PIN_SET);
		// Drv_Delay_Ms(1000);
		printf("test\r\n");
		Drv_Delay_Ms(1000);
		rt_thread_yield();
	}
}


