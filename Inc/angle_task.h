/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs 版权所有
 ****************************************************************************
 * 文件名称             :  angle_task.h
 * 版本                 :  0.0.1
 * 作者                 :  lvchunhao
 * 创建日期             :　2019年8月29日
 * 描述                 :  SCA100T角度处理
                           1. 模拟SPI
													 2. SCA100T初始化及配置
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
	
#define  CONFIG_UART_BRAUD  0x06          //串口波特率：1-9600 2-14400 3-19200 4-38400 5-57600 6-115200 7-128000 8-256000 其他-9600
#define  CONFIG_UART_SIZE   4             //波特率地址大小
#define  CONFIG_INFO_ADDR	  0x10          //配置地址
#define  CONFIG_INFO_SIZE   64            //配置大小
	 
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
	 
#define  EN_INT      	__enable_irq();		  //系统开全局中断
#define  DIS_INT     	__disable_irq();	  //系统关全局中断
	 
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
	
		double dbTMPE;              //温度值
	  double dbAngleX;            //角度X
	  double dbAngleY;            //角度Y
	  double dbAngleZ;            //角度Z
	
	  double dbAngleOffcorr;      //温度补偿
	  double dbAngleZeroX;        //零点值X
	  double dbAngleZeroY;        //零点值Y
		double dbAngleZeroZ;        //零点值Z
	  double dbCalibratValueX;    //输入标定值
	  double dbCalibratValueY;
		double dbCalibratValueZ;
		double dbCalibratKValuX;    //标定系数
		double dbCalibratKValuY;
		double dbCalibratKValuZ;
		
		double dbCalibratTmpeX;     //标定X轴时温度
		double dbCalibratTmpeY;     //标定Y轴时温度
		double dbCalibratTmpeZ;     //标定Z轴时温度
		
		double dbAngleOffcorrX;     //补偿后的角度X
		double dbAngleOffcorrY;     //补偿后的角度Y
		double dbAngleOffcorrZ;     //补偿后的角度Z
		
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
