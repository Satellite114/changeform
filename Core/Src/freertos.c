/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lwip/apps/httpd.h"
#include "ad7606.h"
#include "lcd.h"
#include "gui_guider.h"
#include "arm_math.h"
#include "tim.h"
#include "dsp_fft.h"
#include "lvgl.h"
#include "lv_chart.h"
#include "task.h"
#include "task_page1.h"
#include "gpio.h"
#include "sdmmc.h"
#include "events_init.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
ALIGN_32BYTES(FFT fft_1V)
__attribute__((section(".SDRAM")));

ALIGN_32BYTES(FFT fft_2V)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(FFT fft_3V)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(FFT fft_NV)
__attribute__((section(".SDRAM")));

ALIGN_32BYTES(FFT fft_1I)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(FFT fft_2I)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(FFT fft_3I)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(FFT fft_NI)
__attribute__((section(".SDRAM")));

ALIGN_32BYTES(phase P1)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(phase P2)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(phase P3)
__attribute__((section(".SDRAM")));
ALIGN_32BYTES(phase PN)
__attribute__((section(".SDRAM")));

ALIGN_32BYTES(Voltage_three Voltage)
__attribute__((section(".SDRAM")));

lv_chart_series_t *ser1;
lv_chart_series_t *ser2;
lv_chart_series_t *ser3;
lv_chart_series_t *serN;

