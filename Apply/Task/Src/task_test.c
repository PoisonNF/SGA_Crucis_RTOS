#include "task_test.h"

static uint8_t Uart3_ReceiveBuffer[100] = {0};        //���ڲ��Դ���3
static uint8_t Uart3_ReceiveNum = 0;

/**
 * @brief ר���ڲ��Դ���3���ߵ�̨�ĺ���
 * @param Null
 */
static void S_Test_Uart3_Function(void)
{
    Uart3_ReceiveNum = Drv_Uart_Receive_DMA(&Uart3,Uart3_ReceiveBuffer);
    if(Uart3_ReceiveNum != 0)
    {
        Drv_Uart_Transmit(&Uart3,Uart3_ReceiveBuffer,Uart3_ReceiveNum);
        Uart3_ReceiveNum = 0;
    }
}

/**
 * @brief AD4111���ݲɼ�����
 * @param Null
 */
static void S_AD_Acquisition(tagAD24BIT_T* device)
{
    uint8_t ret;
    double V0,V1,V2,V3,V4,V5,V6,V7;

	ret = OCD_AD24bit_GetResult(device, 200);
	if(ret != 0)
	{
	    DBG_ERROR("OCD_AD24bit_GetResult error:%d\r\n",ret);
	}
    
	V0 = device->port[0].result;
	V1 = device->port[1].result;
	V2 = device->port[2].result;
	V3 = device->port[3].result;
	V4 = device->port[4].result;
	V5 = device->port[5].result;
    V6 = device->port[6].result;
    V7 = device->port[7].result;
    
    printf("V0 %f V1 %f V2 %f\r\n",V0,V1,V2);
    printf("V3 %f V4 %f V5 %f\r\n",V3,V4,V5);
    printf("V6 %f V7 %f\r\n\r\n",V6,V7); 
}

/**
 * @brief ר���ڲ���AD4111�ĺ���
 * @param Null
 */
static void S_Test_AD4111_Function(void)
{
    printf("AD4111_1\r\n");
    S_AD_Acquisition(&AD4111_1);
    printf("AD4111_2\r\n");
    S_AD_Acquisition(&AD4111_2);
	Drv_Delay_Ms(1000);
}

/**
 * @brief ר���ڲ���MS5837�ĺ���
 * @param Null
 */
static void S_Test_MS5837_Function(void)
{
    //��ȡMS5837�¶Ⱥ�ѹ������
	OCD_MS5837_GetData(&MS5837);

	//��ӡ�������
	printf("Temp1:%.2fC Press1:%.2fmBar\r\n",MS5837.fTemp1,MS5837.fPress1);
	printf("Temp:%.2fC Press:%.2fmBar\r\n",MS5837.fTemp2,MS5837.fPress2);
	printf("%.2fcm\r\n\r\n",MS5837.fDepth);
}

/**
 * @brief ר���ڲ���JY901S�ĺ���
 * @param Null
 */
static void S_Test_JY901S_Function(void)
{
    //����ɹ������������
	if(OCD_JY901_DataProcess(&JY901S))
    {
        //����ת��
        OCD_JY901_DataConversion(&JY901S);
        //��ӡŷ����
        if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    
            printf("J Angle %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcAngle.ConRoll,
                    JY901S.stcAngle.ConPitch,
                    JY901S.stcAngle.ConYaw);
        if(JY901S.tConfig.usType & JY901_OUTPUT_MAG)	    
            printf("J Mag %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcMag.ConMagX,
                    JY901S.stcMag.ConMagY,
                    JY901S.stcMag.ConMagZ);
        if(JY901S.tConfig.usType & JY901_OUTPUT_ACCEL)	    
            printf("J Accel %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcAcc.ConAccX,
                    JY901S.stcAcc.ConAccY,
                    JY901S.stcAcc.ConAccZ);
        if(JY901S.tConfig.usType & JY901_OUTPUT_GYRO)	    
            printf("J Gyro %.3f %.3f %.3f\r\n\r\n",
                    JY901S.stcGyro.ConGyroX,
                    JY901S.stcGyro.ConGyroY,
                    JY901S.stcGyro.ConGyroZ);
    }
}

/**
 * @brief ר���ڲ���DS1337�ĺ���
 * @param Null
 */
static void S_Test_DS1337_Function(void)
{
    tagDS3231Time_T CurrSysTime = {0};

    /* ��ȡ��ǰʱ�� */
    if(OCD_DS3231_TimeGetHex(&DS1337,&CurrSysTime))
    {
        printf("Read Time:");
        printf("20%02x/%02x/%02x %02x:%02x:%02x ��%x\r\n",
                CurrSysTime.ucYear,CurrSysTime.ucMonth,CurrSysTime.ucDate,
                CurrSysTime.ucHour,CurrSysTime.ucMinute,CurrSysTime.ucSecond,
                CurrSysTime.ucWeek);
    }
    Drv_Delay_Ms(1000);    
}

/**
 * @brief ר���ڲ��Ե��ϵͳ�ĺ���
 * @param Null
 */
static void S_Test_Motorsys_Function(void)
{
    //�����ƽ���ת��
    Task_MotorSys_Thruster_SpeedSet(A_1,1550);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(A_1,1500);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(B_1,1550);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(B_1,1500);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(C_1,1550);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(C_1,1500);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(D_1,1550);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Thruster_SpeedSet(D_1,1500);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(A_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(A_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(A_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(B_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(B_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(B_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(C_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(C_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(C_2,180);
    Drv_Delay_Ms(2000);

    Task_MotorSys_Steer_Angle_Set(D_2,0);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(D_2,90);
    Drv_Delay_Ms(2000);
    Task_MotorSys_Steer_Angle_Set(D_2,180);
    Drv_Delay_Ms(2000);

//    Task_MotorSys_AllThruster_SpeedSet(1514);
//    Drv_Delay_Ms(2000);
//    Task_MotorSys_AllThruster_SpeedSet(1500);
}

/**
 * @brief ר���ڲ��Եĺ���
 * @param Null
 */
void Task_Test_Handle(void)
{
    // S_Test_Uart3_Function();

    // S_Test_AD4111_Function();

    // S_Test_MS5837_Function();

    // S_Test_JY901S_Function();

    // S_Test_DS1337_Function();

    S_Test_Motorsys_Function();

}

