#ifndef __DRV_UART_H_
#define __DRV_UART_H_

#include "drv_hal_conf.h"

#define UART_TIME_OUT	0xff

/* ���ڽ�����Ϣ�ṹ�� */
typedef struct
{
	uint16_t			usRxCnt;			/* �������ݼ����� */
	uint16_t			usRxLenth;			/* �������ݳ��� */
	uint16_t			usRxMAXLenth;		/* ����������󳤶� */
	uint8_t				ucpRxBuffer[1];		/* ����Buffer */
	uint8_t				*ucpRxCache;		/* ���ջ����� */
}tagUartRxInfo_T;

/* ���ڷ�����Ϣ�ṹ�� */
typedef struct 
{
	uint16_t			usTxMAXLenth;		/* ����������󳤶� */
	uint8_t				*ucpTxCache;		/* ���ͻ����� */
}tagUartTxInfo_T;

/* ����DMA���� */
typedef struct
{
	DMA_HandleTypeDef	tDMATx;				/* DMA���;�� */
	DMA_HandleTypeDef	tDMARx;				/* DMA���վ�� */

	uint8_t				ucDMARxCplt;			/* DMA������ɱ�־*/
	uint8_t 			ucDMATxCplt;			/* DMA������ɱ�־*/

	bool 				bTxEnable;			/* ����ʹ�ܷ��� */
	bool				bRxEnable;			/* ����ʹ�ܷ��� */

	uint8_t				ucDMARxPriority;		/* DMA�����ж����ȼ���0-15 */
	uint8_t 			ucDMARxSubPriority;		/* DMA�����ж������ȼ���0-15 */

	uint8_t				ucDMATxPriority;		/* DMA�����ж����ȼ���0-15 */
	uint8_t 			ucDMATxSubPriority;		/* DMA�����ж������ȼ���0-15 */
}tagDMAUart_T;

/* �����豸�ṹ�� */
typedef struct
{
	UART_HandleTypeDef 	tUARTHandle;	/* STM32�ڲ������豸ָ�� */
	tagDMAUart_T		tUartDMA;		/* ����DMA���� */
	tagUartRxInfo_T		tRxInfo;		/* ���ڽ�����Ϣ */
	tagUartTxInfo_T		tTxInfo;		/* ���ڷ�����Ϣ */
	tagGPIO_T			tGPIO[2];		/* GPIO��� */
	uint8_t				ucPriority;		/* �ж����ȼ���0-15 */
	uint8_t 			ucSubPriority;	/* �ж������ȼ���0-15 */
}tagUART_T;

/* ������ӳ���
	USART1	full remap (TX/PB6, RX/PB7)
			no remap (TX/PA9, RX/PA10)
	USART2	full remap (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
			no remap (CTS/PA0, RTS/PA1, TX/PA2, RX/PA3, CK/PA4)
	USART3	full remap (TX/PD8,  RX/PD9,  CK/PD10, CTS/PD11, RTS/PD12)
			partial	remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14)
			no remap (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14)
*/

void Drv_Uart_ITInit(tagUART_T *_tUART);
void Drv_Uart_DMAInit(tagUART_T *_tUART);
void Drv_Uart_Transmit(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize);
void Drv_Uart_Transmit_IT(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize);
void Drv_Uart_Transmit_DMA(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize);
void Drv_Uart_ReceIT_Enable(tagUART_T *_tUART, uint8_t *_ucpBuffer, uint16_t _uspSize);
void Drv_Uart_IRQHandler(tagUART_T *_tUART);
void Drv_Uart_DMA_RxHandler(tagUART_T *_tUART);
void Drv_Uart_DMA_TxHandler(tagUART_T *_tUART);

#endif
