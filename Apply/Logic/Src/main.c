#include "main.h"
#include "drv_hal_conf.h"	/* �����ض��� */ 
#include "task_userinit.h"
#include "usercode.h"

#ifdef RTT_ENABLE
#include <rtthread.h>		/* RTOS�����޸���rtconfig.h��*/
#else
#include "task_sysinit.h"
#endif

int main()
{
#ifdef	RTT_ENABLE
	rt_kprintf("RTT ����\r\n");
	/*
     * ������Ӳ����ʼ���� RT-Thread ϵͳ��ʼ���Ѿ��� main ����֮ǰ��ɣ�
     * ���� component.c �ļ��е� rtthread_startup()����������ˡ� 
     * ������ main �����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
    */
#else	/* ������� */
	Task_Sys_Init();		/* ϵͳ��ʼ�������� */
#endif
    Task_UserInit();		/* �û������ʼ�� */	
    UserLogic_Code();		/* �û��߼�ִ�� */
}
