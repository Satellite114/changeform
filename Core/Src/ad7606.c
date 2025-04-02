#include "ad7606.h"
#include "usart.h"


/*******************************************************
 * 
 * Declare a struct variable in ur app_code.c as bellow
 * AD7606Dev ad7606dev;
 * and initialize it.
 * 
********************************************************/

short testAdc[testCHs];   // just for test .


static void ini7606Paras(AD7606Dev * dev)
{ 
    dev->baseaddr=0x60000000;
    dev->interface=AD7606_PARALLEL;
    dev->range=AD7606_10V;
    dev->osr=AD7606_OSR_64;

}

void ad7606ini(AD7606Dev * dev)
{

    int i;

    ini7606Paras(dev);
    
    /// set rang 

    /// clear bufs.
    for(i=0;i<DataBufLen;i++)
    {
        dev->dataBuf[i]=0;
    }

	HAL_GPIO_WritePin(ADC_STBY_GPIO_Port,ADC_STBY_Pin,GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(ADC_RST_GPIO_Port,ADC_RST_Pin,GPIO_PIN_SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(ADC_RST_GPIO_Port,ADC_RST_Pin,GPIO_PIN_RESET);
	
}


void get_AD7606(void)
{
		// for(i=0;i<8;i++)
		// {
		// 	testAdc[i]=AD7606Addr;
		// }
}

void test_AD7606(void)
{
    int i;

    for(i=0;i<testCHs;i++)
    {
    	testAdc[i]=AD7606Addr;
    }
}


void print_AD7606(void)
{
    int i;
    printf("\r\n AD7606 DATAs:\r\n");
    for(i=0;i<testCHs;i++)
    {
        printf("\r\n DATA at CH%d:\t%.3f\r\n",i,testAdc[i]/32768.0*10);
    }
}