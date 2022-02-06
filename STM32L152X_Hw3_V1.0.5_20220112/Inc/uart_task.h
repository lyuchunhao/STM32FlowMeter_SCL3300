/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             :  uart_task.h
 * �汾                 :  0.0.1
 * ����                 :  lvchunhao
 * ��������             :��2019��8��11��
 * ����                 :  Uart�ն˷����߳�
                           1. ���е��·�����ͨ�����������
 ****************************************************************************/
#ifndef _UART_TASK_H
#define _UART_TASK_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stdint.h"
	
	 
extern uint8_t g_u8UartBraudRate;
extern uint8_t g_u8Rs232RecvCompeletFlag;
	 
void vTaskUartWrite(void *pArgs);
void vTaskUartRecev(void *pArgs);
void Rs232RecvOneData(uint8_t u8Bytes);
int32_t Rs232RecvProtolData(uint8_t u8Data);
int32_t PostUartWriteMsg(uint8_t *pData, uint32_t u32DataLen);
	 
	 
#ifdef __cplusplus
}
#endif
#endif /* _SEND_TASK_H */

