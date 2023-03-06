/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_rm3100.c

* ���ݼ�����rm3100ģ���ļ�

* �ļ���ʷ��

* �汾��	����		����		˵��
* 1.1.8		2022-10-25	���	�������ļ�

****************************************************************************/
#include "ocd_rm3100.h"

/* RM3100��ʼ������ */
struct config tRM3100 = 
{
    .ucCycle_Count   = 200,
    .fSample_Rate   = 37,
    .fMax_Data_Rate = 440,
    .fGain          = 75
};

//*********************************RM3100--spi***************************************************//

/**
 * @brief RM3100Ƭѡ
 * @param _tSPI-spi���ָ��
 * @param _ucLevel-��ƽ
 * @retval Null
*/
static void S_ThreeD3100_CS(tagSPI_T *_tSPI,uint8_t _ucLevel)
{
	HAL_GPIO_WritePin(_tSPI->tGPIO[3].tGPIOPort,_tSPI->tGPIO[3].tGPIOInit.Pin,_ucLevel?GPIO_PIN_SET:GPIO_PIN_RESET);
}

/**
 * @brief RM3100�Ķ��ֽ�д��
 * @param _tSPI-spi���ָ��
 * @param _ucReg_addr-�Ĵ�����ַ
 * @param _ucpDataIn-д�����ݵĵ�ַ
 * @param _ucLenth-д�����ݵĳ���
 * @retval Null
*/
static void S_SPI_Write_M3D3100(tagSPI_T *_tSPI,uint8_t _ucReg_addr,uint8_t *_ucpDataIn,uint8_t _ucLenth)
{
	uint8_t bytecount=0;
	uint8_t temp=0;

	S_ThreeD3100_CS(_tSPI,0) ;	
	temp = 0x00+(_ucReg_addr&0x3f);
	Drv_SPI_TransmitReceive(_tSPI,temp);

	for(bytecount=0;bytecount<_ucLenth;bytecount++)
	{
		temp=*(_ucpDataIn+bytecount);
		Drv_SPI_TransmitReceive(_tSPI,temp);
	}
	S_ThreeD3100_CS(_tSPI,1);
}

/**
 * @brief RM3100�Ķ��ֽڶ�ȡ
 * @param _tSPI-spi���ָ��
 * @param _ucReg_addr-�Ĵ�����ַ
 * @param _ucpDataOut-�������ݵĵ�ַ
 * @param _ucLenth-�������ݵĳ���
 * @retval Null
*/
static void S_SPI_Read_M3D3100(tagSPI_T *_tSPI,uint8_t _ucReg_addr,uint8_t *_ucpDataOut,uint8_t _ucLenth)
{
	uint8_t bytecount=0;
	uint8_t temp=0;
	
	S_ThreeD3100_CS(_tSPI,0);
	temp = 0x80+(_ucReg_addr);
	Drv_SPI_TransmitReceive(_tSPI,temp);
	
	for(bytecount=0;bytecount<_ucLenth;bytecount++)
	{
		temp=Drv_SPI_TransmitReceive(_tSPI,0);
		*(_ucpDataOut+bytecount) = temp;
	}
	S_ThreeD3100_CS(_tSPI,1);	
}

/**
 * @brief RM3100Ϊ��������ģʽʱ���������ݲ�������
 * @param _tSPI-spi���ָ��
 * @param _usValue-����
 * @retval uint8_t-�ɹ�-1  ʧ��-0
*/
uint8_t OCD_SetCycleCount(tagSPI_T *_tSPI,uint16_t _usValue) 
{
    uint8_t to_reg[6];

    if (_usValue > 65535)
        return 0;
    else
	{
		if (_usValue > 400)
        _usValue = 400;
		else if (_usValue < 30)
        _usValue = 30;

		to_reg[0] = _usValue>>8;
		to_reg[1] = _usValue;
		to_reg[2] = to_reg[0];
		to_reg[3] = to_reg[1];
		to_reg[4] = to_reg[0];
		to_reg[5] = to_reg[1];

		S_SPI_Write_M3D3100(_tSPI, M3D_3100_CCX, to_reg,6);
    }
    return 1;
}

