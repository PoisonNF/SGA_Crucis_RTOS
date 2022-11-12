#include "task_conf.h"

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
	Drv_Uart_DMA_Handler(&Uart1);

}
/**
 * @brief ����2�жϺ���
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}
extern rt_sem_t binary_sem;
extern rt_mq_t msgqueue;
void USART2_IRQHandler(void)
{
		/* ʾ�� */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* ���貿�� */
	rt_interrupt_enter();
//	Task_USART2_IRQHandler();
	//Drv_Uart_DMA_Handler(&demoUart2);
	Drv_Uart_DMA_Handler(&JY901S.tUART);
	rt_mq_send(msgqueue,"�����ж�",sizeof("�����ж�"));	//������Ϣ����
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

}

/**
 * @brief ����4�жϺ���
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{

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

