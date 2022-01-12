/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             : common.h
 * �汾                 : 0.0.1
 * ����                 : lvchunhao
 * ��������             :��2017��7��25��
 * ����                 : 
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



#define  PRINT_DEBUG                        //��ӡ�ַ���/Hex����

#define  PI                 3.1415926
#define  USART_IRQ_USED     0               //�жϺ����Զ���
#define  MAX_PTL_BYTES      64              //Ŀǰ��������Э���ֽ���

#define  MSG_BUFF_SIZE      256
#define  MAX_RECV_SIZE      256             //���ڽ��ջ�����
#define  MAX_SEND_SIZE      256             //���ڷ��ͻ�����



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
		TaskFunction_t	pTaskFxn;               //������
    uint16_t      u16TaskPrio;              //�������ȼ�
    uint16_t	  u16StackSize;				        //����ջ��С
    xQueueHandle  s32MsgQueID;              //���������ڽ�����Ϣ����Ϣ����ID
    xTaskHandle    stTask;                  //�������ݽṹ(���)

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
		STEP_FIND_HEAD,                            //Ѱ��Э��ͷ       
	  STEP_TYPE_OK,                              //���ͱ�ΪF0 A0 B0�е�һ��
	  STEP_LENGTH_GET,                           //��ó���
	  STEP_DATA_GET,                             //��������
}EmRecvStep;

/*����STM32֮MCU����*/
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


