/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_fatfs.c

* ���ݼ�����FATFSģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��

* 1.0.0a 	2020-02-22	���		�������ļ�
* 1.0.1a 	2020-03-29	���		�޸�OCD_FATFS_ReadDir�Ľӿڲ����Լ��ڲ��߼����޸�OCD_FATFS_ReadData_SpecifyIndexִ���߼�
									����OCD_FATFS_GetFileInfo����

****************************************************************************/
#include "ocd_fatfs.h"

/**
 * @brief FATFS�ļ�ϵͳ�����ļ���
 * @param _tFATFS-FATFS�ṹ��ָ��
 * @param _cpPath-�ļ���·��ָ��
 * @retval uint8_t
 */
uint8_t OCD_FATFS_CreateDir(tagFATFS_T *_tFATFS, const char *_cpPath)
{
	f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1); /* ΪSD������һ�������� */
	if(f_mkdir(_cpPath)==0) 
	{
	   
	}
	else
	{
		return 0; /* �����ļ���ʧ�ܻ��ļ����Ѵ��� */
	}
	f_mount(NULL, 0, 1); /* ע�������� */
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��ȡ��Ӧ�ļ���Ŀ¼�µ��ļ���
 * @param _tFATFS-FATFS�ṹ��ָ��
 * @param _tpINFO-�ļ������Ϣ�ṹ��ָ��
 * @param _cpPath-�ļ���·��ָ��
 * @param _ucNameLen-�ļ�������
 * @retval uint8_t-�ļ�����
 */
uint8_t OCD_FATFS_ReadDir(tagFATFS_T *_tFATFS, tagFileInfo_T *_tpINFO, const char *_cpPath, uint8_t _ucNameLen)
{  
	uint8_t index = 0;
	uint8_t j;
	
	f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	
	if (f_opendir(&_tFATFS->tFATFSInfo.tDIR, _cpPath) == FR_OK)    
	{   
		while (f_readdir(&_tFATFS->tFATFSInfo.tDIR, &_tFATFS->tFATFSInfo.tFILINFO) == FR_OK)    
		{  
			if(!_tFATFS->tFATFSInfo.tFILINFO.fname[0])
				break;
				
			for(j = 0; j < _ucNameLen; j++)
			{
				_tpINFO[index].file_name[j] = _tFATFS->tFATFSInfo.tFILINFO.fname[j];
			}
			index++;
		}
	}
	else 
	{
		return 0;
	}
	   
	f_mount(NULL, 0, 1);
	return index;
}

/**
 * @brief FATFS�ļ�ϵͳ��ȡ��Ӧ·�����ļ�ָ�����ȵ�����
 * @param _tFATFS-FATFS�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @param _ucpData-������ݵĻ�������ָ��
 * @param _usLen-���ݳ���
 * @param _ulByteVal-��ȡ������Ч�ֽ���
 * @retval uint8_t
 */
uint8_t OCD_FATFS_ReadData_SpecifyFiles(tagFATFS_T *_tFATFS, char *_cpFileName, uint8_t *_ucpData, uint16_t _usLen, uint32_t _ulByteVal)
{
	FRESULT res;
	
	f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_OPEN_EXISTING|FA_READ);
	if(res)
		return 0;
	
	res = f_read(&_tFATFS->tFATFSInfo.tFIL, _ucpData, _usLen, &_ulByteVal);
	if(res)
		return 0;
	
	res = f_close(&_tFATFS->tFATFSInfo.tFIL);
	if(res)
		return 0;
	
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��ȡ��Ӧ·�����ļ���ָ��λ�õ�����
 * @param _tFATFS-�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @param _ucpData-������ݵĻ�������ָ��
 * @param _usLength-��ȡ���ݵĳ���
 * @param _ulOffset-��ȡλ�õ�ƫ����
 * @param _ulByteVal-��ȡ������Ч�ֽ���
 * @retval uint8_t
 */
uint8_t OCD_FATFS_ReadData_SpecifyIndex(tagFATFS_T *_tFATFS, char *_cpFileName, uint8_t *_ucpData, uint16_t _usLength, uint32_t _ulOffset, uint32_t _ulByteVal)
{
	FRESULT res;
	
	f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_OPEN_EXISTING|FA_READ);	
	if(res)
		return 0;
	
	res = f_lseek(&_tFATFS->tFATFSInfo.tFIL,_ulOffset);	
	if(res)
		return 0;
	
	res = f_read(&_tFATFS->tFATFSInfo.tFIL, _ucpData, _usLength, &_ulByteVal);
	if(res)
		return 0;
	
	res = f_close(&_tFATFS->tFATFSInfo.tFIL);
	if(res)
		return 2;
	
	f_mount(NULL, 0, 1);

	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��Ӧ·�����ļ���ָ��λ��д������
 * @param _tFATFS-�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @param _cpData-��Ҫд�����ݵĻ�������ָ��
 * @param _lLen-д�����ݵĳ���
 * @param _ulByteVal-д�����Ч�ֽ���
 * @retval uint8_t-1-�ɹ�������-ʧ��
 */
