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
		.tPWMHandle.Instance	= TIM8,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_1,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_6,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO组映射 */
		.tGPIO.AFMode			= NO_REMAP,			/* IO重映射模式 */
	},
	[1] =	//PWM2
	{
		.tPWMHandle.Instance	= TIM8,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_2,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_7,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO组映射 */
		.tGPIO.AFMode			= NO_REMAP,			/* IO重映射模式 */
	},
	[2] =	//PWM3
	{
		.tPWMHandle.Instance	= TIM8,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_3,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO组映射 */
		.tGPIO.AFMode			= NO_REMAP,			/* IO重映射模式 */
	},
	[3] =	//PWM4
	{
		.tPWMHandle.Instance	= TIM8,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_4,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_9,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO组映射 */
		.tGPIO.AFMode			= NO_REMAP,			/* IO重映射模式 */
	},

	//steer engine config

	[4] =	//RS1
	{
		.tPWMHandle.Instance	= TIM4,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_1,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_12,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO组映射 */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO重映射模式 */
	},
	[5] =	//RS2
	{
		.tPWMHandle.Instance	= TIM4,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_2,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO组映射 */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO重映射模式 */
	},
	[6] =	//RS3
	{
		.tPWMHandle.Instance	= TIM4,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_3,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO组映射 */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO重映射模式 */
	},
	[7] =	//RS4
	{
		.tPWMHandle.Instance	= TIM4,         	/* 定时器3 */
		.fDuty					= 7.5,				/* 初始占空比 */
		.ulFreq					= 50,				/* 频率 */
		.ulChannel				= TIM_CHANNEL_4,	/* 通道 */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_15,		/* IO映射 */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO组映射 */
		.tGPIO.AFMode			= FULL_REMAP,			/* IO重映射模式 */
	},
};

/* OLED示例 */
tagOLED_T tOLED= 
{
	/* SCL线 */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOC,					/* GPIO分组 */
	
	/* SDA线 */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_11,				/* GPIO引脚 */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOC,					/* GPIO分组 */
};

/* ADC句柄示例 */
tagADC_T demoADC[] = 
{
	[0]=
	{ 
		.tGPIO.tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO引脚 */
		.tGPIO.tGPIOInit.Mode 		= GPIO_MODE_ANALOG,		/* GPIO模式 */
		.tGPIO.tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIO.tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIO.tGPIOPort 			= GPIOA,					/* GPIO分组 */
		
		.tADCHandle.Instance					=ADC1,
		.tADCHandle.Init.DataAlign				=ADC_DATAALIGN_RIGHT,	/* 右对齐 */
		.tADCHandle.Init.ScanConvMode			=ENABLE,				/* 非扫描模式 */
		.tADCHandle.Init.ContinuousConvMode		=DISABLE,				/* 关闭连续转换 */
		.tADCHandle.Init.NbrOfConversion		=1,						/* 1个转换在规则序列中 也就是只转换规则序列1 */ 
		.tADCHandle.Init.DiscontinuousConvMode	=DISABLE,				/* 禁止不连续采样模式 */
		.tADCHandle.Init.NbrOfDiscConversion	=0,						/* 不连续采样通道数为0 */
		.tADCHandle.Init.ExternalTrigConv		=ADC_SOFTWARE_START,	/* 软件触发 */
		
		.tADCChannel.Channel		= ADC_CHANNEL_1,				/* 通道 */
		.tADCChannel.Rank			= 1,							/* 第1个序列，序列1 */
		.tADCChannel.SamplingTime	= ADC_SAMPLETIME_13CYCLES_5,	/* 采样时间 */
		
		.ucAverageNum				= 100,							/* 均值滤波均值数 */
	},
};

/* GPIO句柄示例 */
tagGPIO_T demoGPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOB,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOE,					/* GPIO分组 */
	},
    
};

/* 串口句柄示例 */
tagUART_T demoUart1 = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tRxInfo.usRxMAXLenth             	= 100,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	.tUartDMA.tDMARx.Instance			= DMA1_Channel5,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ulDMAPriority				= 1,				/* DMA中断优先级 */
	.tUartDMA.ulDMASubPriority			= 1,				/* DMA中断子优先级 */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_9,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO重映射 */
};

/* 串口句柄示例 */
tagUART_T demoUart2 = 
{
	.tUARTHandle.Instance 				= USART2,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 9600,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tRxInfo.usRxMAXLenth             	= 300,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	.tUartDMA.tDMARx.Instance			= DMA1_Channel6,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_NORMAL,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ulDMAPriority				= 1,				/* DMA中断优先级 */
	.tUartDMA.ulDMASubPriority			= 1,				/* DMA中断子优先级 */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO重映射 */
};

/* 串口句柄示例 */
tagJY901_T JY901S = 
{
	.tConfig.ucBaud 	= JY901_RXBAUD_9600,
	.tConfig.ucRate		= JY901_RX_0_2HZ,
	.tConfig.ucType		= JY901_OUTPUT_ACCEL | JY901_OUTPUT_GYRO | JY901_OUTPUT_ANGLE | JY901_OUTPUT_MAG,

	.tUART.tUARTHandle.Instance 				= USART2,			/* STM32 串口设备 */
	.tUART.tUARTHandle.Init.BaudRate   			= 9600,				/* 串口波特率 */
	.tUART.tUARTHandle.Init.WordLength 			= UART_WORDLENGTH_8B,
	.tUART.tUARTHandle.Init.StopBits   			= UART_STOPBITS_1,
	.tUART.tUARTHandle.Init.Parity     			= UART_PARITY_NONE,
	.tUART.tUARTHandle.Init.HwFlowCtl  			= UART_HWCONTROL_NONE,
	.tUART.tUARTHandle.Init.Mode       			= UART_MODE_TX_RX,
	.tUART.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tUART.tRxInfo.usRxMAXLenth             	= 300,                 /* 接收数据长度 长度保持在协议最长字节*2以上，确保缓存池一定能够稳定接收一个完整的数据帧*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.tUART.ulPriority							= 1,				/* 中断优先级 */
	.tUART.ulSubPriority						= 3,				/* 中断子优先级 */
	
	.tUART.tUartDMA.tDMARx.Instance					= DMA1_Channel6,
	.tUART.tUartDMA.tDMARx.Init.Direction			= DMA_PERIPH_TO_MEMORY,
	.tUART.tUartDMA.tDMARx.Init.PeriphInc			= DMA_PINC_DISABLE,
	.tUART.tUartDMA.tDMARx.Init.MemInc				= DMA_MINC_ENABLE,
	.tUART.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.Mode				= DMA_NORMAL,
	.tUART.tUartDMA.tDMARx.Init.Priority			= DMA_PRIORITY_LOW,

	.tUART.tUartDMA.ulDMAPriority				= 1,				/* DMA中断优先级 */
	.tUART.tUartDMA.ulDMASubPriority			= 1,				/* DMA中断子优先级 */
	
	
	.tUART.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO引脚 */
	.tUART.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tUART.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tUART.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tUART.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tUART.tGPIO[0].AFMode					= NO_REMAP,					/* GPIO重映射 */
	
	.tUART.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO引脚 */
	.tUART.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tUART.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tUART.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tUART.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO分组 */
	.tUART.tGPIO[1].AFMode					= NO_REMAP,					/* GPIO重映射 */
};


