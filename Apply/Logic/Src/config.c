#include "config.h"

/* ���������õ�����IO
	motor 													steering engine
		  PWM1	PD12											RS1	PC9
		  PWM2	PD13											RS2	PC8
		  PWM3	PD14											RS3	PC7
		  PWM4	PD15											RS4	PC6
	OLED 
		SCL��	PC10 SDA��	PC11

	RS485����I/O 
		PE15

	ADC
		PA1

	JY901S
		PA2	PA3 Uart2
	
	PS2�ֱ�
		DAT	PA8
		CMD PA11
		CS	PA12
		CLK PA15

	SPI_soft
		PE2     ------> SPI_SCK				
		PE4     ------> SPI_MISO		
    	PE3     ------> SPI_MOSI		
		PE1     ------> SPI_NSS 		

	SPI
		PA5     ------> SPI1_SCK		PB13     ------> SPI2_SCK		PB3     ------> SPI3_SCK
    	PA6     ------> SPI1_MISO		PB14     ------> SPI2_MISO		PB4     ------> SPI3_MISO
    	PA7     ------> SPI1_MOSI		PB15     ------> SPI2_MOSI		PB5     ------> SPI3_MOSI
		PC5     ------> SPI1_NSS		PD9      ------> SPI2_NSS		PB7     ------> SPI3_NSS

	Uart1			Uart2			Uart3			Uart4			Uart5
		TX PA9 			TX PA2			TX PB10			TX PC10			TX PC12
		RX PA10			RX PA3			RX PB11			RX PC11			RX PD2
*/

/* PWM��������*/
tagPWM_T PWM[]=
{
	//motor config
	[0] =	//PWM1
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��4 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_12,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= FULL_REMAP,		/* IO��ӳ��ģʽ */
	},
	[1] =	//PWM2
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��4 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= FULL_REMAP,		/* IO��ӳ��ģʽ */
	},
	[2] =	//PWM3
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��4 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= FULL_REMAP,		/* IO��ӳ��ģʽ */
	},
	[3] =	//PWM4
	{
		.tPWMHandle.Instance	= TIM4,         	/* ��ʱ��4 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_15,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= FULL_REMAP,		/* IO��ӳ��ģʽ */
	},

	//steer engine config

	[4] =	//RS1
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��8 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_4,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_9,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,		/* IO��ӳ��ģʽ */
	},
	[5] =	//RS2
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��8 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_3,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,		/* IO��ӳ��ģʽ */
	},
	[6] =	//RS3
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��8 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_2,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_7,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,		/* IO��ӳ��ģʽ */
	},
	[7] =	//RS4
	{
		.tPWMHandle.Instance	= TIM8,         	/* ��ʱ��8 */
		.fDuty					= 7.5,				/* ��ʼռ�ձ� */
		.ulFreq					= 50,				/* Ƶ�� */
		.ucChannel				= TIM_CHANNEL_1,	/* ͨ�� */
		.tGPIO.tGPIOInit.Pin	= GPIO_PIN_6,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
		.tGPIO.ucAFMode			= NO_REMAP,		/* IO��ӳ��ģʽ */
	},
};

/* OLED�������� */
tagOLED_T OLED= 
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

/* ADC�������� */
tagADC_T ADC[] = 
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

/* GPIO�������� */
tagGPIO_T GPIO[] =
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


/* PS2�ֱ��������� */
tagPS2_T PS2 = 
{
	//DI/DAT
	.tGPIO[0].tGPIOInit.Pin = GPIO_PIN_8,
	.tGPIO[0].tGPIOInit.Mode = GPIO_MODE_INPUT,
	.tGPIO[0].tGPIOInit.Pull = GPIO_NOPULL,
	.tGPIO[0].tGPIOPort = GPIOA,
	.tGPIO[0].ucAFMode = NO_REMAP,
	//DO/CMD
	.tGPIO[1].tGPIOInit.Pin = GPIO_PIN_11,
	.tGPIO[1].tGPIOInit.Mode = GPIO_MODE_OUTPUT_PP,
	.tGPIO[1].tGPIOInit.Pull = GPIO_NOPULL,
	.tGPIO[1].tGPIOInit.Speed = GPIO_SPEED_FREQ_HIGH,
	.tGPIO[1].tGPIOPort = GPIOA,
	.tGPIO[1].ucAFMode = NO_REMAP,
	//CS
	.tGPIO[2].tGPIOInit.Pin = GPIO_PIN_12,
	.tGPIO[2].tGPIOInit.Mode = GPIO_MODE_OUTPUT_PP,
	.tGPIO[2].tGPIOInit.Pull = GPIO_NOPULL,
	.tGPIO[2].tGPIOInit.Speed = GPIO_SPEED_FREQ_HIGH,
	.tGPIO[2].tGPIOPort = GPIOA,
	.tGPIO[2].ucAFMode = NO_REMAP,
	//CLK
	.tGPIO[3].tGPIOInit.Pin = GPIO_PIN_15,
	.tGPIO[3].tGPIOInit.Mode = GPIO_MODE_OUTPUT_PP,
	.tGPIO[3].tGPIOInit.Pull = GPIO_NOPULL,
	.tGPIO[3].tGPIOInit.Speed = GPIO_SPEED_FREQ_HIGH,
	.tGPIO[3].tGPIOPort = GPIOA,
	.tGPIO[3].ucAFMode = NO_REMAP,
};

