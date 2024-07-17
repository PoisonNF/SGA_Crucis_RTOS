#include "task_jy901.h"

/**
 * @brief JY901������
 * @param Null
 */
void Task_JY901_Handle(void)
{
    //�����ȡ���ź�����˵�����յ�����
	if(rt_sem_take(JY901S_Sem,RT_WAITING_FOREVER) == RT_EOK)
	{
        //����ɹ������������
		if(OCD_JY901_DataProcess(&JY901S))
        {
            //����ת��
            OCD_JY901_DataConversion(&JY901S);
            //��ӡŷ����
            if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    
                printf("J Angle %.3f %.3f %.3f\r\n",
                        JY901S.stcAngle.ConRoll,
                        JY901S.stcAngle.ConPitch,
                        JY901S.stcAngle.ConYaw);
            
            //�����ݷ��뱨�����ݻ�����
            memcpy(&ReportDataBuffer[ANGLE_BASE],&JY901S.stcAngle.ConRoll,FLOAT_SIZE);
            memcpy(&ReportDataBuffer[ANGLE_BASE + FLOAT_SIZE],&JY901S.stcAngle.ConPitch,FLOAT_SIZE);
            memcpy(&ReportDataBuffer[ANGLE_BASE + 2 * FLOAT_SIZE],&JY901S.stcAngle.ConYaw,FLOAT_SIZE);
        }
	}
}


