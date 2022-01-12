/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs 版权所有
 ****************************************************************************
 * 文件名称             : common.h
 * 版本                 : 0.0.1
 * 作者                 : lvchunhao
 * 创建日期             :　2017年7月25日
 * 描述                 : 
 ****************************************************************************/
#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "cmsis_os.h"

#include "main.h"
#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "i2c.h"

#include "scl3300.h"
#include "uart_task.h"
#include "angle_task.h"



#define  PRINT_DEBUG                        //打印字符串/Hex开关

#define  PI                 3.1415926
#define  USART_IRQ_USED     0               //中断函数自定义
#define  MAX_PTL_BYTES      64              //目前设置最大的协议字节数

#define  MSG_BUFF_SIZE      256
#define  MAX_RECV_SIZE      256             //串口接收缓冲区
#define  MAX_SEND_SIZE      256             //串口发送缓冲区



#define RS232_IT_ENABLE()  STM32L_UART_RxITEnable(&huart1, 1)
#define RS232_IT_DIABLE()  STM32L_UART_RxITEnable(&huart1, 0)


typedef union _tagUn12BytesData
{
		uint8_t u8Data[12];
	  uint32_t u32Data[3];
}Un12BytesData;

typedef union _tagUn32AndArray
{
		uint32_t u32SCL3300CMD;
	  uint8_t  u8SCL3300CMD[4];
	
}Un32AndArray;

typedef struct _tagStTaskObj
{
    const char    *pTaskName;
		TaskFunction_t	pTaskFxn;               //任务函数
    uint16_t      u16TaskPrio;              //任务优先级
    uint16_t	  u16StackSize;				        //任务栈大小
    xQueueHandle  s32MsgQueID;              //本任务用于接受消息的消息队列ID
    xTaskHandle    stTask;                  //任务数据结构(句柄)

}StTaskObj;


typedef struct _tagStMsgPkg
{
		uint8_t *pData;
		uint8_t u8UartType;
		uint32_t u32DataLen;
}StMsgPkg;

typedef enum _tagEmUartType
{
		TYPE_NUM_UART1 = 0x01,
		TYPE_NUM_UART2,
		TYPE_NUM_UART3,
}EmUartType;

typedef enum _tagEmAINNum
{
		ADS1263_AIN2_A2OUT1 = 0x01,
		ADS1263_AIN3_A2OUT2,
		ADS1263_AIN4_A1OUT2,
		ADS1263_AIN5_A1OUT1,
}EmAINNum;

typedef enum _tagEmRecvStep
{
		STEP_RECV_INIT = 0x00,                     
		STEP_FIND_HEAD,                            //寻找协议头       
	  STEP_TYPE_OK,                              //类型必为F0 A0 B0中的一种
	  STEP_LENGTH_GET,                           //获得长度
	  STEP_DATA_GET,                             //接收数据
}EmRecvStep;

/*定义STM32之MCU类型*/
typedef enum _tagEmMCUTypedef{
   TYPE_STM32F0,
   TYPE_STM32F1,
	 TYPE_STM32F2,
   TYPE_STM32F3,
   TYPE_STM32F4,
   TYPE_STM32F7,
   TYPE_STM32L0,
   TYPE_STM32L1,
   TYPE_STM32L4,
   TYPE_STM32H7,
}EmMCUTypedef;

#ifdef PRINT_DEBUG
#if 1
#define PRINT(x, ...) RS485_SEND_ENABLE(); \
                      vTaskDelay(1);\
											printf(" "x, ##__VA_ARGS__);\
	                    vTaskDelay(5);\
											RS485_RECV_ENABLE(); 							
#else
#define PRINT(x, ...) printf("[%s:%d]: "x, __FILE__, __LINE__, ##__VA_ARGS__);
#endif
#else
#define PRINT(x, ...)
#endif

#endif /* _COMMON_H */


