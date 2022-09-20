#include "usercode.h"
#include "drv_hal_conf.h"
#include "task_conf.h"
#include "bsp_io.h"

extern tagOLED_T tOLED;
/* ÓÃ»§Âß¼­´úÂë */
void UserLogic_Code(void)
{
	//Task_Motor_Init();
	//Task_Steer_Init();

    // float *p;
	// p = Task_Horizontal_Heading_Calculation(500,30);

    // float num1 = *p,num2 = *(p+1);

	// OCD_OLED_ShowFNum(&tOLED,0,0,num1,16);
    // OCD_OLED_ShowFNum(&tOLED,0,2,num2,16);
    
	// printf("%f\r\n",*p+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+1)+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+2)+STOP_PWM_VALUE);
	// printf("%f\r\n",*(p+3)+STOP_PWM_VALUE);
	PID pid;
	float pidvalue[3] = {0.2,1,0};
	pid.pre_value = 1400;

    printf("pid test\r\n");
    PID_init(&pid,pidvalue);
	for(int i = 0; i<50;i++)
	{
        PID_calc(&pid,pid.pre_value,1500);
		Task_Motor_SpeedSet(1,pid.ctrl_out);
        printf("%f\r\n",pid.ctrl_out);
		Drv_Delay_Ms(100);
		if(pid.pre_value == 1500)	return;
	}


	while(1)
	{
		
	}
}
