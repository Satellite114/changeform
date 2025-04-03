#include "task_page1.h"
// 设置chart_2的样式
extern lv_ui guider_ui;
lv_chart_cursor_t *cursor;
extern FFT fft_1V;
extern FFT fft_2V;
extern FFT fft_3V;
extern FFT fft_NV; // 四通道电压采样

extern FFT fft_1I;
extern FFT fft_2I;
extern FFT fft_3I;
extern FFT fft_NI; // 四通道电流采样
extern phase P1;
extern phase P2;
extern phase P3;
extern phase PN; // 四通道相位采样
extern Voltage_three Voltage; // 三相电压采样
extern uint8_t V_I_flag;

void page_init()
{
    lv_obj_set_style_width(guider_ui.wave_model_chart_2, 0, LV_PART_INDICATOR); // 设置点的大小
    lv_obj_set_style_height(guider_ui.wave_model_chart_2, 0, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_NONE), LV_PART_SCROLLBAR); // 设置滚动条颜色？？？
    lv_chart_set_div_line_count(guider_ui.wave_model_chart_2, 5, 10);                                             // 设置栅格数量
    lv_obj_set_style_line_color(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_NONE), LV_PART_MAIN);    // 修改栅格颜色
    lv_chart_set_axis_tick(guider_ui.wave_model_chart_2, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 5, 5, true, 40);          // 设置标签个数和大小
    lv_obj_set_style_line_color(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS);   // 标签的颜色
    lv_obj_set_style_text_color(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS);
    lv_chart_set_range(guider_ui.wave_model_chart_2, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
    lv_chart_set_update_mode(guider_ui.wave_model_chart_2, LV_CHART_UPDATE_MODE_CIRCULAR); // 设置循环刷新
    lv_chart_set_point_count(guider_ui.wave_model_chart_2, 256);
    // cursor = lv_chart_add_cursor(guider_ui.wave_model_chart_2, lv_palette_main(LV_PALETTE_GREEN), LV_DIR_RIGHT); // 添加光标
    // lv_point_t point = {100, 120};
    // lv_chart_set_cursor_pos(guider_ui.wave_model_chart_2, cursor, &point); // 光标位置
    // lv_chart_set_zoom_y(guider_ui.wave_model_chart_2, 512); // 缩放

    lv_chart_set_type(guider_ui.wave_model_chart_3, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(guider_ui.wave_model_chart_3, 25); // 图表上点的个数
    lv_obj_set_style_pad_column(guider_ui.wave_model_chart_3, 0, LV_PART_MAIN);
    lv_chart_set_range(guider_ui.wave_model_chart_3, LV_CHART_AXIS_PRIMARY_Y, 0, 500);
    lv_chart_set_axis_tick(guider_ui.wave_model_chart_3, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 5, 5, true, 40);        // 设置标签个数和大小
    lv_obj_set_style_line_color(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS); // 标签的颜色
    lv_obj_set_style_text_color(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS);
    lv_chart_set_axis_tick(guider_ui.wave_model_chart_3, LV_CHART_AXIS_PRIMARY_X, 5, 0, 25, 5, true, 10);       // 设置标签个数和大小
    lv_obj_set_style_line_color(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS); // 标签的颜色
    lv_obj_set_style_text_color(guider_ui.wave_model_chart_3, lv_palette_main(LV_PALETTE_NONE), LV_PART_TICKS);
}
void task_page()
{

    lv_label_set_text_fmt(guider_ui.wave_model_freq, "%.2fHZ", fft_1V.freq);

    if (!lv_obj_has_flag(guider_ui.wave_model_chart_2, LV_OBJ_FLAG_HIDDEN))
    {
      lv_chart_refresh(guider_ui.wave_model_chart_2);
    }


    
    if (!lv_obj_has_flag(guider_ui.wave_model_chart_3, LV_OBJ_FLAG_HIDDEN))
    {
      lv_chart_refresh(guider_ui.wave_model_chart_3);
    }
    if (!lv_obj_has_flag(guider_ui.wave_model_table_1, LV_OBJ_FLAG_HIDDEN))
    {
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 0, 1, "%.2f", fft_1V.RMS);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 0, 2, "%.2f", fft_2V.RMS);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 0, 3, "%.2f", fft_3V.RMS);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 1, 1, "%.2f", fft_1V.max_v);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 1, 2, "%.2f", fft_2V.max_v);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 1, 3, "%.2f", fft_3V.max_v);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 2, 1, "%.2f", fft_1V.min_v);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 2, 2, "%.2f", fft_2V.min_v);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 2, 3, "%.2f", fft_3V.min_v);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 3, 1, "%.2f", fft_1V.THD_);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 3, 2, "%.2f", fft_2V.THD_);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 3, 3, "%.2f", fft_3V.THD_);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 4, 1, "%.2f", fft_1V.DC);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 4, 2, "%.2f", fft_2V.DC);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_1, 4, 3, "%.2f", fft_3V.DC);
    }


    
    if (!lv_obj_has_flag(guider_ui.wave_model_table_2, LV_OBJ_FLAG_HIDDEN))
    {

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 0, 1, "%.2f", P1.PF);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 0, 2, "%.2f", P2.PF);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 0, 3, "%.2f", P3.PF);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 1, 1, "%.2f", P1.DPF);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 1, 2, "%.2f", P2.DPF);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 1, 3, "%.2f", P3.DPF);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 2, 1, "%.2f", P1.ph);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 2, 2, "%.2f", P2.ph);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 2, 3, "%.2f", P3.ph);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 3, 1, "%.2f", P1.P); // 有功功率
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 3, 2, "%.2f", P2.P);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 3, 3, "%.2f", P3.P);

      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 4, 1, "%.2f", P1.Power_p);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 4, 2, "%.2f", P2.Power_p);
      lv_table_set_cell_value_fmt(guider_ui.wave_model_table_2, 4, 3, "%.2f", P3.Power_p);
    }


    
    if (!lv_obj_has_flag(guider_ui.wave_model_one_value, LV_OBJ_FLAG_HIDDEN))
    {
      if (V_I_flag == 0) // 显示电压
      {
        lv_label_set_text_fmt(guider_ui.wave_model_one_value, "%.2f V", fft_1V.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_two_value, "%.2f V", fft_2V.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_three_value, "%.2f V", fft_3V.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_N_val, "%.2f V", fft_NV.RMS);
      }
      else if (V_I_flag == 1) // 显示电流
      {
        lv_label_set_text_fmt(guider_ui.wave_model_one_value, "%.2f A", fft_1I.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_two_value, "%.2f A", fft_2I.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_three_value, "%.2f A", fft_3I.RMS);
        lv_label_set_text_fmt(guider_ui.wave_model_N_val, "%.2f A", fft_NI.RMS);
      }

    
    }






    lv_label_set_text_fmt(guider_ui.wave_model_label_21, "t:%.2fms", 10);
    lv_label_set_text_fmt(guider_ui.wave_model_label_22, "V1:%.2fV", fft_1V.max_v);
    lv_label_set_text_fmt(guider_ui.wave_model_label_23, "V2:%.2fV", fft_2V.max_v);
    lv_label_set_text_fmt(guider_ui.wave_model_label_24, "V3:%.2fV", fft_3V.max_v);
    lv_label_set_text_fmt(guider_ui.wave_model_label_25, "VN:%.2fV", fft_NV.max_v);

    // lv_label_set_text_fmt(guider_ui.wave_model_one_value, "%.1fV",value_1);
    // lv_label_set_text_fmt(guider_ui.wave_model_two_value, "%.1fV",value_1);
    // lv_label_set_text_fmt(guider_ui.wave_model_three_value, "%.1fV",value_1);
    // lv_label_set_text_fmt(guider_ui.wave_model_N_val, "%.1fV",value_N);
}
