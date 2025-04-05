#include "dsp_fft.h"
#include <math.h>
#include <string.h>
#include "arm_math.h"
extern float32_t rat;
extern float32_t step;
extern float32_t level;

void fft_run(FFT *fft)
{
    // 归一化 ADC 数据并填充复数数组
    float32_t max_v = -INFINITY, min_v = INFINITY;
    float32_t temp_RMS = 0;
    // 谐波有效值： 频域幅值*2/采样点数
    for (int i = 0; i < fft->length; i++)
    {
        // fft->LVGL_wave[i] = fft->adcConvertValue[i] * 50;
        fft->FFT_IN[2 * i] = fft->adcConvertValue[i];
        fft->FFT_IN[2 * i + 1] = 0; // 虚部

        temp_RMS += fft->adcConvertValue[i] * fft->adcConvertValue[i] / (float)fft->length;

        if (fft->adcConvertValue[i] > max_v)
            max_v = fft->adcConvertValue[i];
        if (fft->adcConvertValue[i] < min_v)
            min_v = fft->adcConvertValue[i];
    }
    downsample_data(rat, fft->adcConvertValue, fft->length, fft->LVGL_wave, 256, step);
    fft->RMS = sqrt(temp_RMS);

    fft->max_v = max_v;
    fft->min_v = min_v;

    // 执行 FFT
    arm_cfft_f32(&arm_cfft_sR_f32_len2048, fft->FFT_IN, 0, 1);

    // 计算幅值并找最大值
    arm_cmplx_mag_f32(fft->FFT_IN, fft->FFT_OUT, fft->length);

    float32_t temp_max = INT32_MIN;
    uint16_t max_idx = 1;

    for (uint16_t i = 1; i < fft->length / 2; i++)
    {
        if (fft->FFT_OUT[i] > temp_max)
        {
            temp_max = fft->FFT_OUT[i];
            max_idx = i;
        }
    }
    fft->max_fft = temp_max;
    fft->index_ = max_idx;

    // uint16_t step; // 12800/2048=6.25
    // step = 50.0f / ((float32_t)(fft->Sampling) / (float32_t)(fft->length));
    // step = 8;
    for (uint16_t i = 0; i < 50; i++)
    {
        fft->LVGL_xb[i] = (fft->FFT_OUT[8 * (i + 1)]/fft->max_fft) * 100;
    }

    // 计算基波频率
    fft->freq = ((float)(fft->Sampling)) / ((float)fft->length) * fft->index_;
    fft->DC = fft->FFT_OUT[0] / (float)fft->length;
    // 计算总谐波失真（THD）
    fft->THD_ = THD(fft->FFT_OUT, fft->length);

    // 计算相位
    calculatePhase(fft);

    // 触发事件
    // osEventFlagsSet(Event_allHandle, EVENT_FFT);
}

float THD(float *Mag, int len)
{
    float ans = 0.0;
    uint16_t max_index = 1;

    // 查找基波索引
    for (uint16_t i = 2; i < len / 2; i++)
    {
        if (Mag[i] > Mag[max_index])
        {
            max_index = i;
        }
    }

    // 计算 THD
    float max_mag_sq = Mag[max_index] * Mag[max_index];
    for (uint16_t i = 2 * max_index; i < len / 2; i += max_index)
    {
        ans += Mag[i] * Mag[i];
    }

    return sqrtf(ans / max_mag_sq);
}

void fft_find_max(uint16_t offset, float32_t *buffer, uint16_t find_len, float32_t *max_value, uint16_t *max_index)
{
    float32_t max_v = buffer[offset];
    uint16_t max_idx = offset;

    for (uint16_t i = offset + 1; i < offset + find_len; i++)
    {
        if (buffer[i] > max_v)
        {
            max_v = buffer[i];
            max_idx = i;
        }
    }
    *max_value = max_v;
    *max_index = max_idx;
}

void calculatePhase(FFT *fft)
{

    uint16_t temp = fft->index_;
    uint16_t step; // 12800/2048=6.25
    step = 50.0f / ((float32_t)(fft->Sampling) / (float32_t)(fft->length));
    for (uint8_t i = 0; i < 50; i++)
    {
        float real = fft->FFT_IN[2 * temp];
        float imag = fft->FFT_IN[2 * temp + 1];

        fft->FFT_PHASE[i] = atan2f(imag, real) * (180.0f / M_PI);
        temp += step;
    } // PHASE[0]为基波相位角
}

