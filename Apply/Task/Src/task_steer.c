#include "task_conf.h"

#include "bsp_io.h"


/*180����
0.5ms----------------0�ȣ�          2.5     500hz
1ms -----------------45�ȣ�         5       1000hz
1.5ms----------------90�ȣ�         7.5     1500hz
2ms -----------------135�ȣ�        10      2000hz
2.5ms ---------------180��          12.5    2500hz  */

/**
 * @brief �����ʼ������
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
 * @brief ���ת�Ǻ���
 * @param index ѡ�񼸺Ŷ�� 
 * @param ang �Ƕȣ�0�ȡ���180�ȣ�
 * @retval null
*/
void Task_Steer_Angle_Set(int index,int ang)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],ang/180*2000+500);
}

/**
 * @brief �����0�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_0Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],500);
}

/**
 * @brief ���ж����0�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_AllSteer_0Angle(void)
{
    Task_Steer_0Angle(1);
    Task_Steer_0Angle(2);
    Task_Steer_0Angle(3);
    Task_Steer_0Angle(4);
    Drv_Delay_Ms(500);//��ʱ500ms���ת��,��ʱʱ�������
}

/**
 * @brief �����90�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_90Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],1500);
}

/**
 * @brief ���ж����90�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_AllSteer_90Angle(void)
{
    Task_Steer_90Angle(1);
    Task_Steer_90Angle(2);
    Task_Steer_90Angle(3);
    Task_Steer_90Angle(4);
    Drv_Delay_Ms(500);//��ʱ500ms���ת��
}

/**
 * @brief �����180�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_Steer_180Angle(int index)
{
    Drv_PMW_FreqSet(&tPWMDemo[index+3],2500);
}

/**
 * @brief ���ж����180�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_AllSteer_180Angle(void)
{
    Task_Steer_180Angle(1);
    Task_Steer_180Angle(2);
    Task_Steer_180Angle(3);
    Task_Steer_180Angle(4);
    Drv_Delay_Ms(500);//��ʱ500ms���ת��
}



