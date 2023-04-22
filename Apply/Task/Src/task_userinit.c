#include "task_conf.h"
#include "config.h"

void Task_UserInit(void)
{
	//Drv_GPIO_Init(GPIO,2);
    //Drv_GPIO_Set(&GPIO[0]);
    //Drv_GPIO_Set(&GPIO[1]);

    Drv_GPIO_Init(&U4485Ctrl,1);
    //RS485控制IO常闭
    Drv_GPIO_Set(&U4485Ctrl);

    Drv_Uart_DMAInit(&Uart1);
    printf("UART1 DMA INIT!\r\n");

    OCD_JY901_DMAInit(&JY901S);
    printf("JY901S INIT!\r\n");

    Drv_Uart_DMAInit(&Uart3);
    printf("UART3 DMA INIT!\r\n");

    Drv_Uart_DMAInit(&Uart4);
    printf("UART4 IT INIT!\r\n");

    Drv_Uart_ITInit(&OpenMV);
    printf("OpenMV IT INIT!\r\n");
    
    Drv_PWM_Init(PWM,8);
    printf("PWM INIT!\r\n");
    
    //OCD_OLED_Init(&OLED);
    //printf("OLED INIT!\r\n");

    //Drv_ADC_Init(&demoADC,1);

    OCD_RM3100_Init(RM3100,4);
    printf("RM3100 INIT!\r\n");

    Dev_PS2_Init(&PS2);
    printf("PS2 INIT!\r\n");

    Task_Motor_Init();//推机器初始化
    Task_Steer_Init();//舵机初始化
}

