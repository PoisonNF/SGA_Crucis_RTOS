#include "usercode.h"
#include "drv_hal_conf.h"   //SGA库头文件配置
#include "task_conf.h"      //task层头文件配置
#include "ocd_conf.h"       //OCD层头文件配置
#include "bsp_io.h"			//I/O头文件配置


/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	/* 电机测试代码 */
	//Task_Motor_Init();
	//Task_Steer_Init();

	/* 水平定向移动 测试代码*/
    // float *p;
	// p = Task_Horizontal_Heading_Calculation(500,30);

    // float num1 = *p,num2 = *(p+1);

	// OCD_OLED_ShowFNum(&tOLED,0,0,num1,16);
    // OCD_OLED_ShowFNum(&tOLED,0,2,num2,16);
    
	// printf("%f\r\n",*p+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+1)+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+2)+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+3)+STOP_PWM_VALUE);
	
	/* PID 测试代码*/
	// PID pid;
	// float pidvalue[3] = {0.2,1,0};
	// pid.pre_value = 1400;

    // printf("pid test\r\n");
    // PID_init(&pid,pidvalue);

    // while(pid.pre_value != 1500)
    // {
    //     PID_calc(&pid,pid.pre_value,1500);
	// 	   Task_Motor_SpeedSet(1,pid.ctrl_out);
    //     OCD_OLED_ShowFNum(&tOLED,0,0,pid.ctrl_out,16);
    //     printf("%f\r\n",pid.ctrl_out);
	// 	   Drv_Delay_Ms(100);
	// 	//if(pid.pre_value == 1500)	return;
    // }

	/* HUBA511测试程序 */
	// OCD_OLED_ShowString(&tOLED,0,0,"test",16);
	// float adc_value = 0.f;

	while(1)
	{
        // adc_value = Drv_ADC_PollGetValue(&demoADC[0]);
        // OCD_OLED_ShowFNum(&tOLED,0,2,adc_value,16);
        
		/* 串口DMA测试程序 */
		
		// if(demoUart2.tUartDMA.DMARxCplt)
		// {
		// 	//HAL_UART_Transmit(&demoUart1.tUARTHandle,demoUart2.tRxInfo.ucpRxCache, demoUart2.tRxInfo.usRxLenth, 100);
		// 	for (int i = 0; i < demoUart2.tRxInfo.usRxLenth; i+=11)
		// 	{
		// 		if(demoUart2.tRxInfo.ucpRxCache[i] == 0x55) //数据头为0x55
		// 		{
		// 			switch (demoUart2.tRxInfo.ucpRxCache[i+1])
		// 			{
		// 			case 0x51:	memcpy(&stcAcc,&demoUart2.tRxInfo.ucpRxCache[i+2],8);
		// 						break;
		// 			case 0x52:	memcpy(&stcGyro,&demoUart2.tRxInfo.ucpRxCache[i+2],8);
		// 						break;
		// 			case 0x53:	memcpy(&stcAngle,&demoUart2.tRxInfo.ucpRxCache[i+2],8);
		// 						break;
		// 			default:	
		// 				break;
		// 			}
		// 		}

		// 	}

		// 	printf("Acc:%.3f %.3f %.3f\r\n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
		// 	demoUart2.tUartDMA.DMARxCplt = 0;
		// }
		if(JY901S.tUART.tUartDMA.DMARxCplt)
		{
			//HAL_UART_Transmit(&demoUart1.tUARTHandle,JY901S.tUART.tRxInfo.ucpRxCache, JY901S.tUART.tRxInfo.usRxLenth, 100);
			for (int i = 0; i < JY901S.tUART.tRxInfo.usRxLenth; i++)
			{
				if(JY901S.tUART.tRxInfo.ucpRxCache[i] == JY901_HEAD) //数据头为0x55
				{
					uint8_t ucSum = 0;
					for(int j = 0;j<10;j++)
					{
						ucSum += JY901S.tUART.tRxInfo.ucpRxCache[i+j];

					}
					if(ucSum == JY901S.tUART.tRxInfo.ucpRxCache[i+10])
					{
						switch (JY901S.tUART.tRxInfo.ucpRxCache[i+1])
						{
						case 0x51:	memcpy(&JY901S.stcAcc,&JY901S.tUART.tRxInfo.ucpRxCache[i+2],8);
									break;
						case 0x52:	memcpy(&JY901S.stcGyro,&JY901S.tUART.tRxInfo.ucpRxCache[i+2],8);
									break;
						case 0x53:	memcpy(&JY901S.stcAngle,&JY901S.tUART.tRxInfo.ucpRxCache[i+2],8);
									break;
						default:	
							break;
						}
					}
					else continue;
				}

			}
			printf("Acc:%.3f %.3f %.3f\r\n",(float)JY901S.stcAcc.a[0]/32768*16,(float)JY901S.stcAcc.a[1]/32768*16,(float)JY901S.stcAcc.a[2]/32768*16);
			printf("Gyro:%.3f %.3f %.3f\r\n",(float)JY901S.stcGyro.w[0]/32768*2000,(float)JY901S.stcGyro.w[1]/32768*2000,(float)JY901S.stcGyro.w[2]/32768*2000);
			printf("Angle:%.3f %.3f %.3f\r\n",(float)JY901S.stcAngle.Angle[0]/32768*180,(float)JY901S.stcAngle.Angle[1]/32768*180,(float)JY901S.stcAngle.Angle[2]/32768*180);
			JY901S.tUART.tUartDMA.DMARxCplt = 0;
		}
		if(demoUart1.tUartDMA.DMARxCplt)
		{
			printf("%s\r",demoUart1.tRxInfo.ucpRxCache);
			demoUart1.tUartDMA.DMARxCplt = 0;
		}
        
	}
}
