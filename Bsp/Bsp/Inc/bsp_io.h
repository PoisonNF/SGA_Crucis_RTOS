#ifndef __BSP_IO_H_
#define __BSP_IO_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"



/* 用户句柄声明包含区 */

extern tagGPIO_T demoGPIO[];

extern tagUART_T demoUart1;

extern tagUART_T demoUart2;

extern tagJY901_T JY901S;

extern tagPWM_T tPWMDemo[];

extern tagOLED_T tOLED;

extern tagADC_T demoADC[1];
#endif