lv_chart_series_t *ser1_I;
lv_chart_series_t *ser2_I;
lv_chart_series_t *ser3_I;
lv_chart_series_t *serN_I;
extern uint8_t V_I_flag;
extern uint8_t L1_flag;
extern uint8_t L2_flag;
extern uint8_t L3_flag;
extern uint8_t LN_flag;
extern uint8_t L1_I_flag;
extern uint8_t L2_I_flag;
extern uint8_t L3_I_flag;
extern uint8_t LN_I_flag;
extern AD7606Dev ad7606dev;
extern SD_HandleTypeDef hsd1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId refersh_lvglHandle;
osThreadId task_FFTHandle;
osThreadId task_lvglHandle;
osSemaphoreId EVENT_ADCHandle;
osSemaphoreId EVENT_FFTHandle;
osSemaphoreId EVENT_LVGL_REFERSHHandle;
osSemaphoreId EVENT_LVGL_TASKHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Refersh_LVGL(void const *argument);
void TASK_FFT(void const *argument);
void TASK_LVGL(void const *argument);
void init_form_stop();
extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* Hook prototypes */
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
  /* vApplicationMallocFailedHook() will only be called if
  configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
  function that will get called if a call to pvPortMalloc() fails.
  pvPortMalloc() is called internally by the kernel whenever a task, queue,
  timer or semaphore is created. It is also called by various parts of the
  demo application. If heap_1.c or heap_2.c are used, then the size of the
  heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
  FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
  to query the size of free heap space that remains (although it does not
  provide information on how the remaining heap might be fragmented). */
  printf("malloc fail\r\n");
  while (1)
  {

    HAL_GPIO_TogglePin(PG14_GPIO_Port, PG14_Pin);
    osDelay(200);
  }
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of EVENT_ADC */
  osSemaphoreDef(EVENT_ADC);
  EVENT_ADCHandle = osSemaphoreCreate(osSemaphore(EVENT_ADC), 1);

  /* definition and creation of EVENT_FFT */
  osSemaphoreDef(EVENT_FFT);
  EVENT_FFTHandle = osSemaphoreCreate(osSemaphore(EVENT_FFT), 1);

  /* definition and creation of EVENT_LVGL_REFERSH */
  osSemaphoreDef(EVENT_LVGL_REFERSH);
  EVENT_LVGL_REFERSHHandle = osSemaphoreCreate(osSemaphore(EVENT_LVGL_REFERSH), 1);

  /* definition and creation of EVENT_LVGL_TASK */
  osSemaphoreDef(EVENT_LVGL_TASK);
  EVENT_LVGL_TASKHandle = osSemaphoreCreate(osSemaphore(EVENT_LVGL_TASK), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of refersh_lvgl */
  osThreadDef(refersh_lvgl, Refersh_LVGL, osPriorityAboveNormal, 0, 1024);
  refersh_lvglHandle = osThreadCreate(osThread(refersh_lvgl), NULL);

  /* definition and creation of task_FFT */
  osThreadDef(task_FFT, TASK_FFT, osPriorityNormal, 0, 1300);
  task_FFTHandle = osThreadCreate(osThread(task_FFT), NULL);

  /* definition and creation of task_lvgl */
  osThreadDef(task_lvgl, TASK_LVGL, osPriorityNormal, 0, 1300);
  task_lvglHandle = osThreadCreate(osThread(task_lvgl), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_Refersh_LVGL */
/**
 * @brief  Function implementing the refersh_lvgl thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Refersh_LVGL */
void Refersh_LVGL(void const *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN Refersh_LVGL */
  httpd_init();
  FFT_Init(&fft_1V, SAMPLING, FFT_LENGTH, 1); // 1表示电压
  FFT_Init(&fft_2V, SAMPLING, FFT_LENGTH, 1);
  FFT_Init(&fft_3V, SAMPLING, FFT_LENGTH, 1);
  FFT_Init(&fft_NV, SAMPLING, FFT_LENGTH, 1);

  FFT_Init(&fft_1I, SAMPLING, FFT_LENGTH, 0); // 0表示电流
  FFT_Init(&fft_2I, SAMPLING, FFT_LENGTH, 0);
  FFT_Init(&fft_3I, SAMPLING, FFT_LENGTH, 0);
  FFT_Init(&fft_NI, SAMPLING, FFT_LENGTH, 0);

  PHASE_Init(&P1, &fft_1V, &fft_1I);
  PHASE_Init(&P2, &fft_2V, &fft_2I);
  PHASE_Init(&P3, &fft_3V, &fft_3I);
  PHASE_Init(&PN, &fft_NV, &fft_NI);

  Voltage_three_Init(&Voltage, &P1, &P2, &P3);
  /* Infinite loop */
  for (;;)
  {

    // test

    if (lv_disp_get_inactive_time(NULL) < 60000)
    {
      lv_task_handler();
      if(lv_disp_get_inactive_time(NULL) > 30000)
      {
        msg_notice(guider_ui.wave_model_msg, 30000, "30 seconds enters sleep mode");
      }
    }
    /*Sleep after 60 sec inactivity*/
    else
    {
      // // while (!lv_anim_count_running())
      // //   ;
      // 允许外设唤醒系统
      // HAL_SuspendTick(); // 关闭 SysTick 定时器（防止唤醒）

      // GPIO_InitTypeDef GPIO_InitStruct = {0};
      // GPIO_InitStruct.Pin = SKEY_Pin;
      // GPIO_InitStruct.Mode = GPIO_MODE_EVT_FALLING;
      // GPIO_InitStruct.Pull = GPIO_PULLUP;
      // HAL_GPIO_Init(SKEY_GPIO_Port, &GPIO_InitStruct);
      // Display_OFF();
      // // 进入 Stop 模式
      // HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    }
    osDelay(30);
  }
  /* USER CODE END Refersh_LVGL */
}

/* USER CODE BEGIN Header_TASK_FFT */
/**
 * @brief Function implementing the task_FFT thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TASK_FFT */
void TASK_FFT(void const *argument)
{
  /* USER CODE BEGIN TASK_FFT */
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  //HAL_TIMEx_PWMN_Start(&htim8, TIM_CHANNEL_3);
  /* Infinite loop */
  for (;;)
  {
    fft_run(&fft_1V);
    fft_run(&fft_2V);
    fft_run(&fft_3V);
    fft_run(&fft_NV);

    fft_run(&fft_1I);
    fft_run(&fft_2I);
    fft_run(&fft_3I);
    fft_run(&fft_NI);

    PHASE_run(&P1);
    PHASE_run(&P2);
    PHASE_run(&P3);
    PHASE_run(&PN);

    Voltage_three_run(&Voltage);
   // HAL_TIMEx_PWMN_Start(&htim8, TIM_CHANNEL_3);
    osDelay(100);
  }
  /* USER CODE END TASK_FFT */
}

/* USER CODE BEGIN Header_TASK_LVGL */
/**
 * @brief Function implementing the task_lvgl thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TASK_LVGL */
void TASK_LVGL(void const *argument)
{
  /* USER CODE BEGIN TASK_LVGL */
  page_init();
  ser1 = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);
  ser2 = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
  ser3 = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  serN = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser1, fft_1V.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser2, fft_2V.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser3, fft_3V.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, serN, fft_NV.LVGL_wave);

  ser1_I = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);
  ser2_I = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
  ser3_I = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  serN_I = lv_chart_add_series(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  ser1_I->hidden = 1;
  ser2_I->hidden = 1;
  ser3_I->hidden = 1;
  serN_I->hidden = 1;
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser1_I, fft_1I.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser2_I, fft_2I.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, ser3_I, fft_3I.LVGL_wave);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_2, serN_I, fft_NI.LVGL_wave);

  lv_chart_series_t *ser_xb_1 = lv_chart_add_series(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_series_t *ser_xb_2 = lv_chart_add_series(guider_ui.wave_model_chart_3, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_series_t *ser_xb_3 = lv_chart_add_series(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_3, ser_xb_1, fft_1V.LVGL_xb);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_3, ser_xb_2, fft_2V.LVGL_xb);
  lv_chart_set_ext_y_array(guider_ui.wave_model_chart_3, ser_xb_3, fft_3V.LVGL_xb);
  /* Infinite loop */
  for (;;)
  {
    task_page();
    osDelay(1000);
  }
  /* USER CODE END TASK_LVGL */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/**
 * @brief  EXTI line detection callback.
 * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
/* NOTE::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
              __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
This function Should not be modified in the hal_gpio file, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // GPIO_PIN_12 == ADC Complete interrupt
  if (GPIO_Pin == GPIO_PIN_12)
  {
    Get_AD7606();
  }
  if (GPIO_Pin == SKEY_Pin)
  {
    // 重新初始化外设
    init_form_stop();
  }
}
void init_form_stop()
{
  // 1. 重新配置时钟
  SystemClock_Config();

  // 2. 恢复 tick
  HAL_ResumeTick();

  // 3. 重新初始化需要的外设
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();

  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_SPI4_Init();

  MX_I2C1_Init();
  MX_I2C4_Init();

  MX_SDMMC1_SD_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_QUADSPI_Init();

  // 若用 ADC / 定时器：
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();

  SystemClock_Config();
  HAL_ResumeTick();

  MX_FATFS_Init();
  lv_port_fs_init();
  lv_port_disp_init();
  lv_port_indev_init();

  HAL_SD_MspInit(&hsd1);
  HAL_TIM_Base_Start_IT(&htim1);
  ad7606ini(&ad7606dev);
  FatFs_Check();
  Display_Text(250, 230, 1, "WAKE UP");
  Display_ON();
  HAL_Delay(5000);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
