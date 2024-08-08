#include "config.h"


/* LED */
tagGPIO_T LED[] =
{
	
	[0]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [1]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    [2]=
	{ 
		.tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� */
		.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
		.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
		.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
		.tGPIOPort 			= GPIOD,					/* GPIO���� */
	},
    
};

/* SYNC���� */
tagGPIO_T SYNC =
{
	.tGPIOInit.Pin 		= GPIO_PIN_0,				/* GPIO���� */
	.tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tGPIOPort 			= GPIOE,					/* GPIO���� */
};

/* ����1 DAP�ӿ� ����RS232�ӿ� */
tagUART_T Uart1 = 
{
	//���ڹ���ģʽ����
	.tUARTHandle.Instance 						= USART1,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   				= 9600,					/* ���ڲ����� */

	.ucPriority									= 1,						/* �ж����ȼ� */
	.ucSubPriority								= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable							= true,						/* DMA����ʹ�� */
	.tRxInfo.usDMARxMAXSize             		= 100,              		/* DMA���ջ�������С ��С������Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable							= true,						/* DMA����ʹ�� */
	.tTxInfo.usDMATxMAXSize						= 150,						/* DMA���ͻ�������С */
};

/* JY901S�������� */
tagJY901_T JY901S = 
{
	.tConfig.ucBaud 	= JY901_RXBAUD_9600,
	.tConfig.ucRate		= JY901_RX_2HZ,
	.tConfig.usType		= JY901_OUTPUT_ANGLE | JY901_OUTPUT_MAG | JY901_OUTPUT_ACCEL | JY901_OUTPUT_GYRO,

	.tUART.tRxInfo.usDMARxMAXSize             	= 200,                 /* �������ݳ��� ���ȱ�����Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

    .tUART.tUartDMA.bRxEnable					= true,					/* DMA����ʹ�� */
};

/* ����3 ���ߵ�̨ */
tagUART_T Uart3 = 
{
	//���ڹ���ģʽ����
	.tUARTHandle.Instance 						= USART3,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   				= 9600,						/* ���ڲ����� */

	.ucPriority									= 1,						/* �ж����ȼ� */
	.ucSubPriority								= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable							= true,						/* DMA����ʹ�� */
	.tRxInfo.usDMARxMAXSize             		= 100,              		/* DMA���ջ�������С ��С������Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable							= true,						/* DMA����ʹ�� */
	.tTxInfo.usDMATxMAXSize						= 150,						/* DMA���ͻ�������С */
};

/* ����4 I.MX6ull */
tagUART_T Uart4 = 
{
	//���ڹ���ģʽ����
	.tUARTHandle.Instance 						= UART4,					/* STM32 �����豸 */
	.tUARTHandle.Init.BaudRate   				= 115200,					/* ���ڲ����� */

	.ucPriority									= 1,						/* �ж����ȼ� */
	.ucSubPriority								= 3,						/* �ж������ȼ� */
	
	//����DMA���ղ�������
	.tUartDMA.bRxEnable							= true,						/* DMA����ʹ�� */
	.tRxInfo.usDMARxMAXSize             		= 200,              		/* DMA���ջ�������С ��С������Э����ֽ�*2���ϣ�ȷ�������һ���ܹ��ȶ�����һ������������֡*/

	//����DMA���Ͳ�������
	.tUartDMA.bTxEnable							= true,						/* DMA����ʹ�� */
	.tTxInfo.usDMATxMAXSize						= 150,						/* DMA���ͻ�������С */
};