/* ���SPI�������� */
tagSPISoft_T SPI_soft[2] =
{
	[0]=
	{
	/**SPI Soft GPIO Configuration
    PE2     ------> SPI_SCK
	PE4     ------> SPI_MISO
    PE3     ------> SPI_MOSI
	PE1     ------> SPI_NSS 
    */
	.tSPISoft[0].tGPIOInit.Pin		= GPIO_PIN_2,
	.tSPISoft[0].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[0].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[0].tGPIOPort			= GPIOE,
	.tSPISoft[0].ucAFMode				= NO_REMAP,
	
	.tSPISoft[1].tGPIOInit.Pin		= GPIO_PIN_4,
	.tSPISoft[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,
	.tSPISoft[1].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[1].tGPIOPort			= GPIOE,
	.tSPISoft[1].ucAFMode				= NO_REMAP,
	
	.tSPISoft[2].tGPIOInit.Pin		= GPIO_PIN_3,
	.tSPISoft[2].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[2].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[2].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[2].tGPIOPort			= GPIOE,
	.tSPISoft[2].ucAFMode				= NO_REMAP,
	
	.tSPISoft[3].tGPIOInit.Pin		= GPIO_PIN_1,
	.tSPISoft[3].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[3].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[3].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[3].tGPIOPort			= GPIOE,
	.tSPISoft[3].ucAFMode				= NO_REMAP,
	},
	[1] = 
	{
	/**SPI Soft GPIO Configuration
    PB13      ------> SPI_SCK
    PB14      ------> SPI_MISO 
    PB15      ------> SPI_MOSI
    PD9      ------> SPI_NSS
    */
	.tSPISoft[0].tGPIOInit.Pin		= GPIO_PIN_13,
	.tSPISoft[0].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[0].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[0].tGPIOPort			= GPIOB,
	.tSPISoft[0].ucAFMode				= NO_REMAP,
	
	.tSPISoft[1].tGPIOInit.Pin		= GPIO_PIN_14,
	.tSPISoft[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,
	.tSPISoft[1].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[1].tGPIOPort			= GPIOB,
	.tSPISoft[1].ucAFMode				= NO_REMAP,
	
	.tSPISoft[2].tGPIOInit.Pin		= GPIO_PIN_15,
	.tSPISoft[2].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[2].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[2].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[2].tGPIOPort			= GPIOB,
	.tSPISoft[2].ucAFMode				= NO_REMAP,
	
	.tSPISoft[3].tGPIOInit.Pin		= GPIO_PIN_9,
	.tSPISoft[3].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tSPISoft[3].tGPIOInit.Pull 	= GPIO_PULLUP,
	.tSPISoft[3].tGPIOInit.Speed	= GPIO_SPEED_FREQ_HIGH,
	.tSPISoft[3].tGPIOPort			= GPIOD,
	.tSPISoft[3].ucAFMode				= NO_REMAP,
	},
};

/* Ӳ��SPI�������� */
tagSPI_T SPI[3] =
{
	[0]=
	{
	.tSPIHandle.Instance 				= SPI1,
	.tSPIHandle.Init.Mode 				= SPI_MODE_MASTER,
	.tSPIHandle.Init.Direction 			= SPI_DIRECTION_2LINES,
	.tSPIHandle.Init.DataSize 			= SPI_DATASIZE_8BIT,
	.tSPIHandle.Init.CLKPolarity 		= SPI_POLARITY_LOW,
	.tSPIHandle.Init.CLKPhase 			= SPI_PHASE_1EDGE,
	.tSPIHandle.Init.NSS 				= SPI_NSS_SOFT,
	.tSPIHandle.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_64,
	.tSPIHandle.Init.FirstBit 			= SPI_FIRSTBIT_MSB,
	.tSPIHandle.Init.TIMode 			= SPI_TIMODE_DISABLE,
	.tSPIHandle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE,
	.tSPIHandle.Init.CRCPolynomial 		= 10,	
#if defined (STM32L4_SGA_ENABLE)
	.tSPIHandle.Init.CRCLength 		= SPI_CRC_LENGTH_DATASIZE,
	.tSPIHandle.Init.NSSPMode 			= SPI_NSS_PULSE_ENABLE,	
#endif
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
	PC5     ------> SPI1_NSS
    */
    .tGPIO[0].tGPIOInit.Pin		= GPIO_PIN_5,
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[0].tGPIOPort			= GPIOA,
	.tGPIO[0].ucAFMode			= NO_REMAP,

	.tGPIO[1].tGPIOInit.Pin 	= GPIO_PIN_6,
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,
	.tGPIO[1].tGPIOPort			= GPIOA,
	.tGPIO[1].ucAFMode			= NO_REMAP,

	.tGPIO[2].tGPIOInit.Pin		= GPIO_PIN_7,
	.tGPIO[2].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[2].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[2].tGPIOPort			= GPIOA,
	.tGPIO[2].ucAFMode			= NO_REMAP,
	
	.tGPIO[3].tGPIOInit.Pin		= GPIO_PIN_5,
	.tGPIO[3].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tGPIO[3].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[3].tGPIOPort			= GPIOC,
	.tGPIO[3].ucAFMode			= NO_REMAP,
	
	},
	[1]=
	{
	.tSPIHandle.Instance 				= SPI2,
	.tSPIHandle.Init.Mode 				= SPI_MODE_MASTER,
	.tSPIHandle.Init.Direction 			= SPI_DIRECTION_2LINES,
	.tSPIHandle.Init.DataSize 			= SPI_DATASIZE_8BIT,
	.tSPIHandle.Init.CLKPolarity 		= SPI_POLARITY_LOW,
	.tSPIHandle.Init.CLKPhase 			= SPI_PHASE_1EDGE,
	.tSPIHandle.Init.NSS 				= SPI_NSS_SOFT,
	.tSPIHandle.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_32,
	.tSPIHandle.Init.FirstBit 			= SPI_FIRSTBIT_MSB,
	.tSPIHandle.Init.TIMode 			= SPI_TIMODE_DISABLE,
	.tSPIHandle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE,
	.tSPIHandle.Init.CRCPolynomial 		= 10,	
#if defined (STM32L4_SGA_ENABLE)
	.tSPIHandle.Init.CRCLength 		= SPI_CRC_LENGTH_DATASIZE,
	.tSPIHandle.Init.NSSPMode 			= SPI_NSS_PULSE_ENABLE,	
#endif
    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
	PD9     ------> SPI2_NSS
    */
    .tGPIO[0].tGPIOInit.Pin		= GPIO_PIN_13,
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[0].tGPIOPort			= GPIOB,
	.tGPIO[0].ucAFMode			= NO_REMAP,

	.tGPIO[1].tGPIOInit.Pin 	= GPIO_PIN_14,
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,
	.tGPIO[1].tGPIOPort			= GPIOB,
	.tGPIO[1].ucAFMode			= NO_REMAP,

	.tGPIO[2].tGPIOInit.Pin		= GPIO_PIN_15,
	.tGPIO[2].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[2].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[2].tGPIOPort			= GPIOB,
	.tGPIO[2].ucAFMode			= NO_REMAP,
	
	.tGPIO[3].tGPIOInit.Pin		= GPIO_PIN_9,
	.tGPIO[3].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tGPIO[3].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[3].tGPIOPort			= GPIOD,
	.tGPIO[3].ucAFMode			= NO_REMAP,
	
	},
	[2]=
	{
	.tSPIHandle.Instance 				= SPI3,
	.tSPIHandle.Init.Mode 				= SPI_MODE_MASTER,
	.tSPIHandle.Init.Direction 			= SPI_DIRECTION_2LINES,
	.tSPIHandle.Init.DataSize 			= SPI_DATASIZE_8BIT,
	.tSPIHandle.Init.CLKPolarity 		= SPI_POLARITY_LOW,
	.tSPIHandle.Init.CLKPhase 			= SPI_PHASE_1EDGE,
	.tSPIHandle.Init.NSS 				= SPI_NSS_SOFT,
	.tSPIHandle.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_32,
	.tSPIHandle.Init.FirstBit 			= SPI_FIRSTBIT_MSB,
	.tSPIHandle.Init.TIMode 			= SPI_TIMODE_DISABLE,
	.tSPIHandle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE,
	.tSPIHandle.Init.CRCPolynomial 		= 10,	
#if defined (STM32L4_SGA_ENABLE)
	.tSPIHandle.Init.CRCLength 		= SPI_CRC_LENGTH_DATASIZE,
	.tSPIHandle.Init.NSSPMode 			= SPI_NSS_PULSE_ENABLE,	
#endif
   /**SPI3 GPIO Configuration
    PB3     ------> SPI3_SCK
    PB4     ------> SPI3_MISO
    PB5     ------> SPI3_MOSI
	PB7     ------> SPI3_NSS
    */
    .tGPIO[0].tGPIOInit.Pin		= GPIO_PIN_3,
	.tGPIO[0].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[0].tGPIOPort			= GPIOB,
	.tGPIO[0].ucAFMode			= NO_REMAP,

	.tGPIO[1].tGPIOInit.Pin 	= GPIO_PIN_4,
	.tGPIO[1].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[1].tGPIOInit.Pull 	= GPIO_NOPULL,
	.tGPIO[1].tGPIOPort			= GPIOB,
	.tGPIO[1].ucAFMode			= NO_REMAP,

	.tGPIO[2].tGPIOInit.Pin		= GPIO_PIN_5,
	.tGPIO[2].tGPIOInit.Mode 	= GPIO_MODE_AF_PP,
	.tGPIO[2].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[2].tGPIOPort			= GPIOB,
	.tGPIO[2].ucAFMode			= NO_REMAP,
	
	.tGPIO[3].tGPIOInit.Pin		= GPIO_PIN_7,
	.tGPIO[3].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,
	.tGPIO[3].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,
	.tGPIO[3].tGPIOPort			= GPIOB,
	.tGPIO[3].ucAFMode			= NO_REMAP,
	},
	
};

/* Uart1�������� */
tagUART_T Uart1 = 
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
	
	.ucPriority							= 1,				/* �ж����ȼ� */
	.ucSubPriority						= 3,				/* �ж������ȼ� */
	
    .tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel5,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ucDMARxPriority				= 1,				/* DMA�ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_9,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* JY901S�������� */
tagJY901_T JY901S = 
{
	.tConfig.ucBaud 	= JY901_RXBAUD_9600,
	.tConfig.ucRate		= JY901_RX_0_5HZ,
	.tConfig.usType		= JY901_OUTPUT_ACCEL | JY901_OUTPUT_GYRO | JY901_OUTPUT_ANGLE | JY901_OUTPUT_MAG,

	.tUART.tUARTHandle.Instance 				= USART2,			/* STM32 �����豸 */
	.tUART.tUARTHandle.Init.BaudRate   			= 9600,				/* ���ڲ����� */
	.tUART.tUARTHandle.Init.WordLength 			= UART_WORDLENGTH_8B,
	.tUART.tUARTHandle.Init.StopBits   			= UART_STOPBITS_1,
	.tUART.tUARTHandle.Init.Parity     			= UART_PARITY_NONE,
	.tUART.tUARTHandle.Init.HwFlowCtl  			= UART_HWCONTROL_NONE,
	.tUART.tUARTHandle.Init.Mode       			= UART_MODE_TX_RX,
	.tUART.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tUART.tRxInfo.usRxMAXLenth             	= 100,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.tUART.ucPriority							= 1,				/* �ж����ȼ� */
	.tUART.ucSubPriority						= 3,				/* �ж������ȼ� */
	
    .tUART.tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUART.tUartDMA.tDMARx.Instance					= DMA1_Channel6,
	.tUART.tUartDMA.tDMARx.Init.Direction			= DMA_PERIPH_TO_MEMORY,
	.tUART.tUartDMA.tDMARx.Init.PeriphInc			= DMA_PINC_DISABLE,
	.tUART.tUartDMA.tDMARx.Init.MemInc				= DMA_MINC_ENABLE,
	.tUART.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE,
	.tUART.tUartDMA.tDMARx.Init.Mode				= DMA_CIRCULAR,
	.tUART.tUartDMA.tDMARx.Init.Priority			= DMA_PRIORITY_LOW,

	.tUART.tUartDMA.ucDMARxPriority				= 1,				/* DMA�ж����ȼ� */
	.tUART.tUartDMA.ucDMARxSubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tUART.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tUART.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tUART.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tUART.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tUART.tGPIO[0].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tUART.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tUART.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_3,				/* GPIO���� */
	.tUART.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tUART.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tUART.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tUART.tGPIO[1].tGPIOPort 				= GPIOA,					/* GPIO���� */
	.tUART.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* Uart3�������� */
tagUART_T Uart3 = 
{
	.tUARTHandle.Instance 				= USART3,			/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   		= 115200,				/* ���ڲ����� */
	.tUARTHandle.Init.WordLength 		= UART_WORDLENGTH_8B,
	.tUARTHandle.Init.StopBits   		= UART_STOPBITS_1,
	.tUARTHandle.Init.Parity     		= UART_PARITY_NONE,
	.tUARTHandle.Init.HwFlowCtl  		= UART_HWCONTROL_NONE,
	.tUARTHandle.Init.Mode       		= UART_MODE_TX_RX,
	.tUARTHandle.Init.OverSampling 		= UART_OVERSAMPLING_16,

	.tRxInfo.usRxMAXLenth             	= 256,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

#if defined (STM32L4_SGA_ENABLE)
	.tUARTHandle.Init.OneBitSampling 	= UART_ONE_BIT_SAMPLE_DISABLE,
	.tUARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
#endif
	
	.ucPriority							= 1,				/* �ж����ȼ� */
	.ucSubPriority						= 4,				/* �ж������ȼ� */
	
    .tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance			= DMA1_Channel3,
	.tUartDMA.tDMARx.Init.Direction		= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc		= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc		= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	  = DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode			= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority		= DMA_PRIORITY_LOW,

	.tUartDMA.ucDMARxPriority				= 2,				/* DMA�ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 1,				/* DMA�ж������ȼ� */
	
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOB,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOB,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* Uart4�������� */
tagUART_T Uart4 = 
{
	.tUARTHandle.Instance 				= UART4,			/* STM32 �����豸 */
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
	
	.ucPriority							= 1,				/* �ж����ȼ� */
	.ucSubPriority						= 3,				/* �ж������ȼ� */

    .tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tUartDMA.tDMARx.Instance				= DMA2_Channel3,
	.tUartDMA.tDMARx.Init.Direction			= DMA_PERIPH_TO_MEMORY,
	.tUartDMA.tDMARx.Init.PeriphInc			= DMA_PINC_DISABLE,
	.tUartDMA.tDMARx.Init.MemInc			= DMA_MINC_ENABLE,
	.tUartDMA.tDMARx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE,
	.tUartDMA.tDMARx.Init.Mode				= DMA_CIRCULAR,
	.tUartDMA.tDMARx.Init.Priority			= DMA_PRIORITY_LOW,

	.tUartDMA.ucDMARxPriority				= 2,				/* DMA�ж����ȼ� */
	.tUartDMA.ucDMARxSubPriority			= 2,				/* DMA�ж������ȼ� */
	
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_10,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_11,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

/* Uart4 485����I/O*/
tagGPIO_T U4485Ctrl =
{
	.tGPIOInit.Pin 						= GPIO_PIN_15,
	.tGPIOInit.Mode 					= GPIO_MODE_OUTPUT_PP,
	.tGPIOInit.Pull 					= GPIO_NOPULL,
	.tGPIOInit.Speed 					= GPIO_SPEED_FREQ_HIGH,
	.tGPIOPort 							= GPIOE,
	.ucAFMode 							= NO_REMAP,
};


/* Uart5�������� */
tagUART_T OpenMV = 
{
	.tUARTHandle.Instance 				= UART5,			/* STM32 �����豸 */
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
	
	.ucPriority							= 1,				/* �ж����ȼ� */
	.ucSubPriority						= 3,				/* �ж������ȼ� */
	
    .tUartDMA.bRxEnable					= true,						/* DMA����ʹ�� */
	.tGPIO[0].tGPIOInit.Pin 			= GPIO_PIN_12,				/* GPIO���� */
	.tGPIO[0].tGPIOInit.Mode 			= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tGPIO[0].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[0].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[0].tGPIOPort 				= GPIOC,					/* GPIO���� */
	.tGPIO[0].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
	
	.tGPIO[1].tGPIOInit.Pin 			= GPIO_PIN_2,				/* GPIO���� */
	.tGPIO[1].tGPIOInit.Mode 			= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tGPIO[1].tGPIOInit.Pull 			= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIO[1].tGPIOInit.Speed 			= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIO[1].tGPIOPort 				= GPIOD,					/* GPIO���� */
	.tGPIO[1].ucAFMode					= NO_REMAP,					/* GPIO��ӳ�� */
};

