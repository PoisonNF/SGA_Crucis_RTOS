#include "task_conf.h"

#include "config.h"

/*  
  <���� <���� <����       4          1                P1 = 0.5 * P *cos(��+45��)
 |           |                                  P2 = 0.5 * P *cos(��-225��)
 |           |                      -->         P3 = 0.5 * P *cos(��-135��)
 |           |                                  P4 = 0.5 * P *cos(��-45��)
  ����> ����> ����>       3          2 
 */

/**
 * @brief ˮƽ�������
 * @param Pro ���ƽ���    P�ķ�ΧΪ[0,560]    ���������ռ�ձ�Ϊ8.9(1780hz)����Сռ�ձ�Ϊ6(1200hz)
 * @param �� ��X��ļн� ��Ϊ[0,2*pi)
 * @retval Pout ����ĸ��ƽ����ķ���������׵�ַ
*/
float *Task_Horizontal_Heading_Calculation(uint16_t Pro,float ��)
{
    static float Pout[4];
    if(0 < Pro <= 560)
    {
        Pout[0] = 0.5*Pro*cos(��+PI/4);     //P1���ƽ���
        Pout[1] = 0.5*Pro*cos(��-5*PI/4);    //P2���ƽ���
        //Pout[2] = 0.5*Pro*cos((��-135)*pi/180);    //P3���ƽ���
        //Pout[3] = 0.5*Pro*cos((��-45)*pi/180);     //P4���ƽ���
        Pout[2] = -Pout[0];
        Pout[3] = -Pout[1];
    }
    return Pout;
}

/**
 * @brief ����PS2�ֱ�����ҡ�����ݣ������ƽ�����Ƕȣ����ƽ�����ֵ
 * @param L_Diff ��ҡ��ƫ��
 * @param R_Diff ��ҡ��ƫ��
 * @retval NULL
*/
void Task_Motion_Process(int L_Diff,int R_Diff)
{
    float angle = 0.0;	    //�Ƕ�
	float Pro   = 0.0;		//�ƽ���
	float *Pout = NULL;	    //����ĸ��ƽ���������ָ��

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

uint8_t HOR_FLAG = 0,VER_FLAG = 0;//ˮƽģʽ��־����ֱģʽ��־
/**
 * @brief �˶����ƺ���
 * @param PS2_LY ��ҡ��ģ����
 * @param PS2_RX ��ҡ��ģ����
 * @param PS2_KEY ��ֵ
 * @retval NULL
*/
void Task_Motioncontrol(int PS2_LY,int PS2_RX,int PS2_KEY)
{
    int LY_Diff = 127 - PS2_LY;//��ҡ�����ʼֵ�ĲǰΪ������Ϊ��
	int RX_Diff = 128 - PS2_RX;//��ҡ�����ʼֵ�Ĳ��Ϊ������Ϊ��
	int threshold = 2; 	//����ֵ����ֹ��������

	if(PS2_KEY == 0)//�жϼ�ֵ����ֹ������ģʽ�ĸ���
	{
		if(LY_Diff == 0)//��ҡ���޶���
		{
			printf("M STOP!\r\n");
			Task_Motor_AllStop();
			//��־λ����
			HOR_FLAG = 0;
			VER_FLAG = 0;
		}
		if(LY_Diff > threshold || LY_Diff < -threshold)//��ҡ���ж���
		{
			if(LY_Diff>0&&RX_Diff == 0)//����ģ����ǰ��
			{
				if(HOR_FLAG==0)//�������ˮƽģʽ
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff == 0)//����ģ��������
			{
				if(HOR_FLAG==0)
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff>0&&RX_Diff>0)//ǰ��ͬʱ��ת�����ռнǸ�����
			{
				if(HOR_FLAG==0)//�������ˮƽģʽ
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO and LEFT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff>0&&RX_Diff<0)//ǰ��ͬʱ��ת�����ռнǸ�����
			{
				if(HOR_FLAG==0)//�������ˮƽģʽ
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M GO and RIGHT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff>0)//����ͬʱ��ת�����ռнǸ�����
			{
			if(HOR_FLAG==0)//�������ˮƽģʽ
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK and LEFT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
			else if(LY_Diff<0&&RX_Diff<0)//����ͬʱ��ת�����ռнǸ�����
			{
				if(HOR_FLAG==0)//�������ˮƽģʽ
				{
					Task_AllSteer_0Angle();
					//printf("����ˮƽģʽ\r\n");
					HOR_FLAG = 1;
				}
				printf("M BACK and RIGHT!\r\n");
				Task_Motion_Process(LY_Diff,RX_Diff);
			}
		}
	}
	else if(PS2_KEY == PSB_L2)//��ֱ����ģʽ
	{
		if(VER_FLAG==0)//������Ǵ�ֱģʽ
		{
			Task_AllSteer_90Angle();
            VER_FLAG = 1;
		}
		Task_Motor_AllSpeedSet(1550);
		printf("M Come-Up!\r\n");
	}
	else if(PS2_KEY == PSB_R2)//��ֱ�³�ģʽ
	{
		if(VER_FLAG==0)//������Ǵ�ֱģʽ
		{
			Task_AllSteer_90Angle();
            VER_FLAG = 1;
		}
		Task_Motor_AllSpeedSet(1450);
		printf("M Dive!\r\n");
	}
	else if(PS2_KEY == PSB_PAD_UP)//�����ǰ��
	{
        if(HOR_FLAG==0)//�������ˮƽģʽ
		{
			Task_AllSteer_0Angle();
			//printf("����ˮƽģʽ\r\n");
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
	else if(PS2_KEY == PSB_PAD_DOWN)//���������
	{
        if(HOR_FLAG==0)//�������ˮƽģʽ
		{
			Task_AllSteer_0Angle();
			//printf("����ˮƽģʽ\r\n");
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
	else if(PS2_KEY == PSB_PAD_LEFT)//ԭ����ת90��
	{
		printf("M Turn left in place!\r\n");
	}
	else if(PS2_KEY == PSB_PAD_RIGHT)//ԭ����ת90��
	{
		printf("M Turn right in place!\r\n");
	}
}