/**
 * @brief RM3100Ϊ��������ģʽʱ����������ת������
 * @param _tSPI-spi���ָ��
 * @param _ucConf-����
 * @retval uint8_t-�ɹ�-1  ʧ��-0
*/
uint8_t OCD_SetCMMdatarate(tagSPI_T *_tSPI,uint8_t _ucConf) 
{
    if (_ucConf < CMM_UPDATERATE_600 || _ucConf > CMM_UPDATERATE_0_075)
        return 0;
    else{
        uint8_t *ptr;
        float temp = 1000;

        switch (_ucConf){
            case CMM_UPDATERATE_600: temp=600;
                                    break;
            case CMM_UPDATERATE_300: temp=300;
                                    break;
            case CMM_UPDATERATE_150: temp=150;
                                    break;
            case CMM_UPDATERATE_75 : temp=75;
                                    break;
            case CMM_UPDATERATE_37 : temp=37;
                                    break;
            case CMM_UPDATERATE_18 : temp=18;
                                    break;
            case CMM_UPDATERATE_9  : temp=9;
                                    break;
            case CMM_UPDATERATE_4_5: temp=4.5;
                                    break;
            case CMM_UPDATERATE_2_3: temp=2.3;
                                    break;
            case CMM_UPDATERATE_1_2: temp=1.2;
                                    break;
            case CMM_UPDATERATE_0_6: temp=0.6;
                                    break;
            case CMM_UPDATERATE_0_3: temp=0.3;
                                    break;
            case CMM_UPDATERATE_0_15: temp=0.15;
                                    break;
            case CMM_UPDATERATE_0_075: temp=0.075;
                                    break;
        }
        if (temp > tRM3100.fMax_Data_Rate)				
            return 0;

        ptr = &_ucConf;
        S_SPI_Write_M3D3100(_tSPI, M3D_3100_TMRC, ptr,1);
    }
    return 1;
}

/**
 * @brief RM3100������������ģʽ
 * @param _tSPI-spi���ָ��
 * @param _ucConf-����
 * @retval Null
*/
void OCD_ContinuousModeConfig(tagSPI_T *_tSPI,uint8_t _ucConf) 
{
    uint8_t *ptr;
    ptr = &_ucConf;
    S_SPI_Write_M3D3100(_tSPI, M3D_3100_CMM, ptr,1);
}

/**
 * @brief RM3100���õ��β���ģʽ
 * @param _tSPI-spi���ָ��
 * @param _ucConf-����
 * @retval Null
*/
void OCD_SingleModeConfig(tagSPI_T *_tSPI,uint8_t _ucConf) 
{
    uint8_t *ptr;
    ptr = &_ucConf;
    S_SPI_Write_M3D3100(_tSPI, M3D_3100_POLL, ptr,1);
}

/**
 * @brief RM3100�����Ƿ�ת�����
 * @param _tSPI-spi���ָ��
 * @retval uint8_t-ת�����-1  δת����-0
*/
uint8_t OCD_GetDataReadyStatus(tagSPI_T *_tSPI) 
{
    char data[1];
    S_SPI_Read_M3D3100(_tSPI, M3D_3100_STATUS, (uint8_t*) data,1);
    return (data[0] & STATUS_MASK);
}

/**
 * @brief �趨RM3100����ģʽ
 * @param _tSPI-spi���ָ��
 * @retval Null
*/
void OCD_ThreeD3100_Magic_Init(tagSPI_T *_tSPI)
{
    #ifdef  RM3100_SINGLE
	OCD_SingleModeConfig(_tSPI,CMM_ALL_AXIS_ON);     /* ����ģʽ */
	#endif

	#ifndef RM3100_SINGLE
  	OCD_ContinuousModeConfig(_tSPI,CMM_ALL_AXIS_ON|DRDY_WHEN_ALL_AXIS_MEASURED|CM_START); 			/* ���ò�����,drdy ��������ģʽ */
  	OCD_SetCycleCount(_tSPI,200);												
  	OCD_SetCMMdatarate(_tSPI,12);
	#endif
}

/**
 * @brief spi����RM3100��ȡ����
 * @param _tSPI-spi���ָ��
 * @param _tBuff-��Ż������
 * @retval Null
*/
void OCD_ThreeD3100_Magic_GetData(tagSPI_T *_tSPI,MagData_t *_tBuff)
{
	uint8_t i;
	uint8_t temp[9]={0};
	int32_t Mag_Data[3]={0};

	while(OCD_GetDataReadyStatus(_tSPI)==0);
	S_SPI_Read_M3D3100(_tSPI,0x24,temp,9);
	Mag_Data[0]=temp[0]<<16 | temp[1]<<8 | temp[2];			
	Mag_Data[1]=temp[3]<<16 | temp[4]<<8 | temp[5];
	Mag_Data[2]=temp[6]<<16 | temp[7]<<8 | temp[8];

	for(i=0;i<3;i++)
	{
		if(Mag_Data[i]&0x00800000)
		Mag_Data[i]|=0xff000000;
	}
	
	_tBuff->MAG_X=Mag_Data[1]*13;
	_tBuff->MAG_Y=-Mag_Data[0]*13;
	_tBuff->MAG_Z=-Mag_Data[2]*13; 
}


