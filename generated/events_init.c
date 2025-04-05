/*
 * Copyright 2025 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "arm_math.h"
#include "task.h"
#include "screenshot.h"
int16_t sd_count;
int16_t file_now = 0;

static int8_t page = 0;
extern lv_chart_series_t *ser1;
extern lv_chart_series_t *ser2;
extern lv_chart_series_t *ser3;
extern lv_chart_series_t *serN;

extern lv_chart_series_t *ser1_I;
extern lv_chart_series_t *ser2_I;
extern lv_chart_series_t *ser3_I;
extern lv_chart_series_t *serN_I;
extern int wave_model_digital_clock_1_min_value;
extern int wave_model_digital_clock_1_hour_value;
extern int wave_model_digital_clock_1_sec_value;
uint8_t L1_flag = 0;
uint8_t L2_flag = 0;
uint8_t L3_flag = 0;
uint8_t LN_flag = 0;
uint8_t L1_I_flag = 0;
uint8_t L2_I_flag = 0;
uint8_t L3_I_flag = 0;
uint8_t LN_I_flag = 0;
float32_t rat = 50;
float32_t step = 2;
float32_t level = 0;
uint8_t V_I_flag;

void page_switch()
{
	if (page == 0) // 波形模式
	{
		lv_obj_add_flag(guider_ui.wave_model_table_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_img_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_25, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_24, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_23, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_22, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_21, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_num_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_N_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_three_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_two_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_N__, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_three, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_two, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_red, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_blue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_green, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_yellow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_one_value, 120);
		lv_obj_set_height(guider_ui.wave_model_one_value, 30);
		lv_obj_set_width(guider_ui.wave_model_chart_2, 520);
		lv_obj_set_height(guider_ui.wave_model_chart_2, 340);
		lv_obj_set_pos(guider_ui.wave_model_chart_2, 47, 70);
		lv_obj_set_width(guider_ui.wave_model_three_value, 120);
		lv_obj_set_height(guider_ui.wave_model_three_value, 30);
		lv_obj_add_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_three, 300, 28);
		lv_obj_set_pos(guider_ui.wave_model_two, 137, 28);
		lv_obj_set_pos(guider_ui.wave_model_red, 330, 25);
		lv_obj_set_pos(guider_ui.wave_model_green, 167, 25);
		lv_obj_set_pos(guider_ui.wave_model_yellow, 1, 25);
		lv_obj_set_pos(guider_ui.wave_model_num_1, -30, 30);
		lv_obj_add_flag(guider_ui.wave_model_label_26, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_27, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.wave_model_btn_14_label, "Y-");
		lv_label_set_text(guider_ui.wave_model_btn_9_label, "Y+");
		lv_obj_clear_flag(guider_ui.wave_model_btn_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_11, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_13, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);
	}
	if (page == 1) // 截屏模式
	{			   //+227 +70

		lv_obj_clear_flag(guider_ui.wave_model_label_27, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_11, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_13, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_img_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_25, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_24, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_23, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_22, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_21, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_num_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_three_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_two_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N__, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_three, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_two, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_red, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_blue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_green, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_yellow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_26, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_chart_3, LV_OBJ_FLAG_HIDDEN);

		lv_label_set_text(guider_ui.wave_model_btn_14_label, "->");
		lv_label_set_text(guider_ui.wave_model_btn_9_label, "<-");
	}
	if (page == 2) // 谐波模式
	{
		lv_obj_clear_flag(guider_ui.wave_model_btn_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_11, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_13, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_27, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_chart_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_img_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_digital_clock_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_26, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_8, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_7, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.wave_model_num_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_25, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_24, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_23, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_22, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_21, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_three_value, 120);
		lv_obj_set_height(guider_ui.wave_model_three_value, 90);
		lv_obj_clear_flag(guider_ui.wave_model_three_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_two_value, 120);
		lv_obj_set_height(guider_ui.wave_model_two_value, 90);
		lv_obj_clear_flag(guider_ui.wave_model_two_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_one_value, 120);
		lv_obj_set_height(guider_ui.wave_model_one_value, 90);
		lv_obj_clear_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N__, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_three, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_two, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_red, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_blue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_green, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_yellow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_freq, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_power, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.wave_model_btn_14_label, "Y-");
		lv_label_set_text(guider_ui.wave_model_btn_9_label, "Y+");
	}
	if (page == 3) // 最值
	{

		lv_obj_add_flag(guider_ui.wave_model_chart_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_chart_2, 520);
		lv_obj_set_height(guider_ui.wave_model_chart_2, 280);
		lv_obj_set_pos(guider_ui.wave_model_chart_2, 47, 130);
		lv_obj_add_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_num_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_25, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_24, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_23, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_22, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_21, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_three_value, 120);
		lv_obj_set_height(guider_ui.wave_model_three_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_three_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_two_value, 120);
		lv_obj_set_height(guider_ui.wave_model_two_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_two_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_one_value, 120);
		lv_obj_set_height(guider_ui.wave_model_one_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N__, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_num_1, 169, 100);
		lv_obj_set_pos(guider_ui.wave_model_three, 430, 98);
		lv_obj_set_pos(guider_ui.wave_model_two, 299, 98);
		lv_obj_set_pos(guider_ui.wave_model_red, 461, 95);
		lv_obj_set_pos(guider_ui.wave_model_green, 330, 95);
		lv_obj_set_pos(guider_ui.wave_model_yellow, 200, 95);
		lv_obj_clear_flag(guider_ui.wave_model_three, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_two, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_red, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_blue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_green, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_yellow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_freq, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_power, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.wave_model_btn_8, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_26, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_digital_clock_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_img_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_table_2, LV_OBJ_FLAG_HIDDEN);
	}
	if (page == 4) // 功率和电能模式
	{
		lv_obj_add_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_table_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_chart_2, 520);
		lv_obj_set_height(guider_ui.wave_model_chart_2, 280);
		lv_obj_set_pos(guider_ui.wave_model_chart_2, 47, 130);
		lv_obj_add_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_num_1, 209, 70);
		lv_obj_clear_flag(guider_ui.wave_model_num_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_25, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_24, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_23, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_22, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_label_21, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_three_value, 120);
		lv_obj_set_height(guider_ui.wave_model_three_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_three_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_two_value, 120);
		lv_obj_set_height(guider_ui.wave_model_two_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_two_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_width(guider_ui.wave_model_one_value, 120);
		lv_obj_set_height(guider_ui.wave_model_one_value, 90);
		lv_obj_add_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_N__, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_three, 470, 68);
		lv_obj_clear_flag(guider_ui.wave_model_three, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_two, 339, 68);
		lv_obj_clear_flag(guider_ui.wave_model_two, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_red, 501, 65);
		lv_obj_clear_flag(guider_ui.wave_model_red, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_blue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_green, 370, 65);
		lv_obj_clear_flag(guider_ui.wave_model_green, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.wave_model_yellow, 240, 65);
		lv_obj_clear_flag(guider_ui.wave_model_yellow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_freq, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_power, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_5, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_btn_8, LV_OBJ_FLAG_HIDDEN);
		// lv_obj_clear_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_label_26, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.wave_model_digital_clock_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.wave_model_img_1, LV_OBJ_FLAG_HIDDEN);
	}
}

static void wave_model_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_GESTURE:
	{
		lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
		switch (dir)
		{
		case LV_DIR_LEFT:
		{
			lv_indev_wait_release(lv_indev_get_act());
			break;
		}
		}
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_2_event_handler(lv_event_t *e) // 电压电流波形切换
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		V_I_flag = !V_I_flag;
		if (V_I_flag == 1)
		{ // 显示电流
			ser1_I->hidden = 0;
			ser2_I->hidden = 0;
			ser3_I->hidden = 0;
			serN_I->hidden = 0;
			L2_I_flag = 0;
			L1_I_flag = 0;
			L3_I_flag = 0;
			LN_I_flag = 0;

			ser1->hidden = 1;
			ser2->hidden = 1;
			ser3->hidden = 1;
			serN->hidden = 1;
			L2_flag = 1;
			L1_flag = 1;
			L3_flag = 1;
			LN_flag = 1;

			lv_label_set_text(guider_ui.wave_model_btn_2_label, "I");
		}
		else
		{ // 显示电压

			lv_label_set_text(guider_ui.wave_model_btn_2_label, "V");
			ser1->hidden = 0;
			ser2->hidden = 0;
			ser3->hidden = 0;
			serN->hidden = 0;
			L2_flag = 0;
			L1_flag = 0;
			L3_flag = 0;
			LN_flag = 0;

			ser1_I->hidden = 1;
			ser2_I->hidden = 1;
			ser3_I->hidden = 1;
			serN_I->hidden = 1;
			L2_I_flag = 1;
			L1_I_flag = 1;
			L3_I_flag = 1;
			LN_I_flag = 1;
		}
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		page++;
		if (page > 4)
			page = 0;
		page_switch();

		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		page--;
		if (page < 0)
			page = 4;

		page_switch();
		break;
	}
	default:
		break;
	}
}

static void wave_model_btn_1_event_handler(lv_event_t *e) // L1
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (V_I_flag == 1)
		{
			L1_I_flag = !L1_I_flag;
			ser1_I->hidden = L1_I_flag;
		}

		else if (V_I_flag == 0)
		{
			L1_flag = !L1_flag;
			ser1->hidden = L1_flag;
		}

		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_3_event_handler(lv_event_t *e) // L2
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (V_I_flag == 1)
		{
			L2_I_flag = !L2_I_flag;
			ser2_I->hidden = L2_I_flag;
		}

		else if (V_I_flag == 0)
		{
			L2_flag = !L2_flag;
			ser2->hidden = L2_flag;
		}

		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_4_event_handler(lv_event_t *e) // L3
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (V_I_flag == 1)
		{
			L3_I_flag = !L3_I_flag;
			ser3_I->hidden = L3_I_flag;
		}

		else if (V_I_flag == 0)
		{
			L3_flag = !L3_flag;
			ser3->hidden = L3_flag;
		}
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_5_event_handler(lv_event_t *e) // LN
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (V_I_flag == 1)
		{
			LN_I_flag = !LN_I_flag;
			serN_I->hidden = LN_I_flag;
		}

		else if (V_I_flag == 0)
		{
			LN_flag = !LN_flag;
			serN->hidden = LN_flag;
		}
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_6_event_handler(lv_event_t *e) // Ca截屏
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		char filename[60] = {0};
		uint8_t temp = 0;

		vTaskSuspendAll();
		taskENTER_CRITICAL();
		if (page == 0)
		{
			sprintf(filename, "0:test/p%d%d%d.bin", wave_model_digital_clock_1_hour_value, wave_model_digital_clock_1_min_value, wave_model_digital_clock_1_sec_value);
			if (take_snapshot_with_buffer(guider_ui.wave_model_chart_2, filename))
			{
				sd_count++;
				//msg_notice(guider_ui.wave_model_msg, 2000, "截屏成功");
				temp = 1;
				LV_LOG_USER("sd_count = %d\r\n", sd_count);
				refersh_lvgl_image(guider_ui.wave_model_img_1);
			}
			else
			{
				temp = 0;
			}
		}

		taskEXIT_CRITICAL();
		xTaskResumeAll();
		if (temp)
		{
			msg_notice(guider_ui.wave_model_msg, 2000, "Screenshot successful");
		}
		else
		{
			msg_notice(guider_ui.wave_model_msg, 2000, "Screenshot failed");
		}

		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_9_event_handler(lv_event_t *e) // X+
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// taskENTER_CRITICAL();
		if (page == 0)
		{
			step--;
			if (step == 0)
			{
				step = 1;
			}
		}
		else if (page == 1)
		{
			vTaskSuspendAll();
			taskENTER_CRITICAL();
			file_now--;
			if (file_now < 0)
			{
				LV_LOG_USER("file_now < 0, set to sd_count\r\n");
				file_now = sd_count;
			}
			LV_LOG_USER("set filenow to %d", file_now);
			uint8_t temp = OpenFileByIndex("0:test", file_now);
			if (temp)
			{
				refersh_lvgl_image(guider_ui.wave_model_img_1);
			}
		}

		taskEXIT_CRITICAL();
		xTaskResumeAll();

		// taskENTER_CRITICAL();
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_10_event_handler(lv_event_t *e) // X-
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// taskENTER_CRITICAL();
		step++;
		// taskENTER_CRITICAL();
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		level += 5;
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		level -= 5;
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_13_event_handler(lv_event_t *e) // Y+
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// taskENTER_CRITICAL();
		rat += 10;
		// taskENTER_CRITICAL();
		break;
	}
	default:
		break;
	}
}
static void wave_model_btn_14_event_handler(lv_event_t *e) // Y-
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// taskENTER_CRITICAL();
		if (page == 0) // 波形显示模式
		{
			rat -= 10;
		}
		else if (page == 1) // 图片模式
		{
			vTaskSuspendAll();
			taskENTER_CRITICAL();
			file_now++;
			if (file_now > sd_count)
			{
				LV_LOG_USER("file_now >sd_count, set to 0\r\n");
				file_now = 0;
			}
			LV_LOG_USER("set filenow to %d", file_now);
			uint8_t temp = OpenFileByIndex("0:test", file_now);
			if (temp)
			{
				refersh_lvgl_image(guider_ui.wave_model_img_1);
			}
			taskEXIT_CRITICAL();
			xTaskResumeAll();
		}

		// taskENTER_CRITICAL();
		break;
	}
	default:
		break;
	}
}

void events_init_wave_model(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->wave_model, wave_model_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_1, wave_model_btn_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_2, wave_model_btn_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_3, wave_model_btn_3_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_4, wave_model_btn_4_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_5, wave_model_btn_5_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_6, wave_model_btn_6_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_7, wave_model_btn_7_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_8, wave_model_btn_8_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_9, wave_model_btn_9_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_10, wave_model_btn_10_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_11, wave_model_btn_11_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_12, wave_model_btn_12_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_13, wave_model_btn_13_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->wave_model_btn_14, wave_model_btn_14_event_handler, LV_EVENT_ALL, NULL);
}

void switch_btn(lv_timer_t *timer)
{
	lv_obj_add_flag(guider_ui.wave_model_msg, LV_OBJ_FLAG_HIDDEN);
	lv_timer_del(timer); // 删除定时器，避免占用资源
}

// msg消息提示
void msg_notice(lv_obj_t *msg, uint32_t duration_ms, const char *notice)
{
	lv_label_set_text_fmt(guider_ui.wave_model_msg, "%s", notice);
	lv_obj_clear_flag(guider_ui.wave_model_msg, LV_OBJ_FLAG_HIDDEN);
	lv_timer_t *timer = lv_timer_create(switch_btn, duration_ms, msg); // 创建定时器
	if (!timer)
	{
		LV_LOG_ERROR("定时器创建失败！");
	}
}

void events_init(lv_ui *ui)
{
	sd_count = GetFileCount("0:test");
	file_now = sd_count;
	LV_LOG_USER("sd_count = %d\r\n", sd_count);
}
