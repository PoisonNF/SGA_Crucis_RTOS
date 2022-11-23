#ifndef	__USERCODE_H_
#define	__USERCODE_H_

#include "drv_hal_conf.h"

/* 线程句柄 */
extern rt_thread_t thread1;
extern rt_thread_t thread2;
extern rt_thread_t thread3;
extern rt_thread_t thread4;
extern rt_thread_t thread5;
extern rt_thread_t thread6;
extern rt_thread_t thread7;
extern rt_thread_t thread8;
extern rt_thread_t thread9;

/* 信号量句柄*/
extern rt_sem_t binary_sem;
extern rt_sem_t binary_semJ;
extern rt_sem_t binary_semO;

/* 互斥量句柄 */
extern rt_mutex_t ps2_mutex;

/*消息队列句柄*/
extern rt_mq_t msgqueue;

void UserLogic_Code(void);

#endif
