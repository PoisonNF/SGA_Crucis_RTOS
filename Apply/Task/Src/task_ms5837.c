#include "task_ms5837.h"

/**
 * @brief MS5837������
 * @param Null
 */
void Task_MS5837_Handle(void)
{
    OCD_MS5837_GetData(&MS5837);
    if(MS5837.fDepth == 153150.250000)  //δ��MS5837�Ĵ�������
        MS5837.fDepth = 0;
#ifdef DEBUG_PRINTF
    printf("M %0.2f\r\n",MS5837.fDepth);
#endif
    memcpy(&ReportDataBuffer[DEPTH_BASE],&MS5837.fDepth,FLOAT_SIZE);
}


