#include "usercode.h"
#include "drv_hal_conf.h"
#include "task_conf.h"
#include "bsp_io.h"

/* ÓÃ»§Âß¼­´úÂë */
void UserLogic_Code(void)
{
  
    Task_Motor_Init();
	Task_Steer_Init();

	float *p;
	p = Task_Horizontal_Heading_Calculation(4,75);
	printf("%f , %f, %f, %f\r\n",*p,*(p+1),*(p+2),*(p+3));
	Task_Motor_Start(1,*p+7.5);
	Task_Motor_Start(2,*(p+1)+7.5);
	Task_Motor_Start(3,*(p+2)+7.5);
	Task_Motor_Start(4,*(p+3)+7.5);

	
	//Task_Motor_Start(1,6);
	//Task_Motor_Start(2,6);
	//Task_Motor_Start(3,6);
	//Task_Motor_Start(4,6);

	Drv_Delay_Ms(3000);

	Task_Motor_Stop(1);
	Task_Motor_Stop(2);
	Task_Motor_Stop(3);
	Task_Motor_Stop(4);



	while(1)
	{
		
		

	}
}
