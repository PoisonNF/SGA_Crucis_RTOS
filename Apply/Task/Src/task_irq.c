#include "task_conf.h"
#include "usercode.h"
#include "config.h"

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
	rt_interrupt_enter();
	Drv_Uart_DMA_RxHandler(&Uart1);
	rt_sem_release(Order_sem);
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
	Drv_Uart_DMA_RxHandler(&JY901S.tUART);
	rt_mq_send(msgqueue,"interrupt",sizeof("interrupt"));	//������Ϣ����
	rt_sem_release(JY901_sem);	//�ͷ��ź���
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
	Drv_Uart_DMA_RxHandler(&Uart3);
	rt_sem_release(Jetson_sem);	//�ͷ�Jetson�ź���
	rt_interrupt_leave();
}

/**
 * @brief ����4�жϺ���
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{
	rt_interrupt_enter();
	Drv_Uart_DMA_RxHandler(&Uart4);
	rt_interrupt_leave();
}

/**
 * @brief ����5�жϺ���
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{
	rt_interrupt_enter();
	Drv_Uart_IRQHandler(&OpenMV);
	rt_interrupt_leave();
}

uint8_t rData[10];
uint8_t rflag;
/**
 * @brief ���ڽ�����ɷ�����
 * @param null
 * @retval Null
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//�ж��Ƿ��Ǵ���5
	if(huart->Instance == UART5)
	{
		uint8_t com_data; //��ʱ����
		static int rDataFlag = 0;  //buffer�±�λ��
		static uint8_t RXstate = 0;
		//uint16_t cx,cy;

		com_data = OpenMV.tRxInfo.ucpRxBuffer[0];

		if(RXstate == 0 && com_data == 0x2C)  //0x2C֡ͷ
		{
			RXstate = 1;
			rData[rDataFlag++] = com_data;
		}
		else if(RXstate == 1 && com_data == 0x12) //0x12֡ͷ
		{
			RXstate = 2;
			rData[rDataFlag++] = com_data;
		}
		else if(RXstate == 2) //��ʼ������
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
				rt_sem_release(OpenMV_sem);	//�ͷ�OpenMV�ź���
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

