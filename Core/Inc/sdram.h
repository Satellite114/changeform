#ifndef __SDRAM_H__
#define __SDRAM_H__
#include "fmc.h"
#include "main.h"
void fsmc_sdram_test();
void FMC_SDRAM_ReadBuffer(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t n);
void FMC_SDRAM_WriteBuffer(uint8_t *pBuffer,uint32_t WriteAddr,uint32_t n);
#endif