/*
 * Copyright 2025 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "rtc.h"
// extern uint16_t MyRTC_Time[5];
int wave_model_digital_clock_1_min_value;
int wave_model_digital_clock_1_hour_value;
int wave_model_digital_clock_1_sec_value;
char wave_model_digital_clock_1_meridiem[] = "";
void setup_scr_wave_model(lv_ui *ui)
{
	// MyRTC_ReadTime();
	// wave_model_digital_clock_1_min_value = MyRTC_Time[4];
	// wave_model_digital_clock_1_hour_value = MyRTC_Time[3];
	// wave_model_digital_clock_1_sec_value = MyRTC_Time[5];
	// Write codes wave_model
	ui->wave_model = lv_obj_create(NULL);
	lv_obj_set_size(ui->wave_model, 640, 480);

	// Write style for wave_model, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model, lv_color_hex(0xc3dfd6), LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_7
	ui->wave_model_btn_7 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_7_label = lv_label_create(ui->wave_model_btn_7);
	lv_label_set_text(ui->wave_model_btn_7_label, ">");
	lv_label_set_long_mode(ui->wave_model_btn_7_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_7_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_7, 600, 445);
	lv_obj_set_size(ui->wave_model_btn_7, 20, 27);

	// Write style for wave_model_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_7, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_7, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_7, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_6
	ui->wave_model_btn_6 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_6_label = lv_label_create(ui->wave_model_btn_6);
	lv_label_set_text(ui->wave_model_btn_6_label, "Ca");
	lv_label_set_long_mode(ui->wave_model_btn_6_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_6_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_6, 586, 130);
	lv_obj_set_size(ui->wave_model_btn_6, 43, 30);

	// Write style for wave_model_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_6, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_6, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_6, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_2
	ui->wave_model_btn_2 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_2_label = lv_label_create(ui->wave_model_btn_2);
	lv_label_set_text(ui->wave_model_btn_2_label, "V");
	lv_label_set_long_mode(ui->wave_model_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_2, 586, 170);
	lv_obj_set_size(ui->wave_model_btn_2, 40, 30);

	// Write style for wave_model_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_2, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_2, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_1
	ui->wave_model_btn_1 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_1_label = lv_label_create(ui->wave_model_btn_1);
	lv_label_set_text(ui->wave_model_btn_1_label, "L1");
	lv_label_set_long_mode(ui->wave_model_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_1, 586, 210);
	lv_obj_set_size(ui->wave_model_btn_1, 40, 30);

	// Write style for wave_model_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_1, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_1, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_3
	ui->wave_model_btn_3 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_3_label = lv_label_create(ui->wave_model_btn_3);
	lv_label_set_text(ui->wave_model_btn_3_label, "L2");
	lv_label_set_long_mode(ui->wave_model_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_3, 586, 250);
	lv_obj_set_size(ui->wave_model_btn_3, 40, 30);

	// Write style for wave_model_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_3, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_3, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_4
	ui->wave_model_btn_4 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_4_label = lv_label_create(ui->wave_model_btn_4);
	lv_label_set_text(ui->wave_model_btn_4_label, "L3");
	lv_label_set_long_mode(ui->wave_model_btn_4_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_4, 586, 290);
	lv_obj_set_size(ui->wave_model_btn_4, 40, 30);

	// Write style for wave_model_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_4, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_4, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_4, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_5
	ui->wave_model_btn_5 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_5_label = lv_label_create(ui->wave_model_btn_5);
	lv_label_set_text(ui->wave_model_btn_5_label, "N");
	lv_label_set_long_mode(ui->wave_model_btn_5_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_5_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_5, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_5, 586, 330);
	lv_obj_set_size(ui->wave_model_btn_5, 40, 30);

	// Write style for wave_model_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_5, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_5, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_5, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_power
	ui->wave_model_power = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_power, "power");
	lv_label_set_long_mode(ui->wave_model_power, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_power, 530, 4);
	lv_obj_set_size(ui->wave_model_power, 90, 20);

	// Write style for wave_model_power, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_power, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_power, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_power, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_power, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_freq
	ui->wave_model_freq = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_freq, "Label");
	lv_label_set_long_mode(ui->wave_model_freq, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_freq, 250, 4);
	lv_obj_set_size(ui->wave_model_freq, 98, 20);

	// Write style for wave_model_freq, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_freq, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_freq, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_freq, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_freq, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_freq, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_yellow
	ui->wave_model_yellow = lv_arc_create(ui->wave_model);
	lv_arc_set_mode(ui->wave_model_yellow, LV_ARC_MODE_REVERSE);
	lv_arc_set_range(ui->wave_model_yellow, 0, 1);
	lv_arc_set_bg_angles(ui->wave_model_yellow, 0, 0);
	lv_arc_set_angles(ui->wave_model_yellow, 0, 360);
	lv_arc_set_rotation(ui->wave_model_yellow, 0);
	lv_obj_set_style_arc_rounded(ui->wave_model_yellow, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->wave_model_yellow, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_yellow, 1, 25);
	lv_obj_set_size(ui->wave_model_yellow, 38, 38);

	// Write style for wave_model_yellow, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->wave_model_yellow, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_yellow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_yellow, lv_color_hex(0xffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_yellow, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_yellow, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_yellow, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->wave_model_yellow, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_yellow, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_yellow, lv_color_hex(0xffff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);

	// Write style for wave_model_yellow, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_yellow, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->wave_model_yellow, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	// Write codes wave_model_green
	ui->wave_model_green = lv_arc_create(ui->wave_model);
	lv_arc_set_mode(ui->wave_model_green, LV_ARC_MODE_REVERSE);
	lv_arc_set_range(ui->wave_model_green, 0, 1);
	lv_arc_set_bg_angles(ui->wave_model_green, 0, 0);
	lv_arc_set_angles(ui->wave_model_green, 0, 360);
	lv_arc_set_rotation(ui->wave_model_green, 0);
	lv_obj_set_style_arc_rounded(ui->wave_model_green, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->wave_model_green, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_green, 167, 25);
	lv_obj_set_size(ui->wave_model_green, 38, 38);

	// Write style for wave_model_green, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->wave_model_green, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_green, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_green, lv_color_hex(0xffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_green, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_green, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_green, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->wave_model_green, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_green, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_green, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);

	// Write style for wave_model_green, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_green, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->wave_model_green, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	// Write codes wave_model_blue
	ui->wave_model_blue = lv_arc_create(ui->wave_model);
	lv_arc_set_mode(ui->wave_model_blue, LV_ARC_MODE_REVERSE);
	lv_arc_set_range(ui->wave_model_blue, 0, 1);
	lv_arc_set_bg_angles(ui->wave_model_blue, 0, 0);
	lv_arc_set_angles(ui->wave_model_blue, 0, 360);
	lv_arc_set_rotation(ui->wave_model_blue, 0);
	lv_obj_set_style_arc_rounded(ui->wave_model_blue, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->wave_model_blue, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_blue, 490, 25);
	lv_obj_set_size(ui->wave_model_blue, 38, 38);

	// Write style for wave_model_blue, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->wave_model_blue, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_blue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_blue, lv_color_hex(0xffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_blue, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_blue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_blue, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->wave_model_blue, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_blue, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_blue, lv_color_hex(0x0000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);

	// Write style for wave_model_blue, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_blue, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->wave_model_blue, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	// Write codes wave_model_red
	ui->wave_model_red = lv_arc_create(ui->wave_model);
	lv_arc_set_mode(ui->wave_model_red, LV_ARC_MODE_REVERSE);
	lv_arc_set_range(ui->wave_model_red, 0, 1);
	lv_arc_set_bg_angles(ui->wave_model_red, 0, 0);
	lv_arc_set_angles(ui->wave_model_red, 0, 360);
	lv_arc_set_rotation(ui->wave_model_red, 0);
	lv_obj_set_style_arc_rounded(ui->wave_model_red, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->wave_model_red, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_red, 330, 25);
	lv_obj_set_size(ui->wave_model_red, 38, 38);

	// Write style for wave_model_red, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->wave_model_red, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_red, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_red, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_red, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_red, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_red, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->wave_model_red, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->wave_model_red, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->wave_model_red, lv_color_hex(0xff0200), LV_PART_INDICATOR | LV_STATE_DEFAULT);

	// Write style for wave_model_red, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_red, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->wave_model_red, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	// Write codes wave_model_two
	ui->wave_model_two = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_two, "2");
	lv_label_set_long_mode(ui->wave_model_two, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_two, 137, 28);
	lv_obj_set_size(ui->wave_model_two, 100, 32);

	// Write style for wave_model_two, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_two, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_two, &lv_font_arial_32, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_two, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_two, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_two, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_three
	ui->wave_model_three = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_three, "3");
	lv_label_set_long_mode(ui->wave_model_three, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_three, 300, 28);
	lv_obj_set_size(ui->wave_model_three, 100, 32);

	// Write style for wave_model_three, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_three, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_three, &lv_font_arial_32, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_three, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_three, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_three, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_N__
	ui->wave_model_N__ = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_N__, "N");
	lv_label_set_long_mode(ui->wave_model_N__, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_N__, 460, 29);
	lv_obj_set_size(ui->wave_model_N__, 100, 32);

	// Write style for wave_model_N__, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_N__, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_N__, &lv_font_arial_32, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_N__, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_N__, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_N__, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_one_value
	ui->wave_model_one_value = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_one_value, "000.0V");
	lv_label_set_long_mode(ui->wave_model_one_value, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_one_value, 47, 31);
	lv_obj_set_size(ui->wave_model_one_value, 120, 30);

	// Write style for wave_model_one_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_one_value, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_one_value, &lv_font_arial_30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_one_value, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_one_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_one_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_two_value
	ui->wave_model_two_value = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_two_value, "000.0V");
	lv_label_set_long_mode(ui->wave_model_two_value, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_two_value, 210, 27);
	lv_obj_set_size(ui->wave_model_two_value, 120, 30);

	// Write style for wave_model_two_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_two_value, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_two_value, &lv_font_arial_30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_two_value, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_two_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_two_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_three_value
	ui->wave_model_three_value = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_three_value, "000.0V");
	lv_label_set_long_mode(ui->wave_model_three_value, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_three_value, 375, 27);
	lv_obj_set_size(ui->wave_model_three_value, 120, 90);

	// Write style for wave_model_three_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_three_value, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_three_value, &lv_font_arial_30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_three_value, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_three_value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_three_value, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_label_21
	ui->wave_model_label_21 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_21, "Label");
	lv_label_set_long_mode(ui->wave_model_label_21, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_21, 77, 413);
	lv_obj_set_size(ui->wave_model_label_21, 108, 27);

	// Write style for wave_model_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_21, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_21, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_21, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_21, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_label_22
	ui->wave_model_label_22 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_22, "Label");
	lv_label_set_long_mode(ui->wave_model_label_22, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_22, 184, 413);
	lv_obj_set_size(ui->wave_model_label_22, 100, 32);

	// Write style for wave_model_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_22, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_22, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_22, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_22, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_label_23
	ui->wave_model_label_23 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_23, "Label");
	lv_label_set_long_mode(ui->wave_model_label_23, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_23, 285, 413);
	lv_obj_set_size(ui->wave_model_label_23, 100, 32);

	// Write style for wave_model_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_23, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_23, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_23, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_23, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_23, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_label_24
	ui->wave_model_label_24 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_24, "Label");
	lv_label_set_long_mode(ui->wave_model_label_24, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_24, 385, 413);
	lv_obj_set_size(ui->wave_model_label_24, 100, 32);

	// Write style for wave_model_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_24, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_24, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_24, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_24, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_label_25
	ui->wave_model_label_25 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_25, "Label");
	lv_label_set_long_mode(ui->wave_model_label_25, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_25, 480, 413);
	lv_obj_set_size(ui->wave_model_label_25, 100, 32);

	// Write style for wave_model_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_25, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_25, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_25, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_25, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_25, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_N_val
	ui->wave_model_N_val = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_N_val, "000.0V");
	lv_label_set_long_mode(ui->wave_model_N_val, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_N_val, 530, 29);
	lv_obj_set_size(ui->wave_model_N_val, 120, 30);

	// Write style for wave_model_N_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_N_val, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_N_val, &lv_font_arial_30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_N_val, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_N_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_N_val, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_num_1
	ui->wave_model_num_1 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_num_1, "1");
	lv_label_set_long_mode(ui->wave_model_num_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_num_1, -30, 30);
	lv_obj_set_size(ui->wave_model_num_1, 100, 32);

	// Write style for wave_model_num_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_num_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_num_1, &lv_font_arial_32, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_num_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_num_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_num_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_chart_2
	ui->wave_model_chart_2 = lv_chart_create(ui->wave_model);
	lv_chart_set_type(ui->wave_model_chart_2, LV_CHART_TYPE_LINE);
	lv_chart_set_div_line_count(ui->wave_model_chart_2, 0, 0);
	lv_chart_set_point_count(ui->wave_model_chart_2, 5);
	lv_chart_set_range(ui->wave_model_chart_2, LV_CHART_AXIS_PRIMARY_Y, 0, 340);
	lv_chart_set_range(ui->wave_model_chart_2, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
	lv_chart_set_zoom_x(ui->wave_model_chart_2, 256);
	lv_chart_set_zoom_y(ui->wave_model_chart_2, 256);
	lv_obj_set_pos(ui->wave_model_chart_2, 47, 70);
	lv_obj_set_size(ui->wave_model_chart_2, 520, 340);
	lv_obj_set_scrollbar_mode(ui->wave_model_chart_2, LV_SCROLLBAR_MODE_OFF);
	// lv_obj_add_flag(ui->wave_model_chart_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->wave_model_chart_2, LV_OBJ_FLAG_CLICK_FOCUSABLE);

	// Write style for wave_model_chart_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_chart_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_chart_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->wave_model_chart_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->wave_model_chart_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->wave_model_chart_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_chart_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->wave_model_chart_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->wave_model_chart_2, lv_color_hex(0xaba0a0), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->wave_model_chart_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_chart_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_chart_2, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->wave_model_chart_2, lv_color_hex(0x151212), LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_chart_2, &lv_font_montserratMedium_12, LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->wave_model_chart_2, 2, LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->wave_model_chart_2, lv_color_hex(0xe8e8e8), LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->wave_model_chart_2, 255, LV_PART_TICKS | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_8
	ui->wave_model_btn_8 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_8_label = lv_label_create(ui->wave_model_btn_8);
	lv_label_set_text(ui->wave_model_btn_8_label, "<");
	lv_label_set_long_mode(ui->wave_model_btn_8_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_8_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_8, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_8, 10, 445);
	lv_obj_set_size(ui->wave_model_btn_8, 20, 27);

	// Write style for wave_model_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_8, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_8, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_8, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_table_1
	ui->wave_model_table_1 = lv_table_create(ui->wave_model);
	lv_table_set_col_cnt(ui->wave_model_table_1, 4);
	lv_table_set_row_cnt(ui->wave_model_table_1, 5);
	lv_obj_add_flag(ui->wave_model_table_1, LV_OBJ_FLAG_HIDDEN);
	lv_table_set_cell_value(ui->wave_model_table_1, 0, 0, "RMS");
	lv_table_set_cell_value(ui->wave_model_table_1, 1, 0, "MAX");
	lv_table_set_cell_value(ui->wave_model_table_1, 2, 0, "MIN");
	lv_table_set_cell_value(ui->wave_model_table_1, 3, 0, "THD");
	lv_table_set_cell_value(ui->wave_model_table_1, 4, 0, "DC");
	lv_table_set_cell_value(ui->wave_model_table_1, 0, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 1, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 2, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 3, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 4, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 0, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 1, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 2, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 3, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 4, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 0, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 1, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 2, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 3, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_1, 4, 3, "0");
	lv_obj_set_pos(ui->wave_model_table_1, 66, 160);
	lv_obj_set_scrollbar_mode(ui->wave_model_table_1, LV_SCROLLBAR_MODE_OFF);

	// Write style for wave_model_table_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_table_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_table_1, lv_color_hex(0xc3dfd6), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_table_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->wave_model_table_1, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_table_1, &lv_font_arial_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_table_1, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_table_1, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_table_1, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->wave_model_table_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->wave_model_table_1, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->wave_model_table_1, LV_BORDER_SIDE_FULL, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);

	// Write codes wave_model_label_26
	ui->wave_model_label_26 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_26, "START:");
	lv_label_set_long_mode(ui->wave_model_label_26, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_26, 27, 30);
	lv_obj_set_size(ui->wave_model_label_26, 586, 26);

	// Write style for wave_model_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_26, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_26, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_26, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_26, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_26, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_label_26, lv_color_hex(0xf6e828), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_26, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_26, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_26, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->wave_model_label_26, LV_OBJ_FLAG_HIDDEN);

	// Write codes wave_model_digital_clock_1
	static bool wave_model_digital_clock_1_timer_enabled = false;
	ui->wave_model_digital_clock_1 = lv_dclock_create(ui->wave_model, "00:00:00 AM");
	if (!wave_model_digital_clock_1_timer_enabled)
	{
		lv_timer_create(wave_model_digital_clock_1_timer, 1000, NULL);
		wave_model_digital_clock_1_timer_enabled = true;
	}
	lv_obj_set_pos(ui->wave_model_digital_clock_1, 0, 4);
	lv_obj_set_size(ui->wave_model_digital_clock_1, 90, 16);

	// Write style for wave_model_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_digital_clock_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_digital_clock_1, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_digital_clock_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_digital_clock_1, lv_color_hex(0xc3dfd6), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_img_1
	ui->wave_model_img_1 = lv_img_create(ui->wave_model);
	lv_obj_add_flag(ui->wave_model_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->wave_model_img_1, &_f7b64978f5bff1ff9d8a4bf8f3d4d9d6_alpha_520x340);
	lv_img_set_pivot(ui->wave_model_img_1, 50, 50);
	lv_img_set_angle(ui->wave_model_img_1, 0);
	lv_obj_set_pos(ui->wave_model_img_1, 20, 20);
	lv_obj_set_size(ui->wave_model_img_1, 600, 420);
	lv_obj_add_flag(ui->wave_model_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui->wave_model_img_1, LV_OBJ_FLAG_CLICK_FOCUSABLE);
	lv_obj_add_flag(ui->wave_model_img_1, LV_OBJ_FLAG_HIDDEN);

	// Write style for wave_model_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->wave_model_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_9
	ui->wave_model_btn_9 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_9_label = lv_label_create(ui->wave_model_btn_9);
	lv_label_set_text(ui->wave_model_btn_9_label, "X+");
	lv_label_set_long_mode(ui->wave_model_btn_9_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_9_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_9, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_9, 98, 445);
	lv_obj_set_size(ui->wave_model_btn_9, 43, 30);

	// Write style for wave_model_btn_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_9, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_9, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_9, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_10
	ui->wave_model_btn_10 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_10_label = lv_label_create(ui->wave_model_btn_10);
	lv_label_set_text(ui->wave_model_btn_10_label, "X-");
	lv_label_set_long_mode(ui->wave_model_btn_10_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_10_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_10, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_10, 178, 445);
	lv_obj_set_size(ui->wave_model_btn_10, 43, 30);

	// Write style for wave_model_btn_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_10, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_10, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_10, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_11
	ui->wave_model_btn_11 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_11_label = lv_label_create(ui->wave_model_btn_11);
	lv_label_set_text(ui->wave_model_btn_11_label, "L+");
	lv_label_set_long_mode(ui->wave_model_btn_11_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_11_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_11, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_11, 258, 445);
	lv_obj_set_size(ui->wave_model_btn_11, 43, 30);

	// Write style for wave_model_btn_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_11, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_11, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_11, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_11, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_12
	ui->wave_model_btn_12 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_12_label = lv_label_create(ui->wave_model_btn_12);
	lv_label_set_text(ui->wave_model_btn_12_label, "L-");
	lv_label_set_long_mode(ui->wave_model_btn_12_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_12_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_12, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_12, 338, 445);
	lv_obj_set_size(ui->wave_model_btn_12, 43, 30);

	// Write style for wave_model_btn_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_12, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_12, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_12, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_12, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_13
	ui->wave_model_btn_13 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_13_label = lv_label_create(ui->wave_model_btn_13);
	lv_label_set_text(ui->wave_model_btn_13_label, "Y+");
	lv_label_set_long_mode(ui->wave_model_btn_13_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_13_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_13, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_13, 418, 445);
	lv_obj_set_size(ui->wave_model_btn_13, 43, 30);

	// Write style for wave_model_btn_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_13, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_13, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_13, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_13, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_btn_14
	ui->wave_model_btn_14 = lv_btn_create(ui->wave_model);
	ui->wave_model_btn_14_label = lv_label_create(ui->wave_model_btn_14);
	lv_label_set_text(ui->wave_model_btn_14_label, "Y-");
	lv_label_set_long_mode(ui->wave_model_btn_14_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->wave_model_btn_14_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->wave_model_btn_14, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->wave_model_btn_14, 498, 445);
	lv_obj_set_size(ui->wave_model_btn_14, 43, 30);

	// Write style for wave_model_btn_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_btn_14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_btn_14, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_btn_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_btn_14, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_btn_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_btn_14, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_btn_14, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_btn_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_chart_3
	ui->wave_model_chart_3 = lv_chart_create(ui->wave_model);
	lv_chart_set_type(ui->wave_model_chart_3, LV_CHART_TYPE_BAR);
	lv_chart_set_div_line_count(ui->wave_model_chart_3, 0, 0);
	lv_chart_set_point_count(ui->wave_model_chart_3, 50);
	lv_chart_set_range(ui->wave_model_chart_3, LV_CHART_AXIS_PRIMARY_Y, 0, 340);
	lv_chart_set_range(ui->wave_model_chart_3, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
	lv_chart_set_zoom_x(ui->wave_model_chart_3, 256);
	lv_chart_set_zoom_y(ui->wave_model_chart_3, 256);
	lv_obj_set_width(guider_ui.wave_model_chart_3, 520);
	lv_obj_set_height(guider_ui.wave_model_chart_3, 280);
	lv_obj_set_pos(guider_ui.wave_model_chart_3, 47, 130);
	lv_obj_set_scrollbar_mode(ui->wave_model_chart_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->wave_model_chart_3, LV_OBJ_FLAG_HIDDEN);

	// Write style for wave_model_chart_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->wave_model_chart_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_chart_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->wave_model_chart_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->wave_model_chart_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->wave_model_chart_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_chart_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->wave_model_chart_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->wave_model_chart_3, lv_color_hex(0xaba0a0), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->wave_model_chart_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_chart_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_chart_3, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->wave_model_chart_3, lv_color_hex(0x151212), LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_chart_3, &lv_font_montserratMedium_12, LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->wave_model_chart_3, 2, LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->wave_model_chart_3, lv_color_hex(0xe8e8e8), LV_PART_TICKS | LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->wave_model_chart_3, 255, LV_PART_TICKS | LV_STATE_DEFAULT);

	// Write codes wave_model_table_2
	ui->wave_model_table_2 = lv_table_create(ui->wave_model);
	lv_table_set_col_cnt(ui->wave_model_table_2, 4);
	lv_table_set_row_cnt(ui->wave_model_table_2, 5);
	lv_table_set_cell_value(ui->wave_model_table_2, 0, 0, "PF");
	lv_table_set_cell_value(ui->wave_model_table_2, 1, 0, "DPF");
	lv_table_set_cell_value(ui->wave_model_table_2, 2, 0, "PHASE");
	lv_table_set_cell_value(ui->wave_model_table_2, 3, 0, "W");
	lv_table_set_cell_value(ui->wave_model_table_2, 4, 0, "Wh");
	lv_table_set_cell_value(ui->wave_model_table_2, 0, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 1, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 2, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 3, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 4, 1, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 0, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 1, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 2, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 3, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 4, 2, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 0, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 1, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 2, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 3, 3, "0");
	lv_table_set_cell_value(ui->wave_model_table_2, 4, 3, "0");
	lv_obj_set_pos(ui->wave_model_table_2, 70, 142);
	lv_obj_set_scrollbar_mode(ui->wave_model_table_2, LV_SCROLLBAR_MODE_OFF);

	// Write style for wave_model_table_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_table_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_table_2, lv_color_hex(0xc3dfd6), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write style for wave_model_table_2, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->wave_model_table_2, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_table_2, &lv_font_arial_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_table_2, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_table_2, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->wave_model_table_2, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->wave_model_table_2, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->wave_model_table_2, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->wave_model_table_2, LV_BORDER_SIDE_FULL, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->wave_model_table_2, LV_OBJ_FLAG_HIDDEN);

	// Write codes wave_model_label_27
	ui->wave_model_label_27 = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_label_27, "IMAGE:");
	lv_label_set_long_mode(ui->wave_model_label_27, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_label_27, 100, 450);
	lv_obj_set_size(ui->wave_model_label_27, 440, 16);
	lv_obj_add_flag(ui->wave_model_label_27, LV_OBJ_FLAG_HIDDEN);

	// Write style for wave_model_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_label_27, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_label_27, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_label_27, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_label_27, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_label_27, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Write codes wave_model_msg
	ui->wave_model_msg = lv_label_create(ui->wave_model);
	lv_label_set_text(ui->wave_model_msg, "Label");
	lv_label_set_long_mode(ui->wave_model_msg, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->wave_model_msg, 127, 363);
	lv_obj_set_size(ui->wave_model_msg, 388, 30);
	lv_obj_add_flag(ui->wave_model_msg, LV_OBJ_FLAG_HIDDEN);

	// Write style for wave_model_msg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->wave_model_msg, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->wave_model_msg, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->wave_model_msg, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->wave_model_msg, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->wave_model_msg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->wave_model_msg, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->wave_model_msg, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->wave_model_msg, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->wave_model_msg, lv_color_hex(0xff005e), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->wave_model_msg, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->wave_model_msg, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->wave_model_msg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Update current screen layout.
	lv_obj_update_layout(ui->wave_model);

	// Init events for screen.
	events_init_wave_model(ui);
}
