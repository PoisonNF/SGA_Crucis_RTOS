#ifndef __DRV_CONF_H_
#define __DRV_CONF_H_

#define DRIVER_VERSION	"2022/10/25 V1.1.8"

/* RT-Thread���� ʹ��RTTʱ����ע�ͣ����ڹ����е���RTT����ں� */ 
#define RTT_ENABLE               
#ifdef RTT_ENABLE
#include <rtthread.h>	//rt-threadͷ�ļ�
#include "threadpool.h" //����߳���ں�������
#endif // RTT���ͷ�ļ�

#define PRINTF_UART	USART1				/* printfʹ�õĴ��� */

/* STM32оƬѡ�� */
#ifdef STM32F1_SGA_ENABLE
	#define SYSTEM_CLOCK 	72			/* ϵͳ��Ƶʱ�ӣ�72����λ��M */
	
	/* rtt��� */
	#define STM32_SRAM_SIZE 64
	#define STM32F10X_PIN_NUMBERS 100
#endif

#ifdef STM32L4_SGA_ENABLE
	#define SYSTEM_CLOCK 	80			/* ϵͳ��Ƶʱ�ӣ�80����λ��M */
	
	/* rtt��� */
	#define STM32_SRAM_SIZE 64
	#define STM32L4X_PIN_NUMBERS 64
#endif

/* ����ģ�� */
#define DRV_HAL_ENABLE
#define DRV_HAL_GPIO_ENABLE
#define DRV_HAL_DELAY_ENABLE
#define DRV_HAL_TIMER_ENABLE
#define DRV_HAL_SPI_ENABLE
#define DRV_HAL_SPI_SOFT_ENABLE 
#define DRV_HAL_ADC_ENABLE
#define DRV_HAL_UART_ENABLE
#define	DRV_HAL_IIC_SOFT_ENABLE
#define	DRV_HAL_PWM_ENABLE
#define	DRV_HAL_ADC_ENABLE

#include "drv_hal.h"

#ifdef DRV_HAL_DELAY_ENABLE
#include "drv_hal_delay.h"
#endif

#ifdef DRV_HAL_GPIO_ENABLE
#include "drv_hal_gpio.h"
#endif

#ifdef DRV_HAL_PWM_ENABLE
#include "drv_hal_pwm.h"
#endif

#ifdef DRV_HAL_SPI_ENABLE
#include "drv_hal_spi.h"
#endif

#ifdef DRV_HAL_SPI_SOFT_ENABLE
#include "drv_hal_spi_soft.h"
#endif

#ifdef DRV_HAL_TIMER_ENABLE
#include "drv_hal_timer.h"
#endif

#ifdef DRV_HAL_UART_ENABLE
#include "drv_hal_uart.h"
#endif

#ifdef DRV_HAL_IIC_SOFT_ENABLE
#include "drv_hal_iic_soft.h"
#endif

#ifdef DRV_HAL_ADC_ENABLE
#include "drv_hal_adc.h"
#endif

/* C���Ա�׼�� */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#endif
