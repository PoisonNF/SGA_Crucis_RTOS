#include "task_conf.h"

#include "bsp_io.h"

/*180°舵机
0.5ms----------------0度；          2.5
1ms -----------------45度；         5
1.5ms----------------90度；         7.5
2ms -----------------135度；        10
2.5ms ---------------180度          12.5      */

/**
 * @brief 舵机初始化函数
 * @param null
 * @retval null
*/
void Task_Steer_Init(void)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[4],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[5],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[6],7.5);
    Drv_PWM_DutyfactorSet(&tPWMDemo[7],7.5);
    Drv_Delay_Ms(200);
}


/**
 * @brief 舵机转角函数
 * @param index 选择几号舵机 
 * @param ang 角度（0度——180度）
 * @retval null
*/
void Task_Steer_Angle_Set(int index,int ang)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],ang*10/180+2.5);
}

/**
 * @brief 舵机定0度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_0Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],2.5);
}

/**
 * @brief 舵机定90度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_90Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],7.5);
}

/**
 * @brief 舵机定180度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_180Angle(int index)
{
    Drv_PWM_DutyfactorSet(&tPWMDemo[index+3],12.5);
}



