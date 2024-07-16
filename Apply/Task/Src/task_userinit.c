#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

/* �����ʼ������ */
void Task_UserInit(void)
{
    uint8_t ret = 0;

	Drv_GPIO_Init(LED, 3);
    
    Drv_Uart_DMAInit(&Uart1);       /* ��ʼ������1 DAP�ӿ� ����RS232�ӿ� */
    OCD_JY901_DMAInit(&JY901S);     /* ��ʼ��JY901S ʹ�ô���2 */
    Drv_Uart_DMAInit(&Uart3);       /* ��ʼ������3 ���ߵ�̨ */
    
    ret = OCD_AD24BIT_Init(&AD4111_1);  /* 24λAD��ʼ�� */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //���򱨴�stop	
	}
    ret = OCD_AD24BIT_Init(&AD4111_2);  /* 24λAD��ʼ�� */
	if (ret != 0)
	{
		printf("##AD init fail, error code:%d!!!\r\n",ret);
		while(1);  //���򱨴�stop	
	}
    
    Drv_PWM_Init(PWM,11);       /* ��ʼ��PWM */
    
    if(OCD_MS5837_Init(&MS5837) == 0)
        printf("MS5837 error\r\n");
}
