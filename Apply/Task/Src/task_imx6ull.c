#include "task_imx6ull.h"

static uint8_t IMX6ULL_ReceBuf[100];
static uint8_t IMX6ULL_ReceNum = 0;

static char LongitudeStr[11] = {0};  //�����ַ���
static char LatitudeStr[10] = {0};   //γ���ַ���

static uint8_t StartClpt[] = "StartClpt";     //i.mx6ull�����������ʾ

tagGPSinfo_T GPS;

/**
 * @brief IMX6ULL������
 * @param Null
 */
void Task_IMX6ULL_Handle(void)
{
    IMX6ULL_ReceNum = Drv_Uart_Receive_DMA(&Uart4,IMX6ULL_ReceBuf);
    if(IMX6ULL_ReceNum != 0)
    {
        //Drv_Uart_Transmit(&Uart1,IMX6ULL_ReceBuf,IMX6ULL_ReceNum);

        if(!strcmp((char *)IMX6ULL_ReceBuf,(char *)StartClpt))      //I.MX6ull������ᷢ��StartClpt��ʾ�Լ��������
            printf("I.MX6ull Start\r\n");

        uint8_t ret = 0;
        //�ַ�������
        ret = sscanf((char *)IMX6ULL_ReceBuf,"$GNRMC,%*10[^,],%c,%10s,%c,%11s,%c,%*.1f,%*.1f,%*6d,,,%*4s",
                    &GPS.Status,
                    LatitudeStr,
                    &GPS.NS,  
                    LongitudeStr,
                    &GPS.WE  
        );

        //�ַ���ת��Ϊfloat����
        GPS.Latitude = strtof(LatitudeStr,NULL);
        GPS.Longitude = strtof(LongitudeStr,NULL);

        UNUSED(ret);           
#ifdef DEBUG_PRINTF    
        printf("%d %c %4.5f %c %5.5f %c\n",ret,GPS.Status,GPS.Latitude,GPS.NS,GPS.Longitude,GPS.WE);
#endif
        //��GPS��Ϣ���뱨�滺������
        memcpy(&ReportDataBuffer[GPS_BASE                                    ],&GPS.WE,UINT8_T_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE +     UINT8_T_SIZE                 ],&GPS.Longitude,FLOAT_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE +     UINT8_T_SIZE +     FLOAT_SIZE],&GPS.NS,UINT8_T_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE + 2 * UINT8_T_SIZE +     FLOAT_SIZE],&GPS.Latitude,FLOAT_SIZE);
        memcpy(&ReportDataBuffer[GPS_BASE + 2 * UINT8_T_SIZE + 2 * FLOAT_SIZE],&GPS.Status,UINT8_T_SIZE);

        IMX6ULL_ReceNum = 0;
    }
}
