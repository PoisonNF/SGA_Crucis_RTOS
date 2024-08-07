#include "task_ds1337.h"

static tagDS3231Time_T CurrSysTime = {0};

/**
 * @brief DS1337������
 * @param Null
 */
void Task_DS1337_Handle(void)
{
    /* ��ȡ��ǰʱ�� */
    if(OCD_DS3231_TimeGetHex(&DS1337,&CurrSysTime))
    {
#ifdef DEBUG_PRINTF
        printf("Read Time:");
        printf("20%02x/%02x/%02x %02x:%02x:%02x ��%x\r\n",
                CurrSysTime.ucYear,CurrSysTime.ucMonth,CurrSysTime.ucDate,
                CurrSysTime.ucHour,CurrSysTime.ucMinute,CurrSysTime.ucSecond,
                CurrSysTime.ucWeek);
#endif
        memcpy(&ReportDataBuffer[DATE_BASE],&CurrSysTime,6 * UINT8_T_SIZE);
    }
}

/**
 * @brief DS1337ʱ��ͬ������
 * @param DateCMD ͬ��ʱ������
 */
void Task_DS1337_SYNC(uint8_t *DateCMD)
{
    tagDS3231Time_T SetSysTime = {0};

    SetSysTime.ucYear   = *(DateCMD + 3);
    SetSysTime.ucMonth  = *(DateCMD + 4);
    SetSysTime.ucDate   = *(DateCMD + 5);
    SetSysTime.ucHour   = *(DateCMD + 6);
    SetSysTime.ucMinute = *(DateCMD + 7);
    SetSysTime.ucSecond = *(DateCMD + 8);

    OCD_DS3231_TimeSetHex(&DS1337,&SetSysTime);
}
