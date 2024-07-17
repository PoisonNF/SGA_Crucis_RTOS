#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"

void UserLogic_Code(void);

extern rt_sem_t JY901S_Sem;

extern rt_thread_t TestThread_t;
extern rt_thread_t ReportDataThread_t;
extern rt_thread_t JY901Thread_t;

#endif
