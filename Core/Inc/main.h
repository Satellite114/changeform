/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define rsv_OUT_PE3_Pin GPIO_PIN_3
#define rsv_OUT_PE3_GPIO_Port GPIOE
#define rsv_OUT_PC13_Pin GPIO_PIN_13
#define rsv_OUT_PC13_GPIO_Port GPIOC
#define ETH_RST_Pin GPIO_PIN_2
#define ETH_RST_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_11
#define LCD_RST_GPIO_Port GPIOD
#define rsv_OUT_PG3_Pin GPIO_PIN_3
#define rsv_OUT_PG3_GPIO_Port GPIOG
#define ADC_STBY_Pin GPIO_PIN_7
#define ADC_STBY_GPIO_Port GPIOG
#define rsv_OUT_PA8_Pin GPIO_PIN_8
#define rsv_OUT_PA8_GPIO_Port GPIOA
#define rsv_OUT_PA9_Pin GPIO_PIN_9
#define rsv_OUT_PA9_GPIO_Port GPIOA
#define rsv_OUT_PA10_Pin GPIO_PIN_10
#define rsv_OUT_PA10_GPIO_Port GPIOA
#define SD_det_Pin GPIO_PIN_3
#define SD_det_GPIO_Port GPIOD
#define ADC_RST_Pin GPIO_PIN_10
#define ADC_RST_GPIO_Port GPIOG
#define SKEY_Pin GPIO_PIN_13
#define SKEY_GPIO_Port GPIOG
#define PG14_Pin GPIO_PIN_14
#define PG14_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
