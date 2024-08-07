#include "usercode.h"		/* usercode头文件 */
#include "threadpool.h"		/* threadpool头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */


/* 线程入口函数（使用裸机忽略此文件） */
/* 测试线程 */
void TestThread(void* paramenter)
{
    while(1)
    {
        Task_Test_Handle();
        rt_thread_yield();
    }
}

/* 报告数据线程 */
void ReportDataThread(void* paramenter)
{
    Task_ReportData_Handle();
}

/* 读取JY901S数据线程 */
void JY901Thread(void* paramenter)
{
    while(1)
    {
        Task_JY901_Handle();
        Drv_Delay_Ms(400);
    }
}

/* 读取MS5837数据线程 */
void MS5837Thread(void* paramenter)
{
    while(1)
    {
        Task_MS5837_Handle();
        Drv_Delay_Ms(600);
    }    
}

/* 读取AD4111数据线程 */
void AD4111Thread(void* paramenter)
{
    Task_AD4111_Sync();
    while(1)
    {
        Task_AD4111_Handle();
        Drv_Delay_Ms(500);
    }
}

/* 上位机命令解析线程 */
void IPCcmdThread(void* paramenter)
{
    while(1)
    {
        Task_IPCcmd_Handle();
        Drv_Delay_Ms(1);
    }
}

/* I.MX6ull解析线程 */
void IMX6ULLThread(void* paramenter)
{
    while(1)
    {
        Task_IMX6ULL_Handle();
        Drv_Delay_Ms(1);     
    }
}

/* DS1337解析线程 */
void DS1337Thread(void* paramenter)
{
    while(1)
    {
        Task_DS1337_Handle();
        Drv_Delay_Ms(1000);     
    }
}
