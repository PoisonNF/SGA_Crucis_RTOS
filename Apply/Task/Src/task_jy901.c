#include "task_jy901.h"

/**
 * @brief JY901处理函数
 * @param Null
 */
void Task_JY901_Handle(void)
{
    //如果获取到信号量，说明接收到数据
	if(rt_sem_take(JY901S_Sem,RT_WAITING_FOREVER) == RT_EOK)
	{
        //如果成功处理完成数据
		if(OCD_JY901_DataProcess(&JY901S))
        {
            //数据转换
            OCD_JY901_DataConversion(&JY901S);
            //打印欧拉角
            if(JY901S.tConfig.usType & JY901_OUTPUT_ANGLE)	    
                printf("J Angle %.3f %.3f %.3f\r\n",
                        JY901S.stcAngle.ConRoll,
                        JY901S.stcAngle.ConPitch,
                        JY901S.stcAngle.ConYaw);
            
            //将数据放入报告数据缓存区
            memcpy(&ReportDataBuffer[ANGLE_BASE],&JY901S.stcAngle.ConRoll,FLOAT_SIZE);
            memcpy(&ReportDataBuffer[ANGLE_BASE + FLOAT_SIZE],&JY901S.stcAngle.ConPitch,FLOAT_SIZE);
            memcpy(&ReportDataBuffer[ANGLE_BASE + 2 * FLOAT_SIZE],&JY901S.stcAngle.ConYaw,FLOAT_SIZE);
        }
	}
}


