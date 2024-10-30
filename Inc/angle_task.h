/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             :  angle_task.h
 * �汾                 :  0.0.1
 * ����                 :  lvchunhao
 * ��������             :��2019��8��29��
 * ����                 :  SCA100T�Ƕȴ���
                           1. ģ��SPI
													 2. SCA100T��ʼ��������
 ****************************************************************************/
 
#ifndef _ANGLE_TASK_H
#define _ANGLE_TASK_H

#include "common.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#define  ADS_BUFF_SIZE      20	
//#define  AGNLE_OFFSET_VALUE 0.0056	 
#define  AGNLE_OFFSET_VALUE 0.00286	
	
#define  CONFIG_UART_BRAUD  0x06          //���ڲ����ʣ�1-9600 2-14400 3-19200 4-38400 5-57600 6-115200 7-128000 8-256000 ����-9600
#define  CONFIG_UART_SIZE   4             //�����ʵ�ַ��С
#define  CONFIG_INFO_ADDR	  0x10          //���õ�ַ
#define  CONFIG_INFO_SIZE   64            //���ô�С
	 
#define  ANGLE_XZ_ADDR      CONFIG_INFO_ADDR+0
#define  ANGLE_YZ_ADDR      CONFIG_INFO_ADDR+4
#define  ANGLE_ZZ_ADDR      CONFIG_INFO_ADDR+8
#define  ANGLE_KX_ADDR      CONFIG_INFO_ADDR+12
#define  ANGLE_KY_ADDR      CONFIG_INFO_ADDR+16
#define  ANGLE_KZ_ADDR      CONFIG_INFO_ADDR+20

#define  ANGLE_TX_ADDR      CONFIG_INFO_ADDR+24
#define  ANGLE_TY_ADDR      CONFIG_INFO_ADDR+28
#define  ANGLE_TZ_ADDR      CONFIG_INFO_ADDR+32

#define  EEPROM_BASE_ADDR		0x08080000	
#define  EEPROM_BYTE_SIZE		0x0FFF
#define  PEKEY1							0x89ABCDEF		//FLASH_PEKEYR
#define  PEKEY2							0x02030405		//FLASH_PEKEYR
	 
#define  EN_INT      	__enable_irq();		  //ϵͳ��ȫ���ж�
#define  DIS_INT     	__disable_irq();	  //ϵͳ��ȫ���ж�
	 
typedef union tag_Unfloat
{
		float    ftValue;
	  uint8_t  u8Data[4];
		uint32_t u32Value;
}Unfloat;
	 
typedef struct tag_StADS126xData{
		uint32_t u32ADValue;
		uint8_t  u8ADStatus;
		uint8_t  u8ADCheckSum;
}StADS126xData;
	 
typedef struct tag_StSCA100TData{
		uint16_t u16AngleX;
		uint16_t u16AngleY;
		uint16_t u16AngleXY;
	  uint16_t u16AngleTp;
	
		double dbAngleX;
	  double dbAngleY;
		double dbAngleXY;
	  double dbAngleTp;
}StSCA100TData;	 
	 
typedef struct tag_StAngleData{
	  uint16_t u16TMPEIndex;
	  uint16_t u16AxOUTxIndex;
		uint16_t u16ANGX[ADS_BUFF_SIZE];
		uint16_t u16ANGY[ADS_BUFF_SIZE];
		uint16_t u16ANGZ[ADS_BUFF_SIZE];
	  uint16_t u16TMPE[ADS_BUFF_SIZE];
	
		double dbANGX[ADS_BUFF_SIZE];
		double dbANGY[ADS_BUFF_SIZE];
		double dbANGZ[ADS_BUFF_SIZE];
	  double dbTMPR[ADS_BUFF_SIZE];
	
		double dbAverageANGX;
		double dbAverageANGY;
		double dbAverageANGZ;
		double dbAverageTMPE;
	
		double dbTMPE;              //�¶�ֵ
	  double dbAngleX;            //�Ƕ�X
	  double dbAngleY;            //�Ƕ�Y
	  double dbAngleZ;            //�Ƕ�Z
	
	  double dbAngleOffcorr;      //�¶Ȳ���
	  double dbAngleZeroX;        //���ֵX
	  double dbAngleZeroY;        //���ֵY
		double dbAngleZeroZ;        //���ֵZ
	  double dbCalibratValueX;    //����궨ֵ
	  double dbCalibratValueY;
		double dbCalibratValueZ;
		double dbCalibratKValuX;    //�궨ϵ��
		double dbCalibratKValuY;
		double dbCalibratKValuZ;
		
		double dbCalibratTmpeX;     //�궨X��ʱ�¶�
		double dbCalibratTmpeY;     //�궨Y��ʱ�¶�
		double dbCalibratTmpeZ;     //�궨Z��ʱ�¶�
		
		double dbAngleOffcorrX;     //������ĽǶ�X
		double dbAngleOffcorrY;     //������ĽǶ�Y
		double dbAngleOffcorrZ;     //������ĽǶ�Z
		
		double dbTMPEBuff[6];
		double dbTMPEOffCorrY;

}StAngleData;
	 
extern double g_dbDigtalZeroAngleXY;
extern double g_dbAnalogZeroAngleXY;
extern StAngleData   g_stAngleData;
extern uint8_t g_u8OperatePrintFlag;
	
void vTaskStaticOpration(void *pArgs);
void vTaskOperationAngle(void *pArgs);	 
StADS126xData User_ADS126xReadADC1(void);	 

void EEPROM_ReadBytes(uint16_t Addr, uint8_t *Buffer, uint16_t Length);
void EEPROM_WrteBytes(uint32_t u32Addr, uint32_t u32Data);
	 
uint8_t User_ReadEEPROMUartBraudRate(void);
void User_SetEEPROMUartBraudRate(uint8_t u8BraudRate);

#ifdef __cplusplus
}
#endif

#endif /* _ANGLE_TASK_H */
