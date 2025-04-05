#ifndef __AD7606_H__
#define __AD7606_H__

#include "main.h"
#include "gpio.h"

#define AD7606Addr	*(volatile short*)(0x60000000)

#define DataBufLen  1024
#define testCHs 8

enum ad7606_interface {
  AD7606_SERIAL,
  AD7606_PARALLEL,
};

enum ad7606_range {
  AD7606_5V  = 1,
  AD7606_10V = 2,
};

enum ad7606_osr {
  AD7606_OSR_0,
  AD7606_OSR_2,
  AD7606_OSR_4,
  AD7606_OSR_8,
  AD7606_OSR_16,
  AD7606_OSR_32,
  AD7606_OSR_64,
  AD7606_OSR_128,
};

typedef struct ad7606
{
    /* data */
    uint32_t baseaddr;
    int16_t dataBuf[DataBufLen];
      enum ad7606_interface interface;
      enum ad7606_range range;
      enum ad7606_osr osr;
}AD7606Dev;


void ad7606ini(AD7606Dev * dev);

void Get_AD7606(void);


#endif