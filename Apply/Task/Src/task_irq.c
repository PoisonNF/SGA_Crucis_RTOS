#include "task_conf.h"
#include "usercode.h"
#include "bsp_io.h"

/**
 * @brief ����1�жϺ���
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
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* ����ӣ��������޸� */
	
	Task_EXTI9_5_IRQHandler();
}

__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* ����ӣ��������޸� */
	
	Task_EXTI15_10_IRQHandler();
}

/**
 * @brief ����1�жϺ���
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{

}

/**
 * @brief ����1�жϺ���
 * @param null
 * @retval Null
*/

void USART1_IRQHandler(void)
{
	/* ʾ�� */
//	Drv_Uart_IRQHandler(&tPCUart);		/* ���貿�� */	
	//Task_USART1_IRQHandler();
	Drv_Uart_IRQHandler(&Uart1);
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rt_interrupt_enter();
	// if(huart->Instance == USART1)
	// {
	// 	if(Uart1.tRxInfo.ucpRxBuffer[0] == '\n')
  	// 	{
	// 		Uart1.tRxInfo.ucpRxCache[Uart1.tRxInfo.usRxCnt] = '\0';
	// 		Uart1.tRxInfo.usRxCnt = 0;
	// 		rt_sem_release(binary_semO);	//�ͷ�Order�ź���
  	// 	}
  	// 	else
  	// 	{
	// 		if(Uart1.tRxInfo.usRxCnt <128)
	// 		{
	// 		Uart1.tRxInfo.ucpRxCache[Uart1.tRxInfo.usRxCnt] = Uart1.tRxInfo.ucpRxBuffer[0];
	// 		Uart1.tRxInfo.usRxCnt += 1;
	// 		}
  	// 	}
  	// 	while(HAL_UART_Receive_IT(&Uart1.tUARTHandle, Uart1.tRxInfo.ucpRxBuffer, 1) != HAL_OK); 	
	// }
	rt_interrupt_leave();
}

/**
 * @brief ����2�жϺ���
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}

void USART2_IRQHandler(void)
{
		/* ʾ�� */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* ���貿�� */
	rt_interrupt_enter();
//	Task_USART2_IRQHandler();
	//Drv_Uart_DMA_Handler(&demoUart2);
	Drv_Uart_DMA_Handler(&JY901S.tUART);
	//rt_mq_send(msgqueue,"�����ж�",sizeof("�����ж�"));	//������Ϣ����
	rt_sem_release(binary_sem);	//�ͷ��ź���
	rt_interrupt_leave();
}

/**
 * @brief ����3�жϺ���
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{
	rt_interrupt_enter();
	//Drv_Uart_IRQHandler(&Uart3);
	Drv_Uart_DMA_Handler(&Uart3);
	rt_sem_release(binary_semJ);	//�ͷ�Jetson�ź���
	rt_interrupt_leave();
}

/**
 * @brief ����4�жϺ���
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	Drv_Uart_DMA_Handler(&Uart4);
}

/**
 * @brief ����5�жϺ���
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{

}

/**
 * @brief ��ʱ��2�жϺ���
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��3�жϺ���
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��4�жϺ���
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��5�жϺ���
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��6�жϺ���
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��7�жϺ���
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* ʾ�� */
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
* @brief ϵͳ�δ��ж�
* @param Null
* @retval Null
*/
void SysTick_Handler(void)
{
   Drv_HAL_IncTick();
}

/**
* @brief HAL��ϵͳ�����ж�
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

