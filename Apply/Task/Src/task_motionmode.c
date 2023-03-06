#include "task_conf.h"

#include "config.h"

/*  
  <—— <—— <——       4          1                P1 = 0.5 * P *cos(θ+45°)
 |           |                                  P2 = 0.5 * P *cos(θ-225°)
 |           |                      -->         P3 = 0.5 * P *cos(θ-135°)
 |           |                                  P4 = 0.5 * P *cos(θ-45°)
  ——> ——> ——>       3          2 
 */

/**
 * @brief 水平航向计算
 * @param Pro 总推进力    P的范围为[0,560]    经测试最大占空比为8.9(1780hz)，最小占空比为6(1200hz)
 * @param θ 与X轴的夹角 θ为[0,2*pi)
 * @retval Pout 存放四个推进器的分量数组的首地址
*/
float *Task_Horizontal_Heading_Calculation(uint16_t Pro,float θ)
{
    static float Pout[4];
    if(0 < Pro <= 560)
    {
        Pout[0] = 0.5*Pro*cos(θ+PI/4);     //P1的推进力
        Pout[1] = 0.5*Pro*cos(θ-5*PI/4);    //P2的推进力
        //Pout[2] = 0.5*Pro*cos((θ-135)*pi/180);    //P3的推进力
        //Pout[3] = 0.5*Pro*cos((θ-45)*pi/180);     //P4的推进力
        Pout[2] = -Pout[0];
        Pout[3] = -Pout[1];
    }
    return Pout;
}

/**
 * @brief 处理PS2手柄左右摇杆数据，计算推进力与角度，给推进器赋值
 * @param L_Diff 左摇杆偏差
 * @param R_Diff 右摇杆偏差
 * @retval NULL
*/
void Task_Motion_Process(int L_Diff,int R_Diff)
{
    float angle = 0.0;	    //角度
	float Pro   = 0.0;		//推进力
	float *Pout = NULL;	    //存放四个推进器推力的指针

    angle = atan2(R_Diff,L_Diff);
	Pro = sqrt(R_Diff*R_Diff+L_Diff*L_Diff);
	Pout = Task_Horizontal_Heading_Calculation(Pro,angle);

	printf("angle %f Pro %f \r\n",angle,Pro);

	Task_Motor_SpeedSet(1,(uint16_t)(*Pout+STOP_PWM_VALUE));
	Task_Motor_SpeedSet(2,(uint16_t)(*(Pout+1)+STOP_PWM_VALUE));
	Task_Motor_SpeedSet(3,(uint16_t)(*(Pout+2)+STOP_PWM_VALUE));
	Task_Motor_SpeedSet(4,(uint16_t)(*(Pout+3)+STOP_PWM_VALUE));

	printf("M NO.1 %d\r\n",(uint16_t)(*Pout+STOP_PWM_VALUE));
	printf("M NO.2 %d\r\n",(uint16_t)(*(Pout+1)+STOP_PWM_VALUE));
	printf("M NO.3 %d\r\n",(uint16_t)(*(Pout+2)+STOP_PWM_VALUE));
	printf("M NO.4 %d\r\n",(uint16_t)(*(Pout+3)+STOP_PWM_VALUE));
}

uint8_t HOR_FLAG = 0,VER_FLAG = 0;//水平模式标志，竖直模式标志
/**
 * @brief 运动控制函数
 * @param PS2_LY 左摇杆模拟量
 * @param PS2_RX 右摇杆模拟量
 * @param PS2_KEY 键值
 * @retval NULL
*/
void Task_Motioncontrol(int PS2_LY,int PS2_RX,int PS2_KEY)
{
    int LY_Diff = 127 - PS2_LY;//左摇杆与初始值的差，前为正，后为负
	int RX_Diff = 128 - PS2_RX;//右摇杆与初始值的差，左为正，右为负
	int threshold = 2; 	//门限值，防止启动抖动

	if(PS2_KEY == 0)//判断键值，防止对其他模式的干扰
	{
		if(LY_Diff == 0)//左摇杆无动作
		{
			printf("M STOP!\r\n");
			Task_Motor_AllStop();
			//标志位清零
			HOR_FLAG = 0;
			VER_FLAG = 0;
		}
		if(LY_Diff > threshold || LY_Diff < -threshold)//左摇杆有动作
		{
			if(LY_Diff>0&&RX_Diff == 0)//按照模拟量前进
			{
				if(HOR_FLAG==0)//如果不是水平模式
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff == 0)//按照模拟量后退
			{
				if(HOR_FLAG==0)
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff>0&&RX_Diff>0)//前进同时左转，按照夹角给油门
			{
				if(HOR_FLAG==0)//如果不是水平模式
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO and LEFT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff>0&&RX_Diff<0)//前进同时右转，按照夹角给油门
			{
				if(HOR_FLAG==0)//如果不是水平模式
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO and RIGHT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff>0)//后退同时左转，按照夹角给油门
			{
			if(HOR_FLAG==0)//如果不是水平模式
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK and LEFT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff<0)//后退同时右转，按照夹角给油门
			{
				if(HOR_FLAG==0)//如果不是水平模式
				{
					Task_AllSteer_0Angle();
					//printf("进入水平模式\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK and RIGHT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
		}
	}
	else if(PS2_KEY == PSB_L2)//垂直上升模式
	{
		if(VER_FLAG==0)//如果不是垂直模式
		{
			Task_AllSteer_90Angle();
            VER_FLAG = 1;
		}
		Task_Motor_AllSpeedSet(1550);
		printf("M Come-Up!\r\n");
	}
	else if(PS2_KEY == PSB_R2)//垂直下沉模式
	{
		if(VER_FLAG==0)//如果不是垂直模式
		{
			Task_AllSteer_90Angle();
            VER_FLAG = 1;
		}
		Task_Motor_AllSpeedSet(1450);
		printf("M Dive!\r\n");
	}
	else if(PS2_KEY == PSB_PAD_UP)//满输出前进
	{
        if(HOR_FLAG==0)//如果不是水平模式
		{
			Task_AllSteer_0Angle();
			//printf("进入水平模式\r\n");
			HOR_FLAG = 1;
		}
		printf("M PowerMAX GO!\r\n");
		Task_Motor_SpeedSet(1,1544);
		Task_Motor_SpeedSet(2,1455);
		Task_Motor_SpeedSet(3,1455);
		Task_Motor_SpeedSet(4,1544);

		printf("M NO.1 %d\r\n",1544);
		printf("M NO.2 %d\r\n",1455);
		printf("M NO.3 %d\r\n",1455);
		printf("M NO.4 %d\r\n",1544);
	}
	else if(PS2_KEY == PSB_PAD_DOWN)//满输出后退
	{
        if(HOR_FLAG==0)//如果不是水平模式
		{
			Task_AllSteer_0Angle();
			//printf("进入水平模式\r\n");
			HOR_FLAG = 1;
		}
		printf("M PowerMAX GO!\r\n");
		Task_Motor_SpeedSet(1,1454);
		Task_Motor_SpeedSet(2,1545);
		Task_Motor_SpeedSet(3,1545);
		Task_Motor_SpeedSet(4,1454);

		printf("M NO.1 %d\r\n",1454);
		printf("M NO.2 %d\r\n",1545);
		printf("M NO.3 %d\r\n",1545);
		printf("M NO.4 %d\r\n",1454);
	}
	else if(PS2_KEY == PSB_PAD_LEFT)//原地左转90度
	{
		printf("M Turn left in place!\r\n");
	}
	else if(PS2_KEY == PSB_PAD_RIGHT)//原地右转90度
	{
		printf("M Turn right in place!\r\n");
	}
}
