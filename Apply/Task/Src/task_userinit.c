#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

/* 外设初始化函数 */
void Task_UserInit(void)
{
    uint8_t ret = 0;

	Drv_GPIO_Init(LED, 3);
    
    Drv_Uart_DMAInit(&Uart1);       /* 初始化串口1 DAP接口 有线RS232接口 */
    OCD_JY901_DMAInit(&JY901S);     /* 初始化JY901S 使用串口2 */
    Drv_Uart_DMAInit(&Uart3);       /* 初始化串口3 无线电台 */
    
    ret = OCD_AD24BIT_Init(&AD4111_1);  /* 24位AD初始化 */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
    ret = OCD_AD24BIT_Init(&AD4111_2);  /* 24位AD初始化 */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //程序报错stop	
	}
    
    Drv_PWM_Init(PWM,11);       /* 初始化PWM */
    
    if(OCD_MS5837_Init(&MS5837) == 0)
        printf("MS5837 error\r\n");
}