void FFT_Init(FFT *fft, uint16_t Sampling, uint16_t legth, uint8_t flag_V)

{

    fft->Sampling = Sampling;
    fft->length = legth;

    // 初始化默认值
    fft->max_v = 0.0f;
    fft->min_v = 0.0f;
    fft->freq = 0.0f;
    fft->index_ = 0;
    fft->max_fft = 0.0f;
    fft->THD_ = 0.0f;
    // fft->FFT_PHASE = 0.0f;
    fft->flag_V = flag_V;
}

void FFT_Free(FFT *fft)
{
    if (fft)
    {
        free(fft->adcConvertValue);
        free(fft->FFT_OUT);
        free(fft->FFT_IN);
        free(fft->LVGL_wave);
        free(fft->LVGL_xb);
        free(fft);
    }
}
void PHASE_Init(phase *P, FFT *fft_V, FFT *fft_I)
{
    P->P = 0;
    P->Q = 0;
    P->S = 0;
    P->fft_I = fft_I;
    P->fft_V = fft_V;
    P->Power_p = 0;
    P->Power_q = 0;
    P->Power_s = 0;
}
void PHASE_run(phase *p)
{
    double temp = 0;
    double time = (1 / (float32_t)(p->fft_I->Sampling)) * (float32_t)(p->fft_I->length);
    for (uint16_t i = 0; i < p->fft_I->length; i++)
    {
        temp += p->fft_I->adcConvertValue[i] * p->fft_V->adcConvertValue[i];
    }

    p->P = temp / p->fft_I->length;
    p->Power_p += p->P * time; /*  double S; // 视在功率（S）
     double P; // 有功功率（P）
     double Q; // 无功功率（Q）//待修改*/
    // double dert_ph = (p->fft_V->FFT_PHASE) - (p->fft_I->FFT_PHASE); // cosΦ=P/S
    p->S = p->fft_I->RMS * p->fft_V->RMS;
    p->Power_s += p->S * time;
    p->Q = sqrt((p->S) * (p->S) + (p->P) * (p->P));
    p->Power_q += p->Q * time;
    // double K; // 变压器K系数
    // for (uint16_t i = 0; i < 50; i++)
    // {
    //     K += pow((i + 1), 2) * pow((p->fft_I->LVGL_xb[i] * 2 / p->fft_I->length), 2) / pow((p->fft_I->LVGL_xb[0] * 2 / p->fft_I->length), 2);
    // }
    // p->K = K;
    p->ph = (p->fft_V->FFT_PHASE[0]) - (p->fft_I->FFT_PHASE[0]);
    p->DPF = cos(p->ph);
    p->PF = p->P / p->S;
}
void Voltage_three_Init(Voltage_three *v, phase *p1, phase *p2, phase *p3)
{
    v->current_Unbalance = 0;
    v->K = 0;
    v->p1 = p1;
    v->p2 = p2;
    v->p3 = p3;
    v->Voltage_Unbalance = 0;
}
void Voltage_three_run(Voltage_three *v)
{

    // double K; // 变压器K系数
    // for (uint16_t i = 0; i < 50; i++)
    // {
    //     K += pow((i + 1), 2) * pow((v->p1->fft_I->LVGL_xb[i] * 2 / v->p1->fft_I->length), 2) / pow((v->p1->fft_I->LVGL_xb[0] * 2 / v->p1->fft_I->length), 2);
    // }
    // v->K = K;
    // v->current_Unbalance = calculate_unbalance(v->p1->fft_I->RMS, v->p2->fft_I->RMS, v->p3->fft_I->RMS);
    // v->Voltage_Unbalance = calculate_unbalance(v->p1->fft_V->RMS, v->p2->fft_V->RMS, v->p3->fft_V->RMS);
}
double calculate_unbalance(double a, double b, double c)
{
    double avg = (a + b + c) / 3.0;
    double max_dev = fmax(fabs(a - avg), fmax(fabs(b - avg), fabs(c - avg)));
    return (max_dev / avg) * 100.0; // 以百分比表示
}
void downsample_data(float32_t rat, float32_t *input_array, uint16_t input_len, int16_t *output_array, uint16_t output_len, uint8_t step)
{
    if (input_len < output_len || output_len <= 0)
        return; // 避免数组越界

    for (int i = 0; i < output_len; i++)
    {
        double sum = 0;
        for (int j = 0; j < step; j++)
        {
            sum += (input_array[i * step + j]) * rat + level;
        }
        output_array[i] = sum / step; // 取平均值
    }
}
