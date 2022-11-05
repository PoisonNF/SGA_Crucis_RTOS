#include "task_conf.h"

#include "bsp_io.h"


/*180°舵机
0.5ms----------------0度；          2.5     500hz
1ms -----------------45度；         5       1000hz
1.5ms----------------90度；         7.5     1500hz
2ms -----------------135度；        10      2000hz
2.5ms ---------------180度          12.5    2500hz  */

/**
 * @brief 舵机初始化函数
 * @param null
 * @retval null
*/
void Task_Steer_Init(void)
{
    Drv_PMW_FreqSet(&tPWMDemo[4],1500);
    Drv_PMW_FreqSet(&tPWMDemo[5],1500);
    Drv_PMW_FreqSet(&tPWMDemo[6],1500);
    Drv_PMW_FreqSet(&tPWMDemo[7],1500);
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
    Drv_PMW_FreqSet(&tPWMDemo[index+3],ang/180*2000+500);
}

/**
 * @brief 舵机定0度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_0Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],500);
}

/**
 * @brief 所有舵机定0度函数
 * @param NULL
 * @retval null
*/
void Task_AllSteer_0Angle(void)
{
    Task_Steer_0Angle(1);
    Task_Steer_0Angle(2);
    Task_Steer_0Angle(3);
    Task_Steer_0Angle(4);
    Drv_Delay_Ms(500);//延时500ms完成转动,延时时间待测试
}

/**
 * @brief 舵机定90度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_90Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],1500);
}

/**
 * @brief 所有舵机定90度函数
 * @param NULL
 * @retval null
*/
void Task_AllSteer_90Angle(void)
{
    Task_Steer_90Angle(1);
    Task_Steer_90Angle(2);
    Task_Steer_90Angle(3);
    Task_Steer_90Angle(4);
    Drv_Delay_Ms(500);//延时500ms完成转动
}

/**
 * @brief 舵机定180度函数
 * @param index 选择几号舵机 
 * @retval null
*/
void Task_Steer_180Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],2500);
}

/**
 * @brief 所有舵机定180度函数
 * @param NULL
 * @retval null
*/
void Task_AllSteer_180Angle(void)
{
    Task_Steer_180Angle(1);
    Task_Steer_180Angle(2);
    Task_Steer_180Angle(3);
    Task_Steer_180Angle(4);
    Drv_Delay_Ms(500);//延时500ms完成转动
}