/* ADоƬ���� */
tagAD24BIT_T AD4111_1 =
{
	.tSPI.tSPIHandle.Instance 		    = SPI2,		
    .tSPI.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_13,				/* GPIO���� ,SPI2_SCK*/
	.tSPI.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO���� */	
	.tSPI.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_15,				/* GPIO���� ,SPI2_MOSI*/
	.tSPI.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO���� */	
	.tSPI.tGPIO[2].tGPIOInit.Pin 		= GPIO_PIN_14,				/* GPIO���� ,SPI2_MISO*/
	.tSPI.tGPIO[2].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[2].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[2].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[2].tGPIOPort 			= GPIOB,					/* GPIO���� */		
    .tSPI.tGPIO[3].tGPIOInit.Pin 		= GPIO_PIN_12,				/* GPIO���� ,CS*/
	.tSPI.tGPIO[3].tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tSPI.tGPIO[3].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[3].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[3].tGPIOPort 			= GPIOB,					/* GPIO���� */	
	.port_num = 8,  //�����Ķ˿��������������õĶ˿ڶ�Ӧ����
	.port[0].enable = PORT_ENABLE,//�˿�ʹ��
	.port[0].num = VIN0,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[0].gain = 1.001648338,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[0].offset= 0.000936992, //У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[1].enable = PORT_ENABLE,
	.port[1].num = VIN1,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[1].gain = 1.00148387,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[1].offset= 0.002501957,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;	
	.port[2].enable = PORT_ENABLE,
	.port[2].num = VIN2,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[2].gain = 1.0,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[2].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[3].enable = PORT_ENABLE,//�˿�ʹ��
	.port[3].num = VIN3,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[3].gain = 1.0,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[3].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[4].enable = PORT_ENABLE,
	.port[4].num = VIN4,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[4].gain = 1.001571984,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[4].offset= 0.001703874,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;	
	.port[5].enable = PORT_ENABLE,
	.port[5].num = VIN5,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[5].gain = 1.001649837,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[5].offset= 0.001140979,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
    .port[6].enable = PORT_ENABLE,
	.port[6].num = VIN6,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[6].gain = 1.001620507,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[6].offset= 0.001374424,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
    .port[7].enable = PORT_ENABLE,
	.port[7].num = VIN7,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[7].gain = 1.001448878,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[7].offset= 0.00172139,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
};

/* ADоƬ���� */
tagAD24BIT_T AD4111_2 =
{
	.tSPI.tSPIHandle.Instance 		    = SPI3,		
    .tSPI.tGPIO[0].tGPIOInit.Pin 		= GPIO_PIN_3,				/* GPIO���� ,SPI3_SCK*/
	.tSPI.tGPIO[0].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[0].tGPIOPort 			= GPIOB,					/* GPIO���� */	
	.tSPI.tGPIO[1].tGPIOInit.Pin 		= GPIO_PIN_5,				/* GPIO���� ,SPI3_MOSI*/
	.tSPI.tGPIO[1].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[1].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[1].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[1].tGPIOPort 			= GPIOB,					/* GPIO���� */	
	.tSPI.tGPIO[2].tGPIOInit.Pin 		= GPIO_PIN_4,				/* GPIO���� ,SPI3_MISO*/
	.tSPI.tGPIO[2].tGPIOInit.Mode 		= GPIO_MODE_AF_PP,			/* GPIOģʽ */
	.tSPI.tGPIO[2].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[2].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[2].tGPIOPort 			= GPIOB,					/* GPIO���� */		
    .tSPI.tGPIO[3].tGPIOInit.Pin 		= GPIO_PIN_7,				/* GPIO���� ,SPI3_CS*/
	.tSPI.tGPIO[3].tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tSPI.tGPIO[3].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tSPI.tGPIO[3].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tSPI.tGPIO[3].tGPIOPort 			= GPIOD,					/* GPIO���� */	
	.port_num = 8,  //�����Ķ˿��������������õĶ˿ڶ�Ӧ����
	.port[0].enable = PORT_ENABLE,//�˿�ʹ��
	.port[0].num = VIN0,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[0].gain = 1.001566898,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[0].offset= 0.002822938,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[1].enable = PORT_ENABLE,
	.port[1].num = VIN1,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[1].gain = 1.001477404,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[1].offset= 0.002462209,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;	
	.port[2].enable = PORT_ENABLE,
	.port[2].num = VIN2,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[2].gain = 1.0,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[2].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[3].enable = PORT_ENABLE,//�˿�ʹ��
	.port[3].num = VIN3,  //�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[3].gain = 1.0,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[3].offset= 0.0,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[4].enable = PORT_ENABLE,
	.port[4].num = VIN4,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[4].gain = 1.001607121,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[4].offset= 0.002711971,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;	
	.port[5].enable = PORT_ENABLE,
	.port[5].num = VIN5,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[5].gain = 1.001525822,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[5].offset= 0.00250732,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
    .port[6].enable = PORT_ENABLE,
	.port[6].num = VIN6,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[6].gain = 1.001581494,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[6].offset= 0.003163044,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
    .port[7].enable = PORT_ENABLE,
	.port[7].num = VIN7,	//�ɼ��źŵ�,����ģʽ���źŵĵؽ�Vincom�˿�;���ģʽ���źŽӶ�Ӧ�˿�
	.port[7].gain = 1.00152087,  //У����������Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
	.port[7].offset= 0.002486376,//У������ƫ����Y =  gain*X+offset,������ҪУ����Ĭ��gain = 1.0,offset = 0.0;
};

