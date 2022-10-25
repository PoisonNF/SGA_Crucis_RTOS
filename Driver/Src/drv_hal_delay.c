/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_delay.c

* ���ݼ�������ʱ�����ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��
* 1.1.8		2022-10-22	�����		����RTT����ʹ��hal��ʱ�����������,����us��ʱ����

* 1.0.0a 	2020-02-22	���		�������ļ�

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_DELAY_ENABLE
/**
 * @brief ��ʱ����(ms)
 * @param _ulVal-��ʱʱ����Чֵ����λms��
 * @retval Null
*/
void Drv_Delay_Ms(uint32_t _ulVal)
{
	#ifdef RTT_ENABLE
	rt_thread_mdelay(_ulVal);
	#else
	HAL_Delay(_ulVal);
	#endif 
}

/**
 * @brief ��ʱ����(us)
 * @param _ulVal-��ʱʱ����Чֵ����λus��
 * @retval Null
*/
void Drv_Delay_Us(uint32_t _ulVal)
{
	int i,j;
	for(i = 0; i < _ulVal; i++)
		for(j = 0; j < 12; j++);
}
#endif
