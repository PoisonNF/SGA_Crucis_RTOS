#include "task_conf.h"
#include "usercode.h"
#include "bsp_io.h"

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
	rt_interrupt_enter();
	Drv_Uart_DMA_Handler(&Uart1);
	rt_sem_release(Order_sem);
	rt_interrupt_leave();
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
	rt_interrupt_enter();
//	Task_USART2_IRQHandler();
	//Drv_Uart_DMA_Handler(&demoUart2);
	Drv_Uart_DMA_Handler(&JY901S.tUART);
	//rt_mq_send(msgqueue,"进入中断",sizeof("进入中断"));	//发送消息队列
	rt_sem_release(JY901_sem);	//释放信号量
	rt_interrupt_leave();
}

/**
 * @brief 串口3中断函数
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	rt_interrupt_enter();
	//Drv_Uart_IRQHandler(&Uart3);
	Drv_Uart_DMA_Handler(&Uart3);
	rt_sem_release(Jetson_sem);	//释放Jetson信号量
	rt_interrupt_leave();
}

/**
 * @brief 串口4中断函数
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	rt_interrupt_enter();
	Drv_Uart_DMA_Handler(&Uart4);
	rt_interrupt_leave();
}

/**
 * @brief 串口5中断函数
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	rt_interrupt_enter();
	Drv_Uart_IRQHandler(&OpenMV);
	rt_interrupt_leave();
}

uint8_t rData[100];
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
		if(OpenMV.tRxInfo.ucpRxBuffer[0] == '\n') //当检测到换行
		{
			rData[rflag] = '\0'; //加上字符串结尾
			rflag = 0;
			printf("%s",rData);
			rt_sem_release(OpenMV_sem);	//释放OpenMV信号量
		}
		else //没检测到换行
		{
			if(rflag < OpenMV.tRxInfo.usRxMAXLenth) //标志数小于最大可装载数
			{
				//将RxBuffer中的数据放入数组
				rData[rflag] = OpenMV.tRxInfo.ucpRxBuffer[0];
				rflag += 1;
			}
		}
		HAL_UART_Receive_IT(huart,OpenMV.tRxInfo.ucpRxBuffer,1); //再次开启接收
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

#ifndef RTT_ENABLE
/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
 /* USER CODE BEGIN PendSV_IRQn 0 */

 /* USER CODE END PendSV_IRQn 0 */
 /* USER CODE BEGIN PendSV_IRQn 1 */

 /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief 系统滴答中断
* @param Null
* @retval Null
*/
void SysTick_Handler(void)
{
   Drv_HAL_IncTick();
}

/**
* @brief HAL库系统报错中断
* @param Null
* @retval Null
*/
void HardFault_Handler(void)
{
	while(1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

#endif

