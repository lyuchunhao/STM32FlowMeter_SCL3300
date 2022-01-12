/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             :  scl3300.h
 * �汾                 :  0.0.1
 * ����                 :  lvchunhao
 * ��������             :��2019��8��29��
 * ����                 :  ADS1263��ʼ������
                           1. ģ��SPI
													 2. ADS1263��ʼ��������
 ****************************************************************************/
 
#ifndef _SCL3300_H
#define _SCL3300_H

#include "common.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#define MEAS  0x00
#define RWTR  0x08
#define RDSR  0x0A
#define RLOAD 0x0B
#define STX   0x0E
#define STY   0x0F
#define RADX  0x10
#define RADY  0x11
	 

#define SCL_SETMODE1  0xB400001F         //����ģʽ1(1.8g 40Hz low pass filter)
#define SCL_SETMODE2  0xB400102F	       //����ģʽ2(3.6g 70Hz low pass filter)
#define SCL_SETMODE3  0xB400225F	       //����ģʽ3(Inclination Mode 10Hz low pass filter)
#define SCL_SETMODE4  0xB400338F	       //����ģʽ4(Inclination Mode 10Hz low pass filter Low noise)

#define SCL_READSTAT  0x180000E5         //��ȡ״̬
#define SCL_READFLAG1 0x1C0000E3         //��ȡ�����־1
#define SCL_READFLAG2 0x200000C1         //��ȡ�����־2
#define SCL_READCMD   0x340000DF         //��ȡ����
#define SCL_READSTO   0x100000E9         //�Լ����
#define SCL_READTMP   0x140000EF         //��ȡ�¶�
#define SCL_WHOAMI    0x40000091         //����ʶ��

#define SCL_READACCX  0x040000F7         //��ȡ���ٶ�X
#define SCL_READACCY  0x080000FD         //��ȡ���ٶ�Y
#define SCL_READACCZ  0x0C0000FB         //��ȡ���ٶ�Z

#define SCL_READANGX  0x240000C7         //��ȡ�Ƕ�X
#define SCL_READANGY  0x280000CD         //��ȡ�Ƕ�Y
#define SCL_READANGZ  0x2C0000CB         //��ȡ�Ƕ�Z

#define SCL_ENABLEOUT 0xB0001F6F         //ʹ�ܽǶ����
#define SCL_SWREST    0xB4002098        

	 
	 
	 
	 
/* AD263ƬѡCS */
#define SPI1_CS_HIGH()  HAL_GPIO_WritePin(SPI1_CSB_GPIO_Port, SPI1_CSB_Pin, GPIO_PIN_SET)
#define SPI1_CS_LOW()   HAL_GPIO_WritePin(SPI1_CSB_GPIO_Port, SPI1_CSB_Pin, GPIO_PIN_RESET)
	 
/* RS485����ʹ�� */
#define RS485_SEND_ENABLE() HAL_GPIO_WritePin(Rs485_ENABLE_GPIO_Port, Rs485_ENABLE_Pin, GPIO_PIN_SET)
#define RS485_RECV_ENABLE() HAL_GPIO_WritePin(Rs485_ENABLE_GPIO_Port, Rs485_ENABLE_Pin, GPIO_PIN_RESET)	
	 
	 
void User_SCL3300Init(void);	 
uint8_t User_SCL3300TReadTemperature(uint8_t *u8Data);
uint16_t User_SCL3300TReadANGX(uint8_t *u8Data);
uint16_t User_SCL3300TReadANGY(uint8_t *u8Data);
uint16_t User_SCL3300TReadANGZ(uint8_t *u8Data);

#ifdef __cplusplus
}
#endif

#endif /* _SCL3300_H */

