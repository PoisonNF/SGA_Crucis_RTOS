#include "task_conf.h"

#include "bsp_io.h"

/*  
  <—— <—— <——       4          1                P1 = 0.5 * P *cos(θ+45°)
 |           |                                  P1 = 0.5 * P *cos(θ-225°)
 |           |                      -->         P1 = 0.5 * P *cos(θ-135°)
 |           |                                  P1 = 0.5 * P *cos(θ-45°)
  ——> ——> ——>       3          2 
 */

/**
 * @brief 水平航向计算
 * @param P 总推进力    P的范围为[0,560]    经测试最大占空比为8.9(1780hz)，最小占空比为6(1200hz)
 * @param θ 与X轴的夹角 θ为[0,360)
 * @retval Pout 存放四个推进器的分量数组的首地址
*/
float *Task_Horizontal_Heading_Calculation(uint16_t P,int θ)
{
    static float Pout[4];
    if(0 < P <= 560 && 0 < θ < 360)
    {
        Pout[0] = 0.5*P*cos((θ+45)*pi/180);     //P1的推进力
        Pout[1] = 0.5*P*cos((θ-225)*pi/180);    //P2的推进力
        //Pout[2] = 0.5*P*cos((θ-135)*pi/180);    //P3的推进力
        //Pout[3] = 0.5*P*cos((θ-45)*pi/180);     //P4的推进力
        Pout[2] = -Pout[0];
        Pout[3] = -Pout[1];
    }
    return Pout;
}



