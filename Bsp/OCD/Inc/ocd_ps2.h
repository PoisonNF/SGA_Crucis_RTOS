#ifndef __OCD_PS2_H_
#define __OCD_PS2_H_

#include "drv_hal_conf.h"

#define DI  Drv_GPIO_Read(&_tPS2->tGPIO[0])     //DI����

#define DO_H Drv_GPIO_Set(&_tPS2->tGPIO[1])     //����λ��
#define DO_L Drv_GPIO_Reset(&_tPS2->tGPIO[1])   //����λ��

#define CS_H Drv_GPIO_Set(&_tPS2->tGPIO[2])     //CS����
#define CS_L Drv_GPIO_Reset(&_tPS2->tGPIO[2])   //CS����

#define CLK_H Drv_GPIO_Set(&_tPS2->tGPIO[3])    //ʱ������
#define CLK_L Drv_GPIO_Reset(&_tPS2->tGPIO[3])  //ʱ������

/* ������Ӧ */
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
/* ��ɫ�ֱ� */
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
/* ͼ�ηֱ� */
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16


/* ҡ�˴洢λ�� */
#define PSS_RX 5                //��ҡ��X������
#define PSS_RY 6                //��ҡ��Y������
#define PSS_LX 7                //��ҡ��X������
#define PSS_LY 8                //��ҡ��Y������

#define DELAY_TIME  Drv_Delay_Us(5); 

typedef struct 
{
    tagGPIO_T tGPIO[4];     //����[0]DI/DAT [1]DO/CMD [2]CS [3]CLK˳��
}tagPS2_T;

extern uint8_t PS2Data[9];
extern uint16_t MASK[16];
extern uint16_t Handkey;

void PS2_Init(tagPS2_T *_tPS2);
void PS2_SetInit(tagPS2_T *_tPS2);
uint8_t PS2_RedLight(tagPS2_T *_tPS2);
uint8_t PS2_AnologData(uint8_t button);
void PS2_ReadData(tagPS2_T *_tPS2);
uint8_t PS2_DataKey(tagPS2_T *_tPS2);
void PS2_ClearData(void);

#endif

