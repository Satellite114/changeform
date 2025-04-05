/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
extern uint16_t MyRTC_Time[];
RTC_DateTypeDef DateToUpdate;
RTC_TimeTypeDef TimeToUpdate;

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
   */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
/* USER CODE BEGIN RTC_Init 2 */
#if 1
  DateToUpdate.Year = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
  DateToUpdate.Month = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
  DateToUpdate.Date = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
  DateToUpdate.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
  TimeToUpdate.Hours = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6);
  TimeToUpdate.Minutes = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7);
  TimeToUpdate.Seconds = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR8);

  return;
#endif

  sTime.Hours = 17;
  sTime.Minutes = 20;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_SATURDAY;
  sDate.Month = RTC_MONTH_APRIL;
  sDate.Date = 0x5;
  sDate.Year = 0x25;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 456); // Ã¥â€ â„¢Ã¥â€¦Â¥Ã¦Â â?¡Ã¥Â¿â?”Ã¤Â??
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint16_t)sDate.Year);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, (uint16_t)sDate.Month);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, (uint16_t)sDate.Date);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, (uint16_t)sDate.WeekDay);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR6, (uint16_t)sTime.Hours);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR7, (uint16_t)sTime.Minutes);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR8, (uint16_t)sTime.Seconds);

  /* USER CODE END RTC_Init 2 */
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if (rtcHandle->Instance == RTC)
  {
    /* USER CODE BEGIN RTC_MspInit 0 */

    /* USER CODE END RTC_MspInit 0 */
    /** Initializes the peripherals clock
     */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
    /* USER CODE BEGIN RTC_MspInit 1 */

    /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle)
{

  if (rtcHandle->Instance == RTC)
  {
    /* USER CODE BEGIN RTC_MspDeInit 0 */

    /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
    /* USER CODE BEGIN RTC_MspDeInit 1 */

    /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void MyRTC_ReadTime(void)
{
  HAL_RTC_GetTime(&hrtc, &TimeToUpdate, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
  MyRTC_Time[0] = DateToUpdate.Year;
  MyRTC_Time[1] = DateToUpdate.Month;
  MyRTC_Time[2] = DateToUpdate.Date;
  MyRTC_Time[3] = TimeToUpdate.Hours;
  MyRTC_Time[4] = TimeToUpdate.Minutes;
  MyRTC_Time[5] = TimeToUpdate.Seconds;
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
