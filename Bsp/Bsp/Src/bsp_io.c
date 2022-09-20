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
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO引脚 */
	.tIIC.tIICSoft[0].tGPIOInit.Mode		= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
	.tIIC.tIICSoft[0].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[0].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOA,					/* GPIO分组 */
	
	/* SDA线 */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_1,				/* GPIO引脚 */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOA,					/* GPIO分组 */
};


/* GPIO句柄示例 */
tagGPIO_T demoGPIO[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO引脚 */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIO模式 */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
		.tGPIOPort 			= GPIOD,					/* GPIO分组 */
	},
    
};

/* 串口句柄示例 */
tagUART_T demoUart = 
{
	.tUARTHandle.Instance 				= USART1,			/* STM32 串口设备 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* 串口波特率 */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,
	
#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ulPriority							= 1,				/* 中断优先级 */
	.ulSubPriority						= 3,				/* 中断子优先级 */
	
	
	
	.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO引脚 */
	.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIO模式 */
	.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[0].tGPIOPort 			= GPIOA,					/* GPIO分组 */
	.tGPIO[0].AFMode				= NO_REMAP,					/* GPIO重映射 */
	
	.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_10,				/* GPIO引脚 */
	.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_INPUT,			/* GPIO模式 */
	.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO上下拉设置，是否需要上下拉看硬件 */
	.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO速度 */	
	.tGPIO[1].tGPIOPort 			= GPIOA,					/* GPIO分组 */
	.tGPIO[1].AFMode				= NO_REMAP,					/* GPIO重映射 */
};