//*********************************RM3100--soft_spi***************************************************//

/**
 * @brief RM3100�Ķ��ֽ�д��
* @param _tSPI-���spi���ָ��
 * @param _ucReg_addr-�Ĵ�����ַ
 * @param _ucpDataIn-д�����ݵĵ�ַ
 * @param _ucLenth-д�����ݵĳ���
 * @retval Null
*/
static void S_SPI_Write_M3D3100_Soft(tagSPISoft_T *_tSPI,uint8_t _ucReg_addr,uint8_t *_ucpDataIn,uint8_t _ucLenth)
{
	uint8_t bytecount=0;
	uint8_t temp=0;
 
	Drv_SPI_NSS(_tSPI,0);

	temp=0x00+(_ucReg_addr&0x3f);
	Drv_SPI_WriteByte_Soft(_tSPI,temp);

	for(bytecount=0;bytecount<_ucLenth;bytecount++)
	{
		temp=*(_ucpDataIn+bytecount);
		Drv_SPI_WriteByte_Soft(_tSPI,temp);
	}
	Drv_SPI_NSS(_tSPI,1);
}

/**
 * @brief RM3100�Ķ����ֽ�����
 * @param _tSPI-���spi���ָ��
 * @param _ucReg_addr-�Ĵ�����ַ
 * @param _ucpDataOut-д�����ݵĵ�ַ
 * @param _ucLenth-д�����ݵĳ���
 * @retval Null
*/
static void S_SPI_Read_M3D3100_Soft(tagSPISoft_T *_tSPI,uint8_t _ucReg_addr,uint8_t *_ucpDataOut,uint8_t _ucLenth)
{
	uint8_t bytecount = 0;
	uint8_t temp = 0;	

	Drv_SPI_NSS(_tSPI,0);

	temp=0x80+(_ucReg_addr);
	Drv_SPI_WriteByte_Soft(_tSPI,temp);

	for(bytecount=0;bytecount<_ucLenth;bytecount++)
	{
		temp=Drv_SPI_WriteByte_Soft(_tSPI,0);
		*(_ucpDataOut+bytecount) = temp;
	}
	Drv_SPI_NSS(_tSPI,1);
}

/**
 * @brief RM3100���õ��β���ģʽ
 * @param _tSPI-���spi���ָ��
 * @param _ucConf-����
 * @retval Null
*/
void OCD_SingleModeConfig_Soft(tagSPISoft_T *_tSPI,uint8_t _ucConf) 
{
    uint8_t *ptr;

    ptr = &_ucConf ;
    S_SPI_Write_M3D3100_Soft(_tSPI,M3D_3100_POLL, ptr,1);
}

/**
 * @brief RM3100�����Ƿ�ת�����
 * @param _tSPI-���spi���ָ��
 * @retval uint8_t-ת�����-1  δת����-0
*/
uint8_t OCD_GetDataReadyStatus_Soft(tagSPISoft_T *_tSPI)
{
    char data[1];

    S_SPI_Read_M3D3100_Soft(_tSPI,M3D_3100_STATUS, (uint8_t*) data,1);

    return (data[0] & STATUS_MASK);
}

/**
 * @brief RM3100������������ģʽ
 * @param _tSPI-���spi���ָ��
 * @param _ucConf-����
 * @retval Null
*/
void OCD_ContinuousModeConfig_Soft(tagSPISoft_T *_tSPI,uint8_t _ucConf) 
{
    uint8_t *ptr;

    ptr = &_ucConf ;
    S_SPI_Write_M3D3100_Soft(_tSPI,M3D_3100_CMM, ptr,1);
}

/**
 * @brief RM3100Ϊ��������ģʽʱ���������ݲ�������
 * @param _tSPI-���spi���ָ��
 * @param _usValue-����
 * @retval uint8_t-�ɹ�-1  ʧ��-0
*/
uint8_t OCD_SetCycleCount_Soft(tagSPISoft_T *_tSPI,uint16_t _usValue)
{
    uint8_t to_reg[6];

    if (_usValue > 65535 )
        return 0;
    else
	{
		if (_usValue > 400) _usValue=400;
		else if (_usValue < 30) _usValue=30;

		to_reg[0] = _usValue>>8;
		to_reg[1] = _usValue;
		to_reg[2] = to_reg[0];
		to_reg[3] = to_reg[1];
		to_reg[4] = to_reg[0];
		to_reg[5] = to_reg[1];

		S_SPI_Write_M3D3100_Soft(_tSPI,M3D_3100_CCX, to_reg,6);
    }
    return 1;
}