tagPWM_T PWM[] =
{
	[0] =       //A1
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_0,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOB,			/* IO��ӳ�� */
	},
	[1] =       //A2
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_1,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOB,			/* IO��ӳ�� */
	},
	[2] =       //B1
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOE,			/* IO��ӳ�� */
	},
	[3] =       //B2
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOE,			/* IO��ӳ�� */
	},
	[4] =       //C1
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_12,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
	},
	[5] =       //C2
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_13,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
	},
	[6] =       //D1
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_14,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
	},
	[7] =       //D2
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_15,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOD,			/* IO��ӳ�� */
	},
	[8] =       //SB-2
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_6,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
	},
	[9] =       //SB-3
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_7,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
	},
	[10] =      //SB-1
	{
		.fDuty					= 7.5,				/* ��ʼռ�ձȣ�%�� */
		.ulFreq					= 50,				/* Ƶ�ʣ�Hz�� */
        .tGPIO.tGPIOInit.Pin	= GPIO_PIN_8,		/* IOӳ�� */
		.tGPIO.tGPIOPort		= GPIOC,			/* IO��ӳ�� */
	},
};

/* MS5837���*/
tagMS5837_T MS5837 = 
{
	.setOSR = MS5837_OSR4096,
	
	/* SCL�� */
	.tIIC.tIICSoft[0].tGPIOInit.Pin 		= GPIO_PIN_9,				/* GPIO���� */
	.tIIC.tIICSoft[0].tGPIOInit.Mode 		= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tIIC.tIICSoft[0].tGPIOInit.Pull 		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[0].tGPIOInit.Speed 		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[0].tGPIOPort 			= GPIOC,					/* GPIO���� */

	/* SDA�� */
	.tIIC.tIICSoft[1].tGPIOInit.Pin 		= GPIO_PIN_8,				/* GPIO���� */
	.tIIC.tIICSoft[1].tGPIOInit.Mode		= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tIIC.tIICSoft[1].tGPIOInit.Pull		= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIIC.tIICSoft[1].tGPIOInit.Speed		= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIIC.tIICSoft[1].tGPIOPort 			= GPIOA,					/* GPIO���� */
};

/* DS1337Ƭ��RTC */
tagDS3231_T DS1337 = 
{
	/* SCL�� */
	.tIICSoft.tIICSoft[0].tGPIOInit.Pin 	= GPIO_PIN_5,				/* GPIO���� */
	.tIICSoft.tIICSoft[0].tGPIOInit.Mode 	= GPIO_MODE_OUTPUT_PP,		/* GPIOģʽ */
	.tIICSoft.tIICSoft[0].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIICSoft.tIICSoft[0].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIICSoft.tIICSoft[0].tGPIOPort 		= GPIOE,					/* GPIO���� */
	
	/* SDA�� */
	.tIICSoft.tIICSoft[1].tGPIOInit.Pin 	= GPIO_PIN_4,				/* GPIO���� */
	.tIICSoft.tIICSoft[1].tGPIOInit.Mode 	= GPIO_MODE_INPUT,			/* GPIOģʽ */
	.tIICSoft.tIICSoft[1].tGPIOInit.Pull 	= GPIO_NOPULL,				/* GPIO���������ã��Ƿ���Ҫ��������Ӳ�� */
	.tIICSoft.tIICSoft[1].tGPIOInit.Speed 	= GPIO_SPEED_FREQ_HIGH,		/* GPIO�ٶ� */	
	.tIICSoft.tIICSoft[1].tGPIOPort 		= GPIOE,					/* GPIO���� */
};

