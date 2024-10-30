/****************************************************************************
 * Copyright(c), 2001-2060, ihealthlabs ��Ȩ����
 ****************************************************************************
 * �ļ�����             :  angle_task.c
 * �汾                 :  0.0.1
 * ����                 :  lvchunhao
 * ��������             :��2019��8��29��
 * ����                 :  SCA100T�Ƕȴ���
                           1. ģ��SPI
													 2. SCA100T��ʼ��������
 ****************************************************************************/
#include "common.h"


StAngleData   g_stAngleData;

double g_dbDigtalZeroAngleXY = 0.0;
double g_dbAnalogZeroAngleXY = 0.0;

uint8_t g_u8OperatePrintFlag = 0;
uint64_t g_u64TimeBase100ms  = 0x00;            //100ms
uint64_t g_u64TimeBase1000ms = 0x00;




void EEPROM_ReadBytes(uint16_t Addr, uint8_t *Buffer, uint16_t Length)
{
	uint8_t *wAddr;
	wAddr=(uint8_t *)(EEPROM_BASE_ADDR+Addr);
	while(Length--)
	{
		*Buffer++=*wAddr++;
	}	

}

void EEPROM_ReadWords(uint16_t Addr, uint16_t *Buffer, uint16_t Length)
{
	uint32_t *wAddr;
	wAddr=(uint32_t *)(EEPROM_BASE_ADDR+Addr);
	while(Length--)
	{
		*Buffer++=*wAddr++;
	}	
}


