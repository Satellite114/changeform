/**
  ******************************************************************************
  * @file    httpd_cg_ssi.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    31-July-2013
  * @brief   Webserver SSI and CGI handlers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/


#include "lwip/debug.h"
#include "httpd.h"
#include "lwip/tcp.h"
#include "fs.h"
#include "main.h"
#include "ad7606.h"

#include <string.h>
#include <stdlib.h>

tSSIHandler ADC_Page_SSI_Handler;
uint32_t ADC_not_configured=1;

extern short testAdc[testCHs];
/* we will use character "t" as tag for CGI */
char const* TAGCHAR[]=
{
	"A0",
	"A1",
	"A2",
	"A3",
	"A4",
	"A5",
	"A6",
	"A7",
};
//char const** TAGS[]=&TAGCHAR;




/* CGI handler for LED control */ 
const char * LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/* Html request for "/leds.cgi" will start LEDS_CGI_Handler */
const tCGI LEDS_CGI={"/leds.cgi", LEDS_CGI_Handler};

/* Cgi call table, only one CGI used */
tCGI CGI_TAB[1];


/**
  * @brief  ADC_Handler : SSI handler for ADC page 
  * @param int iIndex - tag index in the tag array char const* TAGCHAR[].
  * @param char *pcInsert information need to be returned from SSI service.
  * @param iInsertLen - length of the charactars inserted following the TAGs? ... not clearly enough
  * @return  the length of pcInserts transfered to front end.
  */
u16_t ADC_Handler(int iIndex, char *pcInsert, int iInsertLen)
{
  /* We have only one SSI handler iIndex = 0 */
    
    char Digit[10]={0}; 
    short ADCVal = 0;      
		int i=0;
		if (iIndex <8)
		{
		/* copy buf value in AD7616 result bufs*/
     ADCVal = testAdc[iIndex]; 
		
		/* get digits to display */ 
     sprintf(Digit,"%2.3f",ADCVal/32768.0*10);
     
     while(Digit[i]!=0)
		 {
			 *(pcInsert+i)=Digit[i];
			 i++;
		 }
    /* prepare data to be inserted in html */

		/* strlen(pcInsert) characters need to be inserted in html*/
		iInsertLen=strlen(pcInsert);
		return iInsertLen;
		}
  return 0;
}

/**
  * @brief  CGI handler for LEDs control 
  */
const char * LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  uint32_t i=0;
  
  /* We have only one SSI handler iIndex = 0 */
  if (iIndex==0)
  {
    /* All leds off */
    // STM_EVAL_LEDOff(LED1);
    // STM_EVAL_LEDOff(LED2);
    // STM_EVAL_LEDOff(LED3);
    // STM_EVAL_LEDOff(LED4);
    
    /* Check cgi parameter : example GET /leds.cgi?led=2&led=4 */
    for (i=0; i<iNumParams; i++)
    {
      /* check parameter "led" */
      if (strcmp(pcParam[i] , "led")==0)   
      {
        /* switch led1 ON if 1 */
        if(strcmp(pcValue[i], "1") ==0) 
          HAL_GPIO_WritePin(PG14_GPIO_Port,PG14_Pin,GPIO_PIN_SET);
        /* switch led2 ON if 2 */
        else if(strcmp(pcValue[i], "2") ==0) 
          HAL_GPIO_WritePin(PG14_GPIO_Port,PG14_Pin,GPIO_PIN_SET);
        
        /* switch led3 ON if 3 */
        else if(strcmp(pcValue[i], "3") ==0) 
          HAL_GPIO_WritePin(PG14_GPIO_Port,PG14_Pin,GPIO_PIN_SET);
        
        /* switch led4 ON if 4 */
        else if(strcmp(pcValue[i], "4") ==0) 
          HAL_GPIO_WritePin(PG14_GPIO_Port,PG14_Pin,GPIO_PIN_SET);
      }
    }
  }
  /* uri to send after cgi call*/
  return "/STM32F4x7LED.html";  
}

/**
 * Initialize SSI handlers
 */
void httpd_ssi_init(void)
{  
  /* configure SSI handlers (ADC page SSI) */
  http_set_ssi_handler(ADC_Handler, TAGCHAR, 16);
}

/**
 * Initialize CGI handlers
 */
void httpd_cgi_init(void)
{ 
  /* configure CGI handlers (LEDs control CGI) */
  CGI_TAB[0] = LEDS_CGI;
  http_set_cgi_handlers(CGI_TAB, 1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
