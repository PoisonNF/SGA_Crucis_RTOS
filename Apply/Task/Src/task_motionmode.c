#include "task_conf.h"

#include "bsp_io.h"

/*  
  <���� <���� <����       4          1                P1 = 0.5 * P *cos(��+45��)
 |           |                                  P1 = 0.5 * P *cos(��-225��)
 |           |                      -->         P1 = 0.5 * P *cos(��-135��)
 |           |                                  P1 = 0.5 * P *cos(��-45��)
  ����> ����> ����>       3          2 
 */

/**
 * @brief ˮƽ�������
 * @param Pro ���ƽ���    P�ķ�ΧΪ[0,560]    ���������ռ�ձ�Ϊ8.9(1780hz)����Сռ�ձ�Ϊ6(1200hz)
 * @param �� ��X��ļн� ��Ϊ[0,360)
 * @retval Pout ����ĸ��ƽ����ķ���������׵�ַ
*/
float *Task_Horizontal_Heading_Calculation(uint16_t Pro,int ��)
{
    static float Pout[4];
    if(0 < Pro <= 560 && 0 < �� < 360)
    {
        Pout[0] = 0.5*Pro*cos((��+45)*pi/180);     //P1���ƽ���
        Pout[1] = 0.5*Pro*cos((��-225)*pi/180);    //P2���ƽ���
        //Pout[2] = 0.5*Pro*cos((��-135)*pi/180);    //P3���ƽ���
        //Pout[3] = 0.5*Pro*cos((��-45)*pi/180);     //P4���ƽ���
        Pout[2] = -Pout[0];
        Pout[3] = -Pout[1];
    }
    return Pout;
}

/**
 * @brief ��ֱ�˶�ģʽ
 * @param Pro �ƽ��� Pro>0 ���� Pro<0 �³�    
 * @retval NULL
*/
void Task_Vertical_Mode(uint8_t Pro)
{
    //�Ƚ��ĸ�����ָ���90�ȷ���
    Task_Steer_90Angle(1);
    Task_Steer_90Angle(2);
    Task_Steer_90Angle(3);
    Task_Steer_90Angle(4);
    //����ȡ�����ƽ������ƽ�����
    Task_Motor_SpeedSet(1,STOP_PWM_VALUE + Pro/4*100);
    Task_Motor_SpeedSet(2,STOP_PWM_VALUE + Pro/4*100);
    Task_Motor_SpeedSet(3,STOP_PWM_VALUE + Pro/4*100);
    Task_Motor_SpeedSet(4,STOP_PWM_VALUE + Pro/4*100);
    //����1s
    Drv_Delay_Ms(1000);
    //�ر������ƽ���
    Task_Motor_AllStop();

}

