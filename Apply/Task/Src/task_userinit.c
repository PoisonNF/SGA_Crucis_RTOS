#include "task_conf.h"

#include "bsp_io.h"

extern tagOLED_T tOLED;
void Task_UserInit(void)
{
	Drv_GPIO_Init(demoGPIO, 3);
    
    Drv_Uart_ITInit(&demoUart);
    printf("UART INIT!\r\n");
    Drv_PWM_Init(tPWMDemo,8);
    printf("PWM INIT!\r\n");
    OCD_OLED_Init(&tOLED);
    printf("OLED INIT!\r\n");
}
