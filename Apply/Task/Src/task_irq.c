#include "task_conf.h"
#include "usercode.h"
#include "config.h"

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
__weak void Task_EXTI9_5_IRQHandler(void)
{
	
}

/**
 * @brief This function handles EXTI line[9:5] interrupts.
*/
void EXTI9_5_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* 必须加，参数需修改 */
	
	Task_EXTI9_5_IRQHandler();
}

__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* 必须加，参数需修改 */
	
	Task_EXTI15_10_IRQHandler();
}

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{

}

/**
 * @brief 串口1中断函数
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* 示例 */
//	Drv_Uart_IRQHandler(&tPCUart);		/* 必需部分 */	
	//Task_USART1_IRQHandler();
	//vPortEnterCritical();
	Drv_Uart_DMA_RxHandler(&Uart1);
	osSemaphoreRelease(Order_sem);
	//vPortExitCritical();
}

/**
 * @brief 串口2中断函数
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}

void USART2_IRQHandler(void)
{
		/* 示例 */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* 必需部分 */

//	Task_USART2_IRQHandler();
	//Drv_Uart_DMA_Handler(&demoUart2);

	//vPortEnterCritical();
	Drv_Uart_DMA_RxHandler(&JY901S.tUART);
	//osMessageQueuePut(msgqueue,"interrupt",0,portMAX_DELAY);
	osSemaphoreRelease(JY901_sem);	//释放信号量
	//vPortExitCritical();
}

/**
 * @brief 串口3中断函数
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	vPortEnterCritical();
	//Drv_Uart_IRQHandler(&Uart3);
	Drv_Uart_DMA_RxHandler(&Uart3);
	osSemaphoreRelease(Jetson_sem);	//释放Jetson信号量
	vPortExitCritical();
}

/**
 * @brief 串口4中断函数
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	vPortEnterCritical();
	Drv_Uart_DMA_RxHandler(&Uart4);
	vPortExitCritical();
}

/**
 * @brief 串口5中断函数
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	vPortEnterCritical();
	Drv_Uart_IRQHandler(&OpenMV);
	vPortExitCritical();
}

uint8_t rData[10];
uint8_t rflag;
/**
 * @brief 串口接收完成服务函数
 * @param null
 * @retval Null
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//判断是否是串口5
	if(huart->Instance == UART5)
	{
		uint8_t com_data; //临时变量
		static int rDataFlag = 0;  //buffer下标位置
		static uint8_t RXstate = 0;
		//uint16_t cx,cy;

		com_data = OpenMV.tRxInfo.ucpRxBuffer[0];

		if(RXstate == 0 && com_data == 0x2C)  //0x2C帧头
		{
			RXstate = 1;
			rData[rDataFlag++] = com_data;
		}
		else if(RXstate == 1 && com_data == 0x12) //0x12帧头
		{
			RXstate = 2;
			rData[rDataFlag++] = com_data;
		}
		else if(RXstate == 2) //开始传数据
		{
			rData[rDataFlag++] = com_data;
			if(rDataFlag >= 7 || com_data == 0x5B)
			{
				RXstate = 3;

				//cx = (rData[rDataFlag-4]<<8 + rData[rDataFlag-5]);
				//cy = (rData[rDataFlag-2]<<8 + rData[rDataFlag-3]);
			}
		}
		else if(RXstate == 3 )
		{
			if(rData[rDataFlag-1] == 0x5B)
			{
				osSemaphoreRelease(OpenMV_sem);	//释放OpenMV信号量
				rDataFlag = 0;
				RXstate = 0;
				//cx = hextodec(rData[3])*256 + hextodec(rData[2]);
				//cy = hextodec(rData[5])*256 + hextodec(rData[4]);

				//printf("OPENMV %x %x %x %x\r\n",rData[2],rData[3],rData[4],rData[5]);
				//printf("%d %d\r\n",cx,cy);
				//memset(rData,0,sizeof(rData));
			}
		}
		else
		{
			rDataFlag = 0;
			RXstate = 0;
			for (int i = 0; i < 7; i++)
			{
				rData[i] = 0x00;
			}		
		}
		while(HAL_UART_Receive_IT(&OpenMV.tUARTHandle, OpenMV.tRxInfo.ucpRxBuffer, 1) != HAL_OK); 
	}
}
/**
 * @brief 定时器2中断函数
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器3中断函数
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器4中断函数
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器5中断函数
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器6中断函数
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief 定时器7中断函数
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* 示例 */
//    Drv_Timer_IRQHandler(&demoTIM);
}

