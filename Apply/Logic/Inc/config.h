#ifndef __BSP_IO_H_
#define __BSP_IO_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"



/* 用户句柄声明包含区 */

extern tagGPIO_T GPIO[];

extern tagGPIO_T U4485Ctrl;

extern tagUART_T Uart1;

extern tagJY901_T JY901S;

extern tagUART_T Uart3;

extern tagUART_T Uart4;

extern tagUART_T OpenMV;

extern tagPWM_T PWM[];

extern tagOLED_T OLED;

extern tagADC_T ADC[1];

extern tagPS2_T PS2;

extern tagSPISoft_T SPI_soft[2];

extern tagSPI_T SPI[3]; 
#endif
