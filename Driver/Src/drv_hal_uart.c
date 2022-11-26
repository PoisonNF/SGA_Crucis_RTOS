/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_uart.c

* ���ݼ��������������ļ�

* �ļ���ʷ��

* �汾��	  ����		  ����		˵��
* 1.1.7 	2022-10-11   �����		��������DMA������غ���

* 1.1.4 	2022-09-03   �����		��������������ӳ�����

* 1.1.1 	2022-08-04   �����		�޸��˴����������ȷ������

* 1.0.0a 	2020-02-22	 ���		�������ļ�

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_UART_ENABLE

#define TIME_OUT	0xff

/**
 * @brief �����ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null 
*/
static void S_Uart_NVICConfig(tagUART_T *_tUART)
{	
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		HAL_NVIC_SetPriority(USART1_IRQn, _tUART->ulPriority, _tUART->ulSubPriority);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	}       
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		HAL_NVIC_SetPriority(USART2_IRQn, _tUART->ulPriority, _tUART->ulSubPriority);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		HAL_NVIC_SetPriority(USART3_IRQn, _tUART->ulPriority, _tUART->ulSubPriority);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == UART4)
	{
		HAL_NVIC_SetPriority(UART4_IRQn, _tUART->ulPriority, _tUART->ulSubPriority);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == UART5)
	{
		HAL_NVIC_SetPriority(UART5_IRQn, _tUART->ulPriority, _tUART->ulSubPriority);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
	}
}

/**
 * @brief ����DMA�ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null 
*/
static void S_Uart_DMA_NVICConfig(tagUART_T *_tUART)
{
	//Ŀǰֻ�н���
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		/* DMA1_Channel5_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Channel5_IRQn,_tUART->tUartDMA.ulDMAPriority, _tUART->tUartDMA.ulDMASubPriority);
  		HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		/* DMA1_Channel6_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Channel6_IRQn,_tUART->tUartDMA.ulDMAPriority, _tUART->tUartDMA.ulDMASubPriority);
		HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		/* DMA1_Channel3_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Channel3_IRQn,_tUART->tUartDMA.ulDMAPriority, _tUART->tUartDMA.ulDMASubPriority);
		HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == UART4)
	{
		/* DMA2_Channel3_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Channel3_IRQn,_tUART->tUartDMA.ulDMAPriority, _tUART->tUartDMA.ulDMASubPriority);
		HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
	}

}


/**
 * @brief ���ڲ������ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null
*/
static void S_Uart_ParamConfig(tagUART_T *_tUART)
{	
	if (HAL_UART_Init(&_tUART->tUARTHandle) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
}

/**
 * @brief ����DMA�������ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null
*/
static void S_Uart_DMAParamConfig(tagUART_T *_tUART)
{
	//Ŀǰֻ�н���
	if(HAL_DMA_Init(&_tUART->tUartDMA.tDMARx) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__,__LINE__);
	}
}

/**
 * @brief ����ʱ�ӳ�ʼ������---L4ʹ��
 * @param null
 * @retval Null
*/
static void S_Uart_CLKConfig(void)
{
#if defined (STM32L4_SGA_ENABLE)
/* Select UART function start */
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_UART5;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
/* Select UART function end */	
#endif
}

/**
 * @brief ����ʱ��ʹ�ܺ���
 * @param *_tUART-���ڽṹ��ָ��
 * @retval Null
*/
static void S_UART_CLKEnable(tagUART_T *_tUART)
{
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		__HAL_RCC_USART2_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		__HAL_RCC_USART3_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == UART4)
	{
		__HAL_RCC_UART4_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == UART5)
	{
		__HAL_RCC_UART5_CLK_ENABLE();
	}
}

/**
 * @brief DMAʱ��ʹ�ܺ���
 * @param *_tUART-���ڽṹ��ָ��
 * @retval Null
*/
static void S_UART_DMA_CLKEnable(tagUART_T *_tUART)
{
	if(_tUART->tUARTHandle.Instance == USART1)			__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == USART2)		__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == USART3)		__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == UART4)		__HAL_RCC_DMA2_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == UART5)		while(1);	//uart5����ʹ��DMA
}

/**
 * @brief UART��GPIO�������ú���
 * @param *_tUART-���ھ��ָ��
 * @retval Null
*/
static void S_UART_GPIOConfig(tagUART_T *_tUART)
{
	/* ��������ģʽʱ�� */
	__HAL_RCC_AFIO_CLK_ENABLE();

	/* ���ݲ�ͬ���ڵ�AFMode������Ӧ����ӳ�䣬��ӳ�����drv_hal_uart.h�� */
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		if(_tUART->tGPIO->AFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART1_DISABLE();
		else if(_tUART->tGPIO->AFMode == FULL_REMAP) 	    __HAL_AFIO_REMAP_USART1_ENABLE();
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP)	    while(1);
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP2)	while(1);
	}
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		if(_tUART->tGPIO->AFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART2_DISABLE();
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP)	    while(1);
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP2)	while(1);
		else if(_tUART->tGPIO->AFMode == FULL_REMAP)		__HAL_AFIO_REMAP_USART2_ENABLE();
	}	
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		if(_tUART->tGPIO->AFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART3_DISABLE();
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP)	    __HAL_AFIO_REMAP_USART3_PARTIAL();
		else if(_tUART->tGPIO->AFMode == PARTIAL_REMAP2)	while(1);
		else if(_tUART->tGPIO->AFMode == FULL_REMAP)		__HAL_AFIO_REMAP_USART3_ENABLE();
	}
	
	Drv_GPIO_Init(_tUART->tGPIO, 2); 	/* GPIO��ʼ�� */
}

