/**
  ******************************************************************************
  * File Name          : FMC.h
  * Description        : This file provides code for the configuration
  *                      of the FMC peripheral.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FMC_H
#define __FMC_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



static FMC_SDRAM_CommandTypeDef Command;   //ĺŽäšSDRAMĺ˝äť¤çťćä˝?
#define sdramHandle hsdram1  
#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)  //ĺŽäščśćśćśé´

/**
  * @brief  FMC SDRAM ć°ćŽĺşĺ°ĺ?
  */   
 #define SDRAM_BANK_ADDR     ((uint32_t)0xC0000000)




/**
  * @brief  FMC SDRAM ć¨Ąĺźéç˝ŽçĺŻĺ­ĺ¨ç¸ĺłĺŽäš
  */
 #define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
 #define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
 #define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
 #define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
 #define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
 #define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
 #define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
 #define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
 #define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
 #define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
 #define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)   
 





extern SRAM_HandleTypeDef hsram1;
extern SRAM_HandleTypeDef hsram2;
extern SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */



void MX_FMC_Init(void);
void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram);
void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram);
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram);
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__FMC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
