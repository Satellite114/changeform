#include "sdram.h"
/**
  * @brief  向sdram写入数据 ，在指定地址(WriteAddr+Bank5_SDRAM_ADDR)开始,连续写入n个字节
  * @param  pBuffer: 指向数据的指针 
  * @param  WriteAddr: 要写入的SDRAM内部地址
  * @param  n:要写入的字节数
  * @retval None.
  */

  void FMC_SDRAM_WriteBuffer(uint8_t *pBuffer,uint32_t WriteAddr,uint32_t n)
  {
  
    /* 检查SDRAM标志，等待至SDRAM空闲 */  
    while ( HAL_SDRAM_GetState(&hsdram1) != RESET)
    {
    }
      for(;n!=0;n--)
      {
          *(__IO uint8_t*)(SDRAM_BANK_ADDR+WriteAddr)=*pBuffer;
          WriteAddr++;
          pBuffer++;
      }
  }
  

  /**
  * @brief  从sdram读数据 ，在指定地址((WriteAddr+Bank5_SDRAM_ADDR))开始,连续读出n个字节.
  * @param  pBuffer: 指向数据的指针 
  * @param  ReadAddr: 要读出的起始地址
  * @param  n:要读出的字节数
  * @retval None.
  */
void FMC_SDRAM_ReadBuffer(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t n)
{

  /* 检查SDRAM标志，等待至SDRAM空闲 */  
  while ( HAL_SDRAM_GetState(&hsdram1) != RESET)
  {
  }
	for(;n!=0;n--)
	{
		*pBuffer++=*(__IO uint8_t*)(SDRAM_BANK_ADDR+ReadAddr);
		ReadAddr++;
	}
}


//SDRAM内存测试	    
void fsmc_sdram_test()
{  
	__IO uint32_t i=0;  	  
	__IO uint32_t temp=0;	   
	__IO uint32_t sval=0;	//在地址0读到的数据	  				   
  
	//每隔16K字节,写入一个数据,总共写入2048个数据,刚好是32M字节
	for(i=0;i<32*1024*1024;i+=16*1024)
	{
		*(__IO uint32_t*)(SDRAM_BANK_ADDR+i)=temp; 
		temp++;
	}
	//依次读出之前写入的数据,进行校验		  
 	for(i=0;i<32*1024*1024;i+=16*1024) 
	{	
  		temp=*(__IO uint32_t*)(SDRAM_BANK_ADDR+i);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//后面读出的数据一定要比第一次读到的数据大.	   		   
		printf("SDRAM Capacity:%dKB\r\n",(uint16_t)(temp-sval+1)*16);//打印SDRAM容量
 	}					 
}

