/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs 版权所有
 ****************************************************************************
 * 文件名称             :  uart_task.h
 * 版本                 :  0.0.1
 * 作者                 :  lvchunhao
 * 创建日期             :　2019年8月11日
 * 描述                 :  Uart终端发送线程
                           1. 所有的下发都将通过此任务完成
 ****************************************************************************/
#ifndef _UART_TASK_H
#define _UART_TASK_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stdint.h"
	
	 
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

