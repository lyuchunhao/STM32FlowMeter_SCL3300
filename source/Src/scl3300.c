/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             :  scl3300.c
 * �汾                 :  0.0.1
 * ����                 :  lvchunhao
 * ��������             :��2019��8��29��
 * ����                 :  SCA100T��ʼ������
                           1. ģ��SPI2
													 2. SCA100T��ʼ��������
 ****************************************************************************/

#include "common.h"



/* MSB First Output MSB first Input */
void User_SCL3300TransmitReceive(uint8_t *pWrite, uint8_t *pRead)
{
		__nop();
		SPI1_CS_LOW();
	  __nop();
		__nop();
		__nop();
		__nop();
		HAL_SPI_TransmitReceive(&hspi1, pWrite, pRead, 4, 10);
	  __nop();
		__nop();
		__nop();
		__nop();
		SPI1_CS_HIGH();
	  __nop();
}

void User_SCL3300Init(void)
{
		//1.�����豸 
		uint8_t u8Read[4]  = {0};
		uint8_t u8Write[4]  = {0};
		Un32AndArray un32AndArrayCMD;
	
		//2. ��ʱ10ms
		vTaskDelay(20);
	
		//3. ���ò���ģʽ
		un32AndArrayCMD.u32SCL3300CMD = SCL_SETMODE3;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		//4. ��ʱ5ms
		vTaskDelay(10);
		
		//5. ��ȡ״̬�����Status Summary
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		//6. ��ȡ״̬����ȡStatus Summary(����5����Ӧ)
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		//7. ��ȡ״̬�������κ���Ч����(����6����Ӧ)
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
	
		//8. ʹ�ܽǶ����
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_ENABLEOUT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		//9. ����ʶ��
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_WHOAMI;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		__nop();
		__nop();
		PRINT("Device:0x%02X%02X%02X%02X\n", u8Read[0],u8Read[1],u8Read[2],u8Read[3]);
}
/*
 * OP[31:26] + RS[25:24] + Data[23:8] + CRC[7:0]
 * OP:������,��RW+��ַADDR���
 * RS:����״̬ 00�������� 01�������� 10���� 11����
 * Data������
 * CRC��У��CRC
*/
uint8_t User_SCL3300TReadTemperature(uint8_t *u8Data)
{
		uint16_t u8Rs = 0;
		uint8_t u8Read[4]  = {0};
		uint8_t u8Write[4]  = {0};
		Un32AndArray un32AndArrayCMD;
		
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READTMP;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);

		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		__nop();
		__nop();
		
		memcpy(u8Data, u8Read, 4);
		u8Rs = u8Read[0] & 0x03;
		return u8Rs;
}
uint16_t User_SCL3300TReadANGX(uint8_t *u8Data)
{
		uint16_t u8Rs = 0;
		uint8_t u8Read[4]  = {0};
		uint8_t u8Write[4]  = {0};
		Un32AndArray un32AndArrayCMD;
		
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READANGX;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);

		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		__nop();
		__nop();
		
		memcpy(u8Data, u8Read, 4);
		u8Rs = u8Read[0] & 0x03;
		return u8Rs;	
}
uint16_t User_SCL3300TReadANGY(uint8_t *u8Data)
{
		uint16_t u8Rs = 0;
		uint8_t u8Read[4]  = {0};
		uint8_t u8Write[4]  = {0};
		Un32AndArray un32AndArrayCMD;
		
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READANGY;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);

		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		__nop();
		__nop();
		
		memcpy(u8Data, u8Read, 4);
		u8Rs = u8Read[0] & 0x03;
		return u8Rs;		
}
uint16_t User_SCL3300TReadANGZ(uint8_t *u8Data)
{
		uint16_t u8Rs = 0;
		uint8_t u8Read[4]  = {0};
		uint8_t u8Write[4]  = {0};
		Un32AndArray un32AndArrayCMD;
		
		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READANGZ;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);

		vTaskDelay(1);
		un32AndArrayCMD.u32SCL3300CMD = SCL_READSTAT;
		u8Write[0] = un32AndArrayCMD.u8SCL3300CMD[3];
		u8Write[1] = un32AndArrayCMD.u8SCL3300CMD[2];
		u8Write[2] = un32AndArrayCMD.u8SCL3300CMD[1];
		u8Write[3] = un32AndArrayCMD.u8SCL3300CMD[0];
		User_SCL3300TransmitReceive(u8Write, u8Read);
		
		__nop();
		__nop();
		
		memcpy(u8Data, u8Read, 4);
		u8Rs = u8Read[0] & 0x03;
		return u8Rs;		
}