/**
 * @brief ������ͨ�ж�ģʽ��ʼ������
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null 
*/
void Drv_Uart_ITInit(tagUART_T *_tUART)
{
	S_Uart_CLKConfig();
	S_UART_CLKEnable(_tUART);
	S_UART_GPIOConfig(_tUART);
	S_Uart_ParamConfig(_tUART);		/* ���ô��ڲ��� */
	S_Uart_NVICConfig(_tUART);		/* �����ж����ȼ� */

	Drv_Uart_ReceIT_Enable(_tUART,_tUART->tRxInfo.ucpRxBuffer,1);
}

/**
 * @brief ����DMAģʽ��ʼ������
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null 
*/
void Drv_Uart_DMAInit(tagUART_T *_tUART)
{
	S_Uart_CLKConfig();				/* L4���� */

	S_UART_DMA_CLKEnable(_tUART);
	S_Uart_DMA_NVICConfig(_tUART);
	S_Uart_DMAParamConfig(_tUART);

	S_UART_CLKEnable(_tUART);
	S_UART_GPIOConfig(_tUART);
	S_Uart_NVICConfig(_tUART);		/* �����ж����ȼ� */
	S_Uart_ParamConfig(_tUART);		/* ���ô��ڲ��� */

	__HAL_LINKDMA(&_tUART->tUARTHandle,hdmarx,_tUART->tUartDMA.tDMARx);
	_tUART->tRxInfo.ucpRxCache = (uint8_t *)malloc(_tUART->tRxInfo.usRxMAXLenth);	//Ϊcache����һ�γ��ȵĶ�̬�ڴ�
	__HAL_UART_ENABLE_IT(&_tUART->tUARTHandle,UART_IT_IDLE); //�򿪿����ж�
	HAL_UART_Receive_DMA(&_tUART->tUARTHandle,_tUART->tRxInfo.ucpRxCache,_tUART->tRxInfo.usRxMAXLenth);//����DMA����

}

/**
 * @brief ���ڷ������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpTxData-�������ݵ�ַָ��
 * @param _uspSize-�������ݴ�С
 * @retval Null
*/
void Drv_Uart_Transmit(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize)
{	
	HAL_UART_Transmit(&_tUART->tUARTHandle, _ucpTxData, _uspSize, TIME_OUT);
}

/**
 * @brief ���ڽ����ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpBuffer-��������ָ��
 * @param _usSize-�������ݴ�С
 * @retval Null 
*/
void Drv_Uart_ReceIT_Enable(tagUART_T *_tUART, uint8_t *_ucpBuffer, uint16_t _usSize)
{
	HAL_UART_Receive_IT(&_tUART->tUARTHandle, _ucpBuffer, _usSize);
}

/**
 * @brief ����1�ж�ñ�Ӻ���
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null
*/
void Drv_Uart_IRQHandler(tagUART_T *_tUART)
{
	HAL_UART_IRQHandler(&_tUART->tUARTHandle);
}

/**
 * @brief ����DMA�жϽ��մ����Ӻ���(���ڴ����жϴ�������)
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null
*/
void Drv_Uart_DMA_Handler(tagUART_T *_tUART)
{
	if(__HAL_UART_GET_FLAG(&_tUART->tUARTHandle,UART_FLAG_IDLE) != RESET) // �����жϱ�Ǳ���λ
	{
		__HAL_UART_CLEAR_IDLEFLAG(&_tUART->tUARTHandle);// ����жϱ��
		HAL_UART_DMAStop(&_tUART->tUARTHandle);// ֹͣDMA����
		_tUART->tRxInfo.usRxLenth = _tUART->tRxInfo.usRxMAXLenth - __HAL_DMA_GET_COUNTER(_tUART->tUARTHandle.hdmarx);// ����������ȥδ���յ���������Ϊ�Ѿ����յ���������
        _tUART->tUartDMA.DMARxCplt = 1;// ��ǽ��ս���
        HAL_UART_Receive_DMA(&_tUART->tUARTHandle,_tUART->tRxInfo.ucpRxCache,_tUART->tRxInfo.usRxMAXLenth);// ��������DMA����
	}
}


#endif
