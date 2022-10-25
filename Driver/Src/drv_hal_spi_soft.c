/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_spi_soft.c

* ���ݼ��������spiģ�������ļ�

* �ļ���ʷ��

* �汾��		����		����		˵��
* 1.1.8 	2022-10-25     ���		 �������ļ�

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_SPI_ENABLE
/**
 * @brief ģ��SPI��ʼ��
 * @param _tSPI---SPI�ṹ��ָ��
 * @retval Null 
*/
void Drv_SPISoft_Init(tagSPISoft_T *_tSPI)
{
	Drv_GPIO_Init(_tSPI->tSPISoft, 4);
}

/**
 * @brief SPICLK ���
 * @param id-�ڼ������spi ��Ӧ�ڶ���ʱ��˳��
 * @param level-��ƽ 0-�� 1-��  
 * @retval NULL
*/
void Drv_SPI_CLK(tagSPISoft_T *_tSPI, uint8_t level)
{
	HAL_GPIO_WritePin(_tSPI->tSPISoft[0].tGPIOPort, _tSPI->tSPISoft[0].tGPIOInit.Pin, level?GPIO_PIN_SET:GPIO_PIN_RESET);
}

/**
 * @brief SPIMOSI ���
 * @param id-�ڼ������spi ��Ӧ�ڶ���ʱ��˳�� 
 * @retval �����ĵ�ƽ
*/

GPIO_PinState Drv_SPI_MISO(tagSPISoft_T *_tSPI)
{
	return HAL_GPIO_ReadPin(_tSPI->tSPISoft[3].tGPIOPort, _tSPI->tSPISoft[3].tGPIOInit.Pin);

}

/**
 * @brief SPIMOSI ���
 * @param id-�ڼ������spi ��Ӧ�ڶ���ʱ��˳��
 * @param level-��ƽ 0-�� 1-��  
 * @retval NULL
*/
void Drv_SPI_MOSI(tagSPISoft_T *_tSPI, uint8_t level)
{
	HAL_GPIO_WritePin(_tSPI->tSPISoft[2].tGPIOPort, _tSPI->tSPISoft[2].tGPIOInit.Pin, level?GPIO_PIN_SET:GPIO_PIN_RESET);
}

/**
 * @brief SPIƬѡ
 * @param level-���� 0-�� 1-��  
 * @param id-�ڼ������spi ��Ӧ�ڶ���ʱ��˳��
 * @retval NULL
*/
void Drv_SPI_NSS(tagSPISoft_T *_tSPI,uint8_t level)
{
	HAL_GPIO_WritePin(_tSPI->tSPISoft[1].tGPIOPort, _tSPI->tSPISoft[1].tGPIOInit.Pin, level?GPIO_PIN_SET:GPIO_PIN_RESET);
}

/**
 * @brief ��дһ���ֽ�
 * @param data-д������  
 * @param id-�ڼ������spi ��Ӧ�ڶ���ʱ��˳��
 * @retval ��ȡ������
*/
uint8_t Drv_SPI_WriteByte_soft(tagSPISoft_T *_tSPI,uint8_t data)
{
	uint8_t i = 0;
	uint8_t temp = 0;
	uint8_t read_data = 0xFF;
	for(i=0;i<8;i++) 
	{
		temp = ((data&0x80)==0x80)? 1:0;
		data = data<<1;
		read_data = read_data<<1;
		Drv_SPI_CLK(_tSPI,0);
		Drv_SPI_MOSI(_tSPI,temp);
		SPI_Delay
		Drv_SPI_CLK(_tSPI,1);
		SPI_Delay
		if(Drv_SPI_MISO(_tSPI)==1) {read_data = read_data + 1; } 
	}
	Drv_SPI_CLK(_tSPI,0);
	return read_data;
}

#endif

