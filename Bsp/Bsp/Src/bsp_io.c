#include "bsp_io.h"

/* 
	motor PWM1	PC6							steering engine	RS1	PD12
		  PWM2	PC7											RS2	PD13
		  PWM3	PC8											RS3	PD14
		  PWM4	PC9											RS4	PD15

*/

tagPWM_T tPWMDemo[]=
{
	//motor config
	[0] =	//PWM1
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_6,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[1] =	//PWM2
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_7,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[2] =	//PWM3
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},
	[3] =	//PWM4
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_9,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.AFMode			= NO_REMAP,			/* IO��ӳ��ģʽ */
	},

	//steer engine config

	[4] =	//RS1
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_12,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[5] =	//RS2
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[6] =	//RS3
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
	[7] =	//RS4
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��3 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ulChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_15,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO��ӳ��ģʽ */
	},
};

/* OLEDʾ�� */
tagOLED_T tOLED= 
{
	/* SCL�� */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO���� */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOC,					/* GPIO���� */
	
	/* SDA�� */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO���� */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOC,					/* GPIO���� */
};

/* ADC���ʾ�� */
tagADC_T demoADC[] = 
{
	[0]=
	{ 
		.tGPIO.tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO���� */
		.tGPIO.tGPIOInit.Mode 		= GPIO_MODE_ANALOG,		/* GPIOģʽ */
		.tGPIO.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIO.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIO.tGPIOPort 			= GPIOA,					/* GPIO���� */
		
		.tADCHandle.Instance					=ADC1,
		.tADCHandle.Init.DataAlign				=ADC_DATAALIGN_RIGHT,	/* �Ҷ��� */
		.tADCHandle.Init.ScanConvMode			=ENABLE,				/* ��ɨ��ģʽ */
		.tADCHandle.Init.ContinuousConvMode		=DISABLE,				/* �ر�����ת�� */
		.tADCHandle.Init.NbrOfConversion		=1,						/* 1��ת���ڹ��������� Ҳ����ֻת����������1 */ 
		.tADCHandle.Init.DiscontinuousConvMode	=DISABLE,				/* ��ֹ����������ģʽ */
		.tADCHandle.Init.NbrOfDiscConversion	=0,						/* ����������ͨ����Ϊ0 */
		.tADCHandle.Init.ExternalTrigConv		=ADC_SOFTWARE_START,	/* ������� */
		
		.tADCChannel.Channel		= ADC_CHANNEL_1,				/* ͨ�� */
		.tADCChannel.Rank			= 1,							/* ��1�����У�����1 */
		.tADCChannel.SamplingTime	= ADC_SAMPLETIME_13CYCLES_5,	/* ����ʱ�� */
		
		.ucAverageNum				= 100,							/* ��ֵ�˲���ֵ�� */
	},
};

/* GPIO���ʾ�� */
tagGPIO_T demoGPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOB,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOE,					/* GPIO���� */
	},
    
};

/* ���ھ��ʾ�� */
tagUART_T demoUart1 = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tRxInfo.usRxMAXLenth             	= 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	.tUartDMA.tDMARx.Instance			= DMA1_Channel5,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ulDMAPriority				= 1,				/* DMA�ж����ȼ� */
	.tUartDMA.ulDMASubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_9,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* ���ھ��ʾ�� */
tagUART_T demoUart2 = 
{
	.tUARTHandle.Instance 				= USART2,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tRxInfo.usRxMAXLenth             	= 300,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* �ж����ȼ� */
	.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	.tUartDMA.tDMARx.Instance			= DMA1_Channel6,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ulDMAPriority				= 1,				/* DMA�ж����ȼ� */
	.tUartDMA.ulDMASubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* ���ھ��ʾ�� */
tagJY901_T JY901S = 
{
	.tConfig.ucBaud 	= JY901_RXBAUD_9600,
	.tConfig.ucRate		= JY901_RX_0_2HZ,
	.tConfig.ucType		= JY901_OUTPUT_ACCEL | JY901_OUTPUT_GYRO | JY901_OUTPUT_ANGLE | JY901_OUTPUT_MAG,

	.tUART.tUARTHandle.Instance 				= USART2,			/* STM32 �����豸 */
	.tUART.tUARTHandle.Init.BaudRate   			= 9600,				/* ���ڲ����� */
	.tUART.tUARTHandle.Init.WordLength 			= UART_WORDLENGTH_8B,
	.tUART.tUARTHandle.Init.StopBits   			= UART_STOPBITS_1,
	.tUART.tUARTHandle.Init.Parity     			= UART_PARITY_NONE,
	.tUART.tUARTHandle.Init.HwFlowCtl  			= UART_HWCONTROL_NONE,
	.tUART.tUARTHandle.Init.Mode       			= UART_MODE_TX_RX,
	.tUART.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tUART.tRxInfo.usRxMAXLenth             	= 300,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.tUART.ulPriority							= 1,				/* �ж����ȼ� */
	.tUART.ulSubPriority						= 3,				/* �ж������ȼ� */
	
	.tUART.tUartDMA.tDMARx.Instance					= DMA1_Channel6,
	.tUART.tUartDMA.tDMARx.Init.Direction			= DMA_PERIPH_TO_MEMORY,
	.tUART.tUartDMA.tDMARx.Init.PeriphInc			= DMA_PINC_DISABLE,
	.tUART.tUartDMA.tDMARx.Init.MemInc				= DMA_MINC_ENABLE,
	.tUART.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.Mode				= DMA_NORMAL,
	.tUART.tUartDMA.tDMARx.Init.Priority			= DMA_PRIORITY_LOW,

	.tUART.tUartDMA.ulDMAPriority				= 1,				/* DMA�ж����ȼ� */
	.tUART.tUartDMA.ulDMASubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tUART.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tUART.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tUART.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tUART.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tUART.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tUART.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tUART.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO���� */
	.tUART.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tUART.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tUART.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tUART.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tUART.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};


