#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"

extern osSemaphoreId_t JY901_sem;
extern osSemaphoreId_t Jetson_sem;
extern osSemaphoreId_t OpenMV_sem;
extern osSemaphoreId_t Order_sem;

extern osMutexId_t ps2_mutex;

extern osMessageQId msgqueue;

void UserLogic_Code(void);

#endif
