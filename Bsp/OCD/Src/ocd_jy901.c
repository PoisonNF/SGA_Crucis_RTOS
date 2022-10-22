/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_jy901.c

* ���ݼ�����jy901ģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��
* 1.1.8		2020-10-22	�����		�Խṹ����������ϣ��ṩITģʽ��DMAģʽ

* 1.0.0a 	2020-03-14	���		�������ļ�

* 1.1.0a 	2020-03-29	���		�޸Ĳ����ı�

****************************************************************************/
#include "ocd_jy901.h"


/**
 * @brief JY901���ͽ���ָ���
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
const uint8_t ucpUnlockCmd[] = {0xff, 0xaa, 0x69, 0x88, 0xb5}; 
static void S_JY901_UnLock(tagJY901_T *_tJY901)
{
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpUnlockCmd, sizeof(ucpUnlockCmd));
}

/**
 * @brief JY901��ʱ����
 * @param Null
 * @retval Null
*/
static void S_JY901_Delay(void)
{
	Drv_Delay_Ms(20);
}

/**
 * @brief JY901�������ú���
 * @param *_tJY901-JY901���ָ��
 * @param _ucSet-SAVE_NOW ���浱ǰ;SAVE_RESET ��������;SAVE_DEFAULT �ָ���������;
 * @retval Null
*/
static void S_JY901_SaveConfig(tagJY901_T *_tJY901, uint8_t _ucSet)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x00, 0x00, 0x00};
	
	switch(_ucSet)
	{
		case SAVE_NOW:
			ucpWrite[3] = SAVE_NOW;
		break;
		
		case SAVE_DEFAULT:
			ucpWrite[3] = SAVE_DEFAULT;
		break;

		case SAVE_RESET:
			ucpWrite[3] = SAVE_RESET;
		
		default:
			
		break;
	}
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
}

/**
 * @brief JY901�ش���������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxTypeConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x02, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.ucType >> 8;
	ucpWrite[4] = _tJY901->tConfig.ucType;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901У׼����
 * @param *_tJY901-JY901���ָ��
 * @param _ucMode-У׼ģʽ		
 * @retval Null
*/
void OCD_JY901_Correct(tagJY901_T *_tJY901, uint8_t _ucMode)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x01, 0x00, 0x00};
	
	ucpWrite[3] = _ucMode;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901���ߺ��������ߺ��ٴε���Ϊ������ߣ�
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
const uint8_t ucpSleepCmd[] = {0xff, 0xaa, 0x22, 0x01, 0x00}; 
void OCD_JY901_Sleep(tagJY901_T *_tJY901)
{
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpSleepCmd, sizeof(ucpSleepCmd));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901�ش���������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxSpeedConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x03, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.ucRate;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901�ش�����������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_RxBaudConfig(tagJY901_T *_tJY901)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x04, 0x00, 0x00};
	
	ucpWrite[3] = _tJY901->tConfig.ucBaud;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);		
}

/**
 * @brief JY901�������Զ�У׼����
 * @param *_tJY901-JY901���ָ��
 * @param _ucMode-1-�����Զ�У׼;0-�����Զ�У׼
 * @retval Null
*/
void OCD_JY901_GyroAutoCorrect(tagJY901_T *_tJY901, uint8_t _ucMode)
{
	uint8_t ucpWrite[] = {0xff, 0xaa, 0x63, 0x00, 0x00};
	
	ucpWrite[3] = _ucMode;
	
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, ucpWrite, sizeof(ucpWrite));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901��������������ûش�����Ϊ���������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
const uint8_t ucpOutputOnceCmd[] = {0xff, 0xaa, 0x03, 0x0c, 0x00}; 
void OCD_JY901_OutputOnce(tagJY901_T *_tJY901)
{
	S_JY901_UnLock(_tJY901);
	S_JY901_Delay();
	
	Drv_Uart_Transmit(&_tJY901->tUART, (uint8_t*)ucpOutputOnceCmd, sizeof(ucpOutputOnceCmd));
	S_JY901_Delay();
	
	S_JY901_SaveConfig(_tJY901, SAVE_NOW);
}

/**
 * @brief JY901�жϳ�ʼ������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_ITInit(tagJY901_T *_tJY901)
{
	Drv_Uart_ITInit(&_tJY901->tUART);

	OCD_JY901_RxBaudConfig(_tJY901);
	OCD_JY901_RxSpeedConfig(_tJY901);
	OCD_JY901_RxTypeConfig(_tJY901);
}

/**
 * @brief JY901DMA��ʼ������
 * @param *_tJY901-JY901���ָ��
 * @retval Null
*/
void OCD_JY901_DMAInit(tagJY901_T *_tJY901)
{
	Drv_Uart_DMAInit(&_tJY901->tUART);

	OCD_JY901_RxBaudConfig(_tJY901);
	OCD_JY901_RxSpeedConfig(_tJY901);
	OCD_JY901_RxTypeConfig(_tJY901);
}


