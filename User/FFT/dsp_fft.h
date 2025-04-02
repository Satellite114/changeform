#ifndef __DSP_FFT__H
#define __DSP_FFT__H

#include "stdint.h"
#include "stdio.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "ad7606.h"
#include "FreeRTOS.h"
// #include "cmsis_os2.h" // Add this line to include the header file for osEventFlagsId_t
#include "stdlib.h"
#define sqrt_2 1.414213562373
#define ADC_MAX_VALUE 32768.0f
#define ADC_VOLTAGE 10.0f
// #define FFT_LENGTH 256
#define M_PI 3.14159265
#define HARMONIC_COUNT 50 // 要计算的谐波个数（例如基波+4次谐波）
#define CFFT(x) &arm_cfft_sR_f32_len##x
#define FFT_LENGTH 2048
#define SAMPLING 12800

// extern osEventFlagsId_t Event_allHandle;

typedef enum
{
    /// @brief 正弦波
    FFT_SIN,
    /// @brief 三角波
    FFT_TRIANGLE,
    /// @brief 混合正弦交三角
    FFT_SIN_AND_TRIANGLE,
    /// @brief 混合三角交正弦
    FFT_TRIANGLE_AND_SIN,
    /// @brief 未知的波
    FFT_UNKNOW,
} FFT_TRANSFORM_WAVE_TYPE;
typedef uint8_t FFT_TRANSFORM_WAVE_TYPE_t;
// #pragma pack(2)
typedef struct
{
    uint16_t Sampling;                     // 采样频率
    uint32_t length;                       // FFT 长度
    float32_t adcConvertValue[FFT_LENGTH]; // FFT采样数组
    int16_t LVGL_wave[256];         // lvgl刷新数组
    int16_t LVGL_xb[FFT_LENGTH];           // 谐波数组
    float32_t FFT_OUT[FFT_LENGTH];         // 傅里叶变换幅值数组
    float32_t FFT_IN[FFT_LENGTH * 2];      //
    float32_t max_v;                       // 最大值
    float32_t min_v;                       // 最小值
    float freq;                            // 频率
    uint16_t index_;                       // 幅值的最大值索引
    float32_t max_fft;                     // 幅值最大值
    float THD_;                            // 总谐波失真
    float32_t FFT_PHASE[50];               // 相位角
    float32_t RMS;                         // 有效值
    float32_t RMS_xb[50];
    float32_t DC; // 直流成分
    uint8_t flag_V;
} FFT;
typedef struct
{
    double S; // 视在功率（S）
    double P; // 有功功率（P）
    double Q; // 无功功率（Q）//待修改
    FFT *fft_V;
    FFT *fft_I;
    double Power_s;
    double Power_p;
    double Power_q;
    // double K;   // 变压器K系数
    double PF;  // 功率因数
    double DPF; // 位移功率因数，只考虑基波
    double ph; //相位差

} phase;

typedef struct

{
    float32_t Voltage_Unbalance;
    float32_t current_Unbalance;
    phase *p1;
    phase *p2;
    phase *p3;
    double K;

} Voltage_three;

// #pragma pack()
void fft_run(FFT *fft);
uint8_t *floatToString(float value, uint8_t precision, uint8_t zero_show_str);
uint8_t *numberToString(int number);
float THD(float *Mag, int len);
uint16_t findPeaks(float32_t *in, uint16_t *peak_index, float32_t *peak_buf, uint16_t N);
void fft_find_max(uint16_t offset, float32_t *buffer, uint16_t find_len, float32_t *max_value, uint16_t *max_index);
void calculatePhase(FFT *fft);
// void calculatePhase(float32_t *fft_in, float32_t fft_phase, uint16_t length);
FFT_TRANSFORM_WAVE_TYPE check_fft_wave_type(void);
void integerToString(int num, uint8_t *output);
float32_t find_max(float32_t *buf, uint16_t len);
float32_t find_min(float32_t *buf, uint16_t len);
float Get_harmonic_U(float *harmonic_U, float *Mag, int st, int end, int len);
void FFT_Init(FFT *fft, uint16_t Sampling, uint16_t legth,uint8_t flag_V);
void FFT_Free(FFT *fft);
void PHASE_Init(phase *P, FFT *fft_V, FFT *fft_I);
void PHASE_run(phase *p);
void Voltage_three_Init(Voltage_three *v, phase *p1, phase *p2, phase *p3);
void Voltage_three_run(Voltage_three *v);
double calculate_unbalance(double a, double b, double c);
void downsample_data(float32_t rat,float32_t *input_array, uint16_t input_len, int16_t *output_array, uint16_t output_len,uint8_t flag);

#endif
