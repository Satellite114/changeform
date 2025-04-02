
/**
 * @file lv_port_indev_templ.h
 *
 */

 /*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
 #if 1

 #ifndef LV_PORT_INDEV_H
 #define LV_PORT_INDEV_TH
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /*********************
  *      INCLUDES
  *********************/
 #include "lvgl.h"
 #include "gpio.h"
 #include "main.h"
 #include "tim.h"
 
 /*********************
  *      DEFINES
  *********************/
 void lv_port_indev_init(void);
 
 /**********************
  *      TYPEDEFS
  **********************/
 
 /**********************
  * GLOBAL PROTOTYPES
  **********************/
 #define EC_K  HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)
 /**********************
  *      MACROS
  **********************/

 #ifdef __cplusplus
 } /*extern "C"*/
 #endif
 
 #endif /*LV_PORT_INDEV_TEMPL_H*/
 
 #endif /*Disable/Enable content*/
 