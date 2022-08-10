#include "task_conf.h"

#include "bsp_io.h"

void Task_Motor_Init(void)
{
	Drv_Delay_Ms(2000);		/* 初始停转信号后等待稳定 */
	
	/* 正转满油门，10%占空比 */
	Drv_PWM_DutyfactorSet(&tPWMDemo[0], 10);
	Drv_Delay_Ms(2000);
	
	/* 反转满油门，5%占空比 */
	Drv_PWM_DutyfactorSet(&tPWMDemo[0], 5);
	Drv_Delay_Ms(2000);
	
	/* 停转，7.5%占空比 */
	Drv_PWM_DutyfactorSet(&tPWMDemo[0], 7.5);
	Drv_Delay_Ms(4000);
}

/* 电机转速设置 */
/*_fVal可设置为2.5-12.5，7.5停止
	2.5-7.5 逆时针旋转 7.5-12.5 顺时针旋转
*/
void Task_Motor_SpeedSet(int index,float _fVal)
{
	Drv_PWM_DutyfactorSet(&tPWMDemo[index-1], _fVal);
	//Drv_Delay_Ms(3000);			/* 测试转动3S */
}	

/* 电机工作 */
void Task_Motor_Start(int index,float _fVal)
{
	/* 电机停转 */
	Task_Motor_SpeedSet(index,_fVal);
}

/* 电机停转 */
void Task_Motor_Stop(int index)
{
	/* 电机停转 */
	Drv_PWM_DutyfactorSet(&tPWMDemo[index-1], 7.5);
}