void EEPROM_WriteBytes(uint16_t Addr, uint8_t *Buffer, uint16_t Length)
{
	uint8_t *wAddr;
	wAddr=(uint8_t *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				    //unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_FTDW;		//not fast write
	while(Length--){
		*wAddr++=*Buffer++;
		while(FLASH->SR&FLASH_SR_BSY);
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}

void EEPROM_WriteWords(uint16_t Addr,uint16_t *Buffer,uint16_t Length)
{
	uint32_t *wAddr;
	wAddr=(uint32_t *)(EEPROM_BASE_ADDR+Addr);
	DIS_INT
	FLASH->PEKEYR=PEKEY1;				    //unlock
	FLASH->PEKEYR=PEKEY2;
	while(FLASH->PECR&FLASH_PECR_PELOCK);
	FLASH->PECR|=FLASH_PECR_FTDW;		//not fast write
	while(Length--){
		*wAddr++=*Buffer++;
		while(FLASH->SR&FLASH_SR_BSY);
	}
	FLASH->PECR|=FLASH_PECR_PELOCK;
	EN_INT
}

void EEPROM_WrteBytes(uint32_t u32Addr, uint32_t u32Data)
{
		HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASHEx_DATAEEPROM_Program( FLASH_TYPEPROGRAMDATA_WORD,  EEPROM_BASE_ADDR + u32Addr,  u32Data);
    //HAL_FLASHEx_DATAEEPROM_Erase(FLASH_TYPEERASEDATA_WORD, EEPROM_BASE_ADDR);
    HAL_FLASHEx_DATAEEPROM_Lock();
}

uint8_t User_ReadEEPROMUartBraudRate(void)
{
		uint8_t u8BraudRate = 1;
		Unfloat unFloatValue;
	
	  EEPROM_ReadBytes(CONFIG_UART_BRAUD, unFloatValue.u8Data, CONFIG_UART_SIZE);
	  u8BraudRate = unFloatValue.u32Value;
	
		return u8BraudRate;
}	

void User_SetEEPROMUartBraudRate(uint8_t u8BraudRate)
{
		Unfloat unFloatValue;
	
		unFloatValue.u32Value = u8BraudRate;
		if((unFloatValue.u32Value >= 1)&&(unFloatValue.u32Value <= 8))
		{
				EEPROM_WrteBytes(CONFIG_UART_BRAUD, unFloatValue.u32Value);
		}	
	
}


void User_ReadEEPROMConfig(void)
{
	  uint8_t u8AngleConfigData[CONFIG_INFO_SIZE] = {0};
		Unfloat unFloatValue;
	
	  /* ��ȡE2PPROM�������� */
		EEPROM_ReadBytes(CONFIG_INFO_ADDR, u8AngleConfigData, CONFIG_INFO_SIZE);
		memcpy(unFloatValue.u8Data, u8AngleConfigData+0, 4);
		g_stAngleData.dbAngleZeroX = unFloatValue.ftValue;
		memcpy(unFloatValue.u8Data, u8AngleConfigData+4, 4);
		g_stAngleData.dbAngleZeroY = unFloatValue.ftValue;
		memcpy(unFloatValue.u8Data, u8AngleConfigData+8, 4);
		g_stAngleData.dbAngleZeroZ = unFloatValue.ftValue;
		
		/* X�����+Y�����+X��궨ϵ��+Y��궨ϵ�� */
		memcpy(unFloatValue.u8Data, u8AngleConfigData+12, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratKValuX = 1.0;
		}
		else{
			  g_stAngleData.dbCalibratKValuX = unFloatValue.ftValue;
		}
		
		memcpy(unFloatValue.u8Data, u8AngleConfigData+16, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratKValuY = 1.0;
		}
		else{
			  g_stAngleData.dbCalibratKValuY = unFloatValue.ftValue;
		}
		
		memcpy(unFloatValue.u8Data, u8AngleConfigData+20, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratKValuZ = 1.0;
		}
		else{
			  g_stAngleData.dbCalibratKValuZ = unFloatValue.ftValue;
		}
		
		/* X��Y��Z��궨ʱ���¶� */
		memcpy(unFloatValue.u8Data, u8AngleConfigData+24, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratTmpeX = 25.0;
		}
		else{
			  g_stAngleData.dbCalibratTmpeX = unFloatValue.ftValue;
		}
		
		memcpy(unFloatValue.u8Data, u8AngleConfigData+28, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratTmpeY = 25.0;
		}
		else{
			  g_stAngleData.dbCalibratTmpeY = unFloatValue.ftValue;
		}
		
		memcpy(unFloatValue.u8Data, u8AngleConfigData+32, 4);
		if(unFloatValue.ftValue == 0){
				g_stAngleData.dbCalibratTmpeZ = 25.0;
		}
		else{
			  g_stAngleData.dbCalibratTmpeZ = unFloatValue.ftValue;
		}
}
		

TickType_t xNowTime, xNextTime;
uint32_t g_u32TemperatureCnt = 0;      //�¶Ȼ�ȡ����
double g_dbTemperatureRate = 0.0;      //�¶ȱ仯��
double g_dbTemperatureLast = 0.0;      //1minǰ�¶�
double g_dbTemperatureVale = 0.00286;  //����ϵ��
/*
 * ������    ��vTaskOperationAngle()
 * ����      : �Ƕȴ�����
 * ����      : pArgs [in] : �̲߳���
 * ����      : none
 * ����      : lyuchunhao 2019-8-29
 */
void vTaskOperationAngle(void *pArgs)
{
		uint8_t u8Ret = 0;
		uint8_t u8TmpData[4];
	  uint16_t u16TmpADCValue = 0;
	  uint32_t i = 0;
	  //double dbTmpValue = 0.0;
	
		//EEPROM��ʱ
		vTaskDelay(100);
		User_ReadEEPROMConfig();
	
	  //SCL3300��ʼ��
		PostUartWriteMsg((uint8_t *)"vTaskOperationAngle is Start!\n", 30);
		User_SCL3300Init();
		
		//���ڷ���
	  vTaskDelay(3);
		PRINT("Config Data: %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f\n", g_stAngleData.dbAngleZeroX, \
					g_stAngleData.dbAngleZeroY,g_stAngleData.dbAngleZeroZ,g_stAngleData.dbCalibratKValuX,\
					g_stAngleData.dbCalibratKValuY,g_stAngleData.dbCalibratKValuZ,\
	        g_stAngleData.dbCalibratTmpeX, g_stAngleData.dbCalibratTmpeY, g_stAngleData.dbCalibratTmpeZ);
	
	  //u8Ret = User_ReadEEPROMUartBraudRate();
		PRINT("BraudRate: %d\n", g_u8UartBraudRate);
	
		vTaskDelay(10);
		g_stAngleData.u16TMPEIndex = 0;
		g_stAngleData.u16AxOUTxIndex = 0;
		
		g_u64TimeBase1000ms = 0;
		g_u64TimeBase1000ms = 0;
		xNextTime = xTaskGetTickCount();
	
		while(1)
		{
		
			/* CPOL = 0 CPHA = 0 */
			/* SPIΪ32λ4�ߴӻ���������+SCK�����ط���/�½��ؽ��� */
			/* SPI����ʱ��2M-4M + ����֮��������10us*/
			/* ��ȡSCL3300-D01�ڲ�16bit�Ƕ�:�����Բ� */
			
			/**************************************************************************************************/
			//X�������ԭʼ���
			u8Ret = User_SCL3300TReadANGX(u8TmpData);
			if(u8Ret == 0x01)
			{
					u16TmpADCValue = u8TmpData[2] + 256*u8TmpData[1];
				  g_stAngleData.u16ANGX[g_stAngleData.u16AxOUTxIndex] = u16TmpADCValue;
          g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex] = (double)u16TmpADCValue/16384*90;	
          if(g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex] > 180)
          {
							g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex] = g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex] - 360.0;
					}						
			}
			else
			{
					//PRINT("Read AngX error\n");
			}
			
			//Y�������ԭʼ���
			u8Ret = User_SCL3300TReadANGY(u8TmpData);
			if(u8Ret == 0x01)
			{
					u16TmpADCValue = u8TmpData[2] + 256*u8TmpData[1];
				  g_stAngleData.u16ANGY[g_stAngleData.u16AxOUTxIndex] = u16TmpADCValue;	
          g_stAngleData.dbANGY[g_stAngleData.u16AxOUTxIndex] = (double)u16TmpADCValue/16384*90;	
          if(g_stAngleData.dbANGY[g_stAngleData.u16AxOUTxIndex] > 180)
          {
							g_stAngleData.dbANGY[g_stAngleData.u16AxOUTxIndex] = g_stAngleData.dbANGY[g_stAngleData.u16AxOUTxIndex] - 360.0;
					}					
			}
			else
			{
					//PRINT("Read AngY error\n");
			}		
			
			#if 1
			//Z�������ԭʼ���
			u8Ret = User_SCL3300TReadANGZ(u8TmpData);
			if(u8Ret == 0x01)
			{
					u16TmpADCValue = u8TmpData[2] + 256*u8TmpData[1];
				  g_stAngleData.u16ANGZ[g_stAngleData.u16AxOUTxIndex] = u16TmpADCValue;	
          g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] = (double)u16TmpADCValue/16384*90;	
          if(g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] > 180)
          {
							g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] = g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] - 360.0;
					}					
			}
			else
			{
					//PRINT("Read AngZ error\n");
			}
			#else
			/*
			//A�����=arctan(fabs(Y/X))*180.0/PI
			dbTmpValue = fabs(g_stAngleData.dbANGY[g_stAngleData.u16AxOUTxIndex]/g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex]);
			g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] = atan(dbTmpValue)*180.0/PI;
			if(g_stAngleData.dbANGX[g_stAngleData.u16AxOUTxIndex] * g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] >= 0)
			{
					g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] = g_stAngleData.dbANGZ[g_stAngleData.u16AxOUTxIndex] * -1.0;
			}*/
			#endif
			
			//ԭʼ�¶����
			u8Ret = User_SCL3300TReadTemperature(u8TmpData);
			if(u8Ret == 0x01)
			{
					u16TmpADCValue = u8TmpData[2] + 256*u8TmpData[1];
				  g_stAngleData.u16TMPE[g_stAngleData.u16AxOUTxIndex] = u16TmpADCValue;
				  g_stAngleData.dbTMPR[g_stAngleData.u16AxOUTxIndex] = -273 + ((double)u16TmpADCValue/18.9);
			}
			else
			{
					//PRINT("Read TemP error\n");
			}
			
			/* ����ƫ�� */
			g_stAngleData.u16AxOUTxIndex++;
			if(g_stAngleData.u16AxOUTxIndex >= ADS_BUFF_SIZE)
			{
					g_stAngleData.u16AxOUTxIndex = 0;
			}
				
			/* ���սǶȣ�ƽ������ */
			g_stAngleData.dbAverageANGX = 0.0;
			g_stAngleData.dbAverageANGY = 0.0;
			g_stAngleData.dbAverageANGZ = 0.0;
			g_stAngleData.dbAverageTMPE = 0.0;
			for(i = 0; i < ADS_BUFF_SIZE; i ++)
			{
					g_stAngleData.dbAverageANGX += g_stAngleData.dbANGX[i];
					g_stAngleData.dbAverageANGY += g_stAngleData.dbANGY[i];
					g_stAngleData.dbAverageANGZ += g_stAngleData.dbANGZ[i];
					g_stAngleData.dbAverageTMPE += g_stAngleData.dbTMPR[i];
			}
			g_stAngleData.dbAngleX = g_stAngleData.dbAverageANGX/ADS_BUFF_SIZE;
			g_stAngleData.dbAngleY = g_stAngleData.dbAverageANGY/ADS_BUFF_SIZE;
			g_stAngleData.dbAngleZ = g_stAngleData.dbAverageANGZ/ADS_BUFF_SIZE;
			g_stAngleData.dbTMPE   = g_stAngleData.dbAverageTMPE/ADS_BUFF_SIZE;

			
			#if 0
			//�¶Ȳ����㷨3��Modify by lvch@2020-06-07 15:56
			//���ݱ궨ʱ���¶�ֵ���в���(�¶��½�1��Ƕ��������0.007��)
			//�¶�����,�Ƕȼ�ȥ����ֵ/�¶��½�,�Ƕȼ��ϲ���ֵ
			g_stAngleData.dbAngleOffcorrX = g_stAngleData.dbAngleX + (g_stAngleData.dbCalibratTmpeX - g_stAngleData.dbTMPE)\
					*(float)AGNLE_OFFSET_VALUE;
			g_stAngleData.dbAngleOffcorrY = g_stAngleData.dbAngleY + (g_stAngleData.dbCalibratTmpeY - g_stAngleData.dbTMPE)\
					*(float)AGNLE_OFFSET_VALUE;
			g_stAngleData.dbAngleOffcorrZ = g_stAngleData.dbAngleZ + (g_stAngleData.dbCalibratTmpeZ - g_stAngleData.dbTMPE)\
					*(float)AGNLE_OFFSET_VALUE;
			#endif
			
			#if 0
			//�¶Ȳ����㷨4��Modify by lvch@2022-01-12
			//�ο�<<�Ƕ�ģ���¶Ȳ����㷨����20220112-���ų�>>
			//�¶ȱ�25Cÿ����1C����-0.00286 ����1C����+0.00286��궨ʱ���¶��޹�
			g_stAngleData.dbAngleOffcorrX = g_stAngleData.dbAngleX - (g_stAngleData.dbTMPE - 25.0)*(float)AGNLE_OFFSET_VALUE;
			g_stAngleData.dbAngleOffcorrY = g_stAngleData.dbAngleY - (g_stAngleData.dbTMPE - 25.0)*(float)AGNLE_OFFSET_VALUE;
			g_stAngleData.dbAngleOffcorrZ = g_stAngleData.dbAngleZ - (g_stAngleData.dbTMPE - 25.0)*(float)AGNLE_OFFSET_VALUE;			
			#endif
			
			//�¶Ȳ����㷨5��Modify by lvch@2022-01-20
			//��̬��������ϵ���ο�<<�²��㷨20220120.doc>>
			g_u32TemperatureCnt++;
			if((g_u32TemperatureCnt == ADS_BUFF_SIZE) && (g_u64TimeBase1000ms == 0))
			{
				  g_dbTemperatureLast = g_stAngleData.dbTMPE;
			}
			xNowTime = xTaskGetTickCount();
			if(xNowTime >= xNextTime + 1000*60)
			{
				  g_u64TimeBase1000ms++;
					xNextTime = xTaskGetTickCount();

					//�¶ȱ仯��1min�¶ȱ仯
				  g_dbTemperatureRate = g_stAngleData.dbTMPE - g_dbTemperatureLast;
					g_dbTemperatureRate = fabs(g_dbTemperatureRate);
					g_dbTemperatureLast = g_stAngleData.dbTMPE;
				  
				  //�����¶Ȳ���ϵ��
				  if(g_dbTemperatureRate <= 0.1)
					{
							g_dbTemperatureVale = 0.00286;
					}
					else if(g_dbTemperatureRate < 0.25)
					{
							g_dbTemperatureVale = 0.00313;
					}
					else if(g_dbTemperatureRate < 0.35)
					{
							g_dbTemperatureVale = 0.00341;						
					}
					else
					{
							g_dbTemperatureVale = 0.00396;						
					}
			}
			
			//����25C -���� С��25C +����
			g_stAngleData.dbAngleOffcorrX = g_stAngleData.dbAngleX - (g_stAngleData.dbTMPE - 25.0)*g_dbTemperatureVale;
			g_stAngleData.dbAngleOffcorrY = g_stAngleData.dbAngleY - (g_stAngleData.dbTMPE - 25.0)*g_dbTemperatureVale;
			g_stAngleData.dbAngleOffcorrZ = g_stAngleData.dbAngleZ - (g_stAngleData.dbTMPE - 25.0)*g_dbTemperatureVale;	
			
			
			#if 0
			//�¶Ȳ����㷨2��Modify by lvch@2020-06-28(Լ1s����̫׼ȷ)
			xNowTime = xTaskGetTickCount();
			if(xNowTime >= xNextTime + 1000)
			{
				  g_u64TimeBase1000ms++;
					xNextTime = xTaskGetTickCount();
				
					g_stAngleData.dbTMPEBuff[g_stAngleData.u16TMPEIndex] = g_stAngleData.dbTMPE;
					g_stAngleData.u16TMPEIndex++;
					if(g_stAngleData.u16TMPEIndex >= 6)
					{
							g_stAngleData.u16TMPEIndex = 0;
					}
					
					//����10s��ʼ���㲹������
					if(g_u64TimeBase1000ms >= 10)
					{
							//�¶ȱ仯�� = ��ǰ�¶� - 6sǰ�¶�
							dbTmpValue = g_stAngleData.dbTMPE - g_stAngleData.dbTMPEBuff[g_stAngleData.u16TMPEIndex];
							//��Ưϵ�� = 0.0322*�¶ȱ仯�� - 0.00186
							g_stAngleData.dbTMPEOffCorrY = 0.0322*(dbTmpValue/6) - 0.00186;
					}
			}
			//�¶Ȳ��� = ����ǰ�Ƕ� - (��Ưϵ��*�¶ȱ仯��)
			g_stAngleData.dbAngleOffcorrY = g_stAngleData.dbAngleY - (g_stAngleData.dbTMPEOffCorrY*dbTmpValue);
			#endif
			
			
			#if 0
			//Modify by lvch@2019-12-29
			//Z��ر��ɷ�����arctan(abs(Y/X))
			dbTmpValue = fabs(g_stAngleData.dbAngleY/g_stAngleData.dbAngleX);
			g_stAngleData.dbAngleZ = atan(dbTmpValue)*180.0/PI;;
			if(g_stAngleData.dbAngleY * g_stAngleData.dbAngleZ >= 0)
			{
					g_stAngleData.dbAngleZ = g_stAngleData.dbAngleZ * -1.0;
			}
			#else
			//Modify by lvch@2019-12-30
			//Ҫ��ر�A�����,Y��ȡ�� 
			/*
			g_stAngleData.dbAngleY = g_stAngleData.dbAngleY * (-1.0);
			g_stAngleData.dbAngleX = g_stAngleData.dbAngleZ;
			*/
			#endif
			/**************************************************************************************************/
			
			vTaskDelay(1);
			
		}	
	
}



/*
 * ������    ��vTaskStaticOpration()
 * ����      : ͳ���߳�
 * ����      : pArgs [in] : �̲߳���
 * ����      : none
 * ����      : lyuchunhao 2019-8-29
 */
void vTaskStaticOpration(void *pArgs)
{
	  TickType_t xDelay, xNextTime;
    const TickType_t xFrequency = 100;		
	  
	  vTaskDelay(30);
	  g_u64TimeBase100ms = 0;
	  PostUartWriteMsg((uint8_t *)"vTaskStaticOpn is Start!\n", 25);
	  xNextTime = xTaskGetTickCount() + xFrequency;
	
		while(1)
		{
				
				/* ��vTaskDelayʵ��vTaskDelayUntil() */
        xDelay = xNextTime - xTaskGetTickCount();
        xNextTime += xFrequency;
        
        if(xDelay <= xFrequency)
        {
            vTaskDelay(xDelay);
        }
				
				g_u64TimeBase100ms++;
		}
	
}



