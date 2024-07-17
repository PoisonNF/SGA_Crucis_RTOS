#include "task_ad4111.h"

/**
 * @brief AD4111���ݲɼ�����
 * @param Null
 */
void AD_Acquisition(tagAD24BIT_T* device)
{
    uint8_t ret;

	ret = OCD_AD24bit_GetResult(device, 200);
	if(ret != 0)
	{
	    DBG_ERROR("OCD_AD24bit_GetResult error:%d\r\n",ret);
	}

#ifdef DEBUG_PRINTF
    double V0,V1,V2,V3,V4,V5,V6,V7;
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
#endif
}

/**
 * @brief AD4111ͬ������
 * @param Null
 */
void Task_AD4111_Sync(void)
{
    Drv_GPIO_Reset(&SYNC);
    Drv_Delay_Ms(500);
	Drv_GPIO_Set(&SYNC);
}

/**
 * @brief AD4111������
 * @param Null
 */
void Task_AD4111_Handle(void)
{
    AD_Acquisition(&AD4111_1);
    AD_Acquisition(&AD4111_2);

    //�����ݷ��뱨�����ݻ�����
    //�ݶȴ�����1   XYZ
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE                 ],&AD4111_2.port[0].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE +     FLOAT_SIZE],&AD4111_2.port[1].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 2 * FLOAT_SIZE],&AD4111_2.port[4].result,FLOAT_SIZE);

    //�ݶȴ�����2   XYZ
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 3 * FLOAT_SIZE],&AD4111_2.port[5].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 4 * FLOAT_SIZE],&AD4111_2.port[6].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 5 * FLOAT_SIZE],&AD4111_2.port[7].result,FLOAT_SIZE);

    //�ݶȴ�����3   XYZ
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 6 * FLOAT_SIZE],&AD4111_1.port[0].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 7 * FLOAT_SIZE],&AD4111_1.port[1].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 8 * FLOAT_SIZE],&AD4111_1.port[4].result,FLOAT_SIZE);

    //�ݶȴ�����4   XYZ
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 9  * FLOAT_SIZE],&AD4111_1.port[5].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 10 * FLOAT_SIZE],&AD4111_1.port[6].result,FLOAT_SIZE);
    memcpy(&ReportDataBuffer[GRADIENTMAGNET_BASE + 11 * FLOAT_SIZE],&AD4111_1.port[7].result,FLOAT_SIZE);
}