uint8_t OCD_FATFS_Write_SpecifyIndex(tagFATFS_T *_tFATFS, char *_cpFileName, char *_cpData, int _lLen, unsigned int _ulIndex, uint32_t _ulByteVal)
{
	FRESULT res;
	
	res = f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	
	if(res)
	{
		return 0;
	}

	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_WRITE | FA_CREATE_ALWAYS);		
	if(res)
	{
		return 0;
	}
	
	res = f_lseek(&_tFATFS->tFATFSInfo.tFIL, _ulIndex);
	if(res)
	{
//		f_mount(0,0);
		return 3;
	}
	
	res = f_write(&_tFATFS->tFATFSInfo.tFIL,_cpData, _lLen, &_ulByteVal);
	if(res)
	{
//		f_mount(0,0);
		return 4;
	}
	
	res = f_close(&_tFATFS->tFATFSInfo.tFIL);
		
//	f_mount(&_tFATFS->tFATFSInfo.tFATFS, 0, 0);
		
	if(res)
	{
		return 2;
	}
	
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��Ӧ·�����ļ���β��д������
 * @param _tFATFS-�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @param _cpData-��Ҫд�����ݵĻ�������ָ��
 * @param _lLen-д�����ݵĳ���
 * @param _ulByteVal-д�����Ч�ֽ���
 * @retval uint8_t-1-�ɹ�������-ʧ��
 */
uint8_t OCD_FATFS_Write_End(tagFATFS_T *_tFATFS, char *_cpFileName, char *_cpData, int _lLen, uint32_t _ulByteVal)
{
	FRESULT res = FR_OK;
	
	res = f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	
	if(res)
	{
		return 0;
	}

	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_WRITE | FA_OPEN_ALWAYS);
		
	if(res)
	{
//		f_mount(0,0);
		return 0;
	}
	
	res = f_lseek(&_tFATFS->tFATFSInfo.tFIL, f_size(&_tFATFS->tFATFSInfo.tFIL));
	if(res)
	{
//		f_mount(0,0);
		return 3;
	}

	res = f_write(&_tFATFS->tFATFSInfo.tFIL,_cpData, _lLen, &_ulByteVal);
	if(res)
	{
//		f_mount(0,0);
		return 4;
	}
	res = f_close(&_tFATFS->tFATFSInfo.tFIL);
		
//	f_mount(&_tFATFS->tFATFSInfo.tFATFS, 0, 0);
		
	if(res)
	{
		return 2;
	}
	
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��Ӧ·�����ļ�д������
 * @param _tFATFS-�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @param _cpData-��Ҫд�����ݵĻ�������ָ��
 * @param _lLen-д�����ݵĳ���
 * @param _ulByteVal-д�����Ч�ֽ���
 * @retval uint8_t-1-�ɹ�������-ʧ��
 */
uint8_t OCD_FATFS_Write(tagFATFS_T *_tFATFS, char *_cpFileName,char *_cpData,int _lLen, uint32_t _ulByteVal)
{
	FRESULT res;
	
	res = f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	
	if(res)
		return 0;

	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_WRITE | FA_OPEN_ALWAYS);
		
	if(res)
		return 0;

	res = f_write(&_tFATFS->tFATFSInfo.tFIL,_cpData, _lLen, &_ulByteVal);
	if(res)
		return 4;

	res = f_close(&_tFATFS->tFATFSInfo.tFIL);
		
//	f_mount(&_tFATFS->tFATFSInfo.tFATFS, 0, 0);
		
	if(res)
	{
		return 2;
	}
	
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��ȡ�ļ���Ϣ
 * @param _tFATFS-�ļ�ϵͳ�ṹ��
 * @param _cpFileName-�ļ�·��ָ��
 * @retval uint8_t-1-�ɹ�������-ʧ��
 */
uint8_t OCD_FATFS_GetFileInfo(tagFATFS_T *_tFATFS, char *_cpFileName)
{
	FRESULT res;
	
	f_mount(&_tFATFS->tFATFSInfo.tFATFS, "0:", 1);
	res = f_open(&_tFATFS->tFATFSInfo.tFIL, _cpFileName, FA_OPEN_EXISTING|FA_READ);	
	if(res)
		return 0;
	
	res = f_stat(_cpFileName, &_tFATFS->tFATFSInfo.tFILINFO);
	if(res)
		return 2;
	
	return 1;
}

/**
 * @brief FATFS�ļ�ϵͳ��ʼ��
 * @param _tFATFS-FATFS�ṹ��ָ��
 * @retval uint8_t
 */
uint8_t OCD_FATFS_Init(tagFATFS_T *_tFATFS)
{
	return OCD_SDCard_SPIInit(_tFATFS->tSPI);
}

