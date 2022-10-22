#include "task_conf.h"
#include "ocd_conf.h"
#include "bsp_io.h"

void Task_UserInit(void)
{
	Drv_GPIO_Init(demoGPIO, 2);
    Drv_GPIO_Set(&demoGPIO[0]);
    Drv_GPIO_Set(&demoGPIO[1]);

    // Drv_Uart_ITInit(&demoUart);
    // printf("UART INIT!\r\n");

    Drv_Uart_DMAInit(&demoUart1);
    printf("UART1 DMA INIT!\r\n");

    //Drv_Uart_DMAInit(&demoUart2);
    OCD_JY901_DMAInit(&JY901S);
    printf("JY901S INIT!\r\n");

    //Drv_PWM_Init(tPWMDemo,8);
    //printf("PWM INIT!\r\n");
    
    //OCD_OLED_Init(&tOLED);
    //printf("OLED INIT!\r\n");

    //Drv_ADC_Init(&demoADC,1);
}
