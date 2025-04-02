/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *wave_model;
	bool wave_model_del;
	lv_obj_t *wave_model_table_2;
	lv_obj_t *wave_model_label_27;
	lv_obj_t *wave_model_btn_1;
	lv_obj_t *wave_model_btn_1_label;
	lv_obj_t *wave_model_btn_2;
	lv_obj_t *wave_model_btn_2_label;
	lv_obj_t *wave_model_btn_3;
	lv_obj_t *wave_model_btn_3_label;
	lv_obj_t *wave_model_btn_4;
	lv_obj_t *wave_model_btn_4_label;
	lv_obj_t *wave_model_btn_5;
	lv_obj_t *wave_model_btn_5_label;
	lv_obj_t *wave_model_btn_6;
	lv_obj_t *wave_model_btn_6_label;
	lv_obj_t *wave_model_power;
	lv_obj_t *wave_model_freq;
	lv_obj_t *wave_model_yellow;
	lv_obj_t *wave_model_green;
	lv_obj_t *wave_model_blue;
	lv_obj_t *wave_model_red;
	lv_obj_t *wave_model_two;
	lv_obj_t *wave_model_three;
	lv_obj_t *wave_model_N__;
	lv_obj_t *wave_model_one_value;
	lv_obj_t *wave_model_two_value;
	lv_obj_t *wave_model_three_value;
	lv_obj_t *wave_model_label_21;
	lv_obj_t *wave_model_label_22;
	lv_obj_t *wave_model_label_23;
	lv_obj_t *wave_model_label_24;
	lv_obj_t *wave_model_label_25;
	lv_obj_t *wave_model_N_val;
	lv_obj_t *wave_model_num_1;
	lv_obj_t *wave_model_chart_2;
	lv_obj_t *wave_model_btn_7;
	lv_obj_t *wave_model_btn_7_label;
	lv_obj_t *wave_model_btn_8;
	lv_obj_t *wave_model_btn_8_label;
	lv_obj_t *wave_model_table_1;
	lv_obj_t *wave_model_label_26;
	lv_obj_t *wave_model_digital_clock_1;
	lv_obj_t *wave_model_img_1;
	lv_obj_t *wave_model_btn_9;
	lv_obj_t *wave_model_btn_9_label;
	lv_obj_t *wave_model_btn_10;
	lv_obj_t *wave_model_btn_10_label;
	lv_obj_t *wave_model_btn_11;
	lv_obj_t *wave_model_btn_11_label;
	lv_obj_t *wave_model_btn_12;
	lv_obj_t *wave_model_btn_12_label;
	lv_obj_t *wave_model_btn_13;
	lv_obj_t *wave_model_btn_13_label;
	lv_obj_t *wave_model_btn_14;
	lv_obj_t *wave_model_btn_14_label;
	lv_obj_t *wave_model_chart_3;
	lv_obj_t *wave_model_msg;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_wave_model(lv_ui *ui);
LV_IMG_DECLARE(_f7b64978f5bff1ff9d8a4bf8f3d4d9d6_alpha_520x340);

LV_FONT_DECLARE(lv_font_arial_16)
LV_FONT_DECLARE(lv_font_simsun_16)
LV_FONT_DECLARE(lv_font_simsun_12)
LV_FONT_DECLARE(lv_font_arial_32)
LV_FONT_DECLARE(lv_font_arial_30)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
