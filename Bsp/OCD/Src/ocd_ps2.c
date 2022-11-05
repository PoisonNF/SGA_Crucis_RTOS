/****************************************************************************

* Sigma�Ŷ�

* �ļ���: ocd_ps2.c

* ���ݼ�����PS2�ֱ�����ģ���ļ�

* �ļ���ʷ��

* �汾��		����		����		˵��
* 1.1.9		2022-10-27	  �����	 �������ļ�

****************************************************************************/
#include "ocd_ps2.h"

uint16_t Handkey;	// ����ֵ��ȡ����ʱ�洢��
uint8_t Comd[2]={0x01,0x42};	//��ʼ�����������
uint8_t PS2Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //���ݴ洢����
                    /*PS2Data[0]    �� 
                      PS2Data[1]    0x73 ���ģʽ 0x41 ���ģʽ
                      PS2Data[2]    0x5A ��������Ԥ��
                      PS2Data[3]    ��8λ����״̬ 0����
                      PS2Data[4]    ��8λ����״̬ 0����
                      PS2Data[5]    PSS_RX
                      PS2Data[6]    PSS_RY
                      PS2Data[7]    PSS_LX
                      PS2Data[8]    PSS_LY
                    */
uint16_t MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
};

/**
 * @brief ���ֱ�����ָ���
 * @param *_tPS2-PS2���ָ��
 * @param CMD ���͵�ָ�ʮ������
 * @retval Null
*/
static void PS2_Cmd(tagPS2_T *_tPS2,uint8_t CMD)
{
	volatile uint16_t ref=0x01;
	PS2Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //���һλ����λ
		}
		else DO_L;

		CLK_H;                      //ʱ������
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
			PS2Data[1] = ref|PS2Data[1];
	}
	Drv_Delay_Us(16);
}

/**
 * @brief ���ֱ����������ݺ���
 * @param *_tPS2-PS2���ָ��
 * @note ����ʹ��ʱ����ǰ����PS2_ClearData
 * @retval Null
*/
void PS2_ReadData(tagPS2_T *_tPS2)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	CS_L;
	PS2_Cmd(_tPS2,Comd[0]);  //��ʼ����
	PS2_Cmd(_tPS2,Comd[1]);  //��������
	for(byte=2;byte<9;byte++)         //��ʼ��������
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
		    if(DI)
		    PS2Data[byte] = ref|PS2Data[byte];
		}
        Drv_Delay_Us(16);
	}
	CS_H;
}

/**
 * @brief �Զ�������PS2�����ݽ��д���,���ذ���״̬
 * @param *_tPS2-PS2���ָ��
 * @retval ���������
*/
uint8_t PS2_DataKey(tagPS2_T *_tPS2)
{
	uint8_t index;

	PS2_ClearData();
	PS2_ReadData(_tPS2);

	Handkey=(PS2Data[4]<<8)|PS2Data[3];     //����16������  ����Ϊ0�� δ����Ϊ1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;	//���������
	}
	return 0;           //û���κΰ�������
}

//�õ�һ��ҡ�˵�ģ����	 ��Χ0~256
uint8_t PS2_AnologData(uint8_t button)
{
	return PS2Data[button];
}

//������ݻ�����
static void PS2_ClearData(void)
{
	uint8_t a;
	for(a=0;a<9;a++)
		PS2Data[a]=0x00;
}

//�ж��Ƿ�Ϊ���ģʽ,0x41=ģ���̵ƣ�0x73=ģ����
//����ֵ��0�����ģʽ
//		  ����������ģʽ
uint8_t PS2_RedLight(tagPS2_T *_tPS2)
{
	CS_L;
	PS2_Cmd(_tPS2,Comd[0]);  //��ʼ����
	PS2_Cmd(_tPS2,Comd[1]);  //��������
	CS_H;
	if( PS2Data[1] == 0X73)   return 0 ;
	else return 1;

}

/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: �ֱ��𶯺�����
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:�Ҳ�С�𶯵�� 0x00�أ�������
	   motor2:�����𶯵�� 0x40~0xFF �������ֵԽ�� ��Խ��
******************************************************/
void PS2_Vibration(tagPS2_T *_tPS2,uint8_t motor1, uint8_t motor2)
{
	CS_L;
	Drv_Delay_Us(16);
    PS2_Cmd(_tPS2,Comd[0]);  //��ʼ����
	PS2_Cmd(_tPS2,Comd[1]);  //��������
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,motor1);
	PS2_Cmd(_tPS2,motor2);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);  
}
//short poll
static void PS2_ShortPoll(tagPS2_T *_tPS2)
{
	CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,Comd[0]);  
	PS2_Cmd(_tPS2,Comd[1]);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0x00);
	CS_H;
	Drv_Delay_Us(16);	
}
//��������
static void PS2_EnterConfing(tagPS2_T *_tPS2)
{
    CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x43);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x01);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);
}
//����ģʽ����
static void PS2_TurnOnAnalogMode(tagPS2_T *_tPS2)
{
	CS_L;
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x44);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x01); //analog=0x01;digital=0x00  ������÷���ģʽ
	PS2_Cmd(_tPS2,0x03); //Ox03�������ã�������ͨ��������MODE������ģʽ��
				         //0xEE������������ã���ͨ��������MODE������ģʽ��
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);
}
//������
void PS2_VibrationMode(tagPS2_T *_tPS2)
{
	CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x4D);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0X01);
	CS_H;
	Drv_Delay_Us(16);	
}
//��ɲ���������
static void PS2_ExitConfing(tagPS2_T *_tPS2)
{
    CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x43);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	CS_H;
	Drv_Delay_Us(16);
}
//�ֱ����ó�ʼ��
void PS2_SetInit(tagPS2_T *_tPS2)
{
	PS2_ShortPoll(_tPS2);
	PS2_ShortPoll(_tPS2);
	PS2_ShortPoll(_tPS2);
	PS2_EnterConfing(_tPS2);		//��������ģʽ
	PS2_TurnOnAnalogMode(_tPS2);	//�����̵ơ�����ģʽ����ѡ���Ƿ񱣴�
	//PS2_VibrationMode();			//������ģʽ
	PS2_ExitConfing(_tPS2);			//��ɲ���������
}


void PS2_Init(tagPS2_T *_tPS2)
{
    Drv_GPIO_Init(_tPS2->tGPIO,4);
    PS2_SetInit(_tPS2);
}
