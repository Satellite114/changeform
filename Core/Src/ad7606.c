#include "ad7606.h"
#include "usart.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "dsp_fft.h"

extern FFT fft_1V;
extern FFT fft_2V;
extern FFT fft_3V;
extern FFT fft_NV; // 四通道电压采样

extern FFT fft_1I;
extern FFT fft_2I;
extern FFT fft_3I;
extern FFT fft_NI; // 四通道电流采样
/*******************************************************
 *
 * Declare a struct variable in ur app_code.c as bellow
 * AD7606Dev ad7606dev;
 * and initialize it.
 *
 ********************************************************/
static void ini7606Paras(AD7606Dev *dev)
{
    dev->baseaddr = 0x60000000;
    dev->interface = AD7606_PARALLEL;
    dev->range = AD7606_10V;
    dev->osr = AD7606_OSR_64;
}

void ad7606ini(AD7606Dev *dev)
{
    int i;
    ini7606Paras(dev);
    /// set rang 硬件上JP3高电平，10V范围

    // for (i = 0; i < DataBufLen; i++)
    // {
    //     dev->dataBuf[i] = 0;
    // }
    HAL_GPIO_WritePin(ADC_STBY_GPIO_Port, ADC_STBY_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_RESET);
}

void Get_AD7606(void)
{
    static uint32_t j = 0;
    if (j == fft_1V.length)
    {
       
        j = 0;
        HAL_TIMEx_PWMN_Stop(&htim8, TIM_CHANNEL_3);
       
        return;
    }
  
    fft_1V.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_2V.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_3V.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_NV.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;

    fft_1I.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_2I.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_3I.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;
    fft_NI.adcConvertValue[j] = AD7606Addr* 10.0 / 32768.0;


    j += 1;
}
