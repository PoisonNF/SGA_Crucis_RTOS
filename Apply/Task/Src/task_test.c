#include "task_test.h"

static uint8_t Uart3_ReceiveBuffer[100] = {0};        //���ڲ��Դ���3

/**
 * @brief ר���ڲ��Դ���3���ߵ�̨�ĺ���
 * @param Null
 */
static void S_Test_Uart3_Function(void)
{
    Drv_Uart_Transmit(&Uart3,(uint8_t *)"Uart3",sizeof("Uart3"));

    if(Drv_Uart_Receive_DMA(&Uart3,Uart3_ReceiveBuffer))
    {
        Drv_Uart_Transmit(&Uart3,Uart3_ReceiveBuffer,sizeof(Uart3_ReceiveBuffer));
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
    }
}

/**
 * @brief ר���ڲ��Եĺ���
 * @param Null
 */
void Task_Test_Handle(void)
{
    printf("SGA_TEST\r\n");

    S_Test_Uart3_Function();

    S_Test_AD4111_Function();

    S_Test_MS5837_Function();

    S_Test_JY901S_Function();

    Drv_Delay_Ms(1000);
}