/**
 * @brief RM3100Ϊ��������ģʽʱ����������ת������
 * @param _tSPI-���spi���ָ��
 * @param _ucConf-����
 * @retval uint8_t-�ɹ�-1  ʧ��-0
*/
uint8_t OCD_SetCMMdatarate_Soft(tagSPISoft_T *_tSPI,uint8_t _ucConf)
{
    if (_ucConf < CMM_UPDATERATE_600 || _ucConf > CMM_UPDATERATE_0_075)
        return 0;
    else{
		uint8_t *ptr;
		float temp = 1000;

		switch (_ucConf)
		{
			case CMM_UPDATERATE_600: temp=600;
									break;
			case CMM_UPDATERATE_300: temp=300;
									break;
			case CMM_UPDATERATE_150: temp=150;
									break;
			case CMM_UPDATERATE_75 : temp=75;
									break;
			case CMM_UPDATERATE_37 : temp=37;
									break;
			case CMM_UPDATERATE_18 : temp=18;
									break;
			case CMM_UPDATERATE_9  : temp=9;
									break;
			case CMM_UPDATERATE_4_5: temp=4.5;
									break;
			case CMM_UPDATERATE_2_3: temp=2.3;
									break;
			case CMM_UPDATERATE_1_2: temp=1.2;
									break;
			case CMM_UPDATERATE_0_6: temp=0.6;
									break;
			case CMM_UPDATERATE_0_3: temp=0.3;
									break;
			case CMM_UPDATERATE_0_15: temp=0.15;
                                    break;
			case CMM_UPDATERATE_0_075: temp=0.075;
									break;
        }
		if (temp > tRM3100.fMax_Data_Rate)				
        return 0;

      	ptr = &_ucConf;
      	S_SPI_Write_M3D3100_Soft(_tSPI,M3D_3100_TMRC, ptr,1);
    }
   	return 1;
}

/**
 * @brief �趨RM3100����ģʽ
 * @param _tSPI-���spi���ָ��
 * @retval Null
*/
void OCD_ThreeD3100_Magic_Init_Soft(tagSPISoft_T *_tSPI)
{
	#ifdef  RM3100_SINGLE
	OCD_SingleModeConfig_Soft(_tSPI,CMM_ALL_AXIS_ON);     /* ����ģʽ */
	#endif
	#ifndef RM3100_SINGLE
  	OCD_ContinuousModeConfig_Soft(_tSPI,CMM_ALL_AXIS_ON|DRDY_WHEN_ALL_AXIS_MEASURED|CM_START); 			/* ���ò�����,drdy ��������ģʽ */

  	OCD_SetCycleCount_Soft(_tSPI,200);												
  	OCD_SetCMMdatarate_Soft(_tSPI,12);
	#endif
}

/**
 * @brief ���spi����RM3100��ȡ����
 * @param _tSPI-���spi���ָ��
 * @param _tBuff-��Ż������
 * @retval Null
*/
void OCD_ThreeD3100_Magic_GetData_Soft(tagSPISoft_T *_tSPI,MagData_t *_tBuff)
{
	uint8_t i;
	uint8_t temp[9]={0};
	int32_t Mag_Data[3]={0};

	while(OCD_GetDataReadyStatus_Soft(_tSPI)==0);
	Drv_SPI_NSS(_tSPI,1); 
	S_SPI_Read_M3D3100_Soft(_tSPI,0x24,temp,9);
	Mag_Data[0]=temp[0]<<16 | temp[1]<<8 | temp[2];			
	Mag_Data[1]=temp[3]<<16 | temp[4]<<8 | temp[5];
	Mag_Data[2]=temp[6]<<16 | temp[7]<<8 | temp[8];

	for(i=0;i<3;i++)
	{
		if(Mag_Data[i]&0x00800000)
		Mag_Data[i]|=0xff000000;
	}
	
	_tBuff->MAG_X = Mag_Data[1]*13;
	_tBuff->MAG_Y = -Mag_Data[0]*13;
	_tBuff->MAG_Z = -Mag_Data[2]*13; 
}



