//
// Created by Alex-Hua on 2024/7/26.
//

#include "lcdTest.h"
#include "cmsis_os.h"

/*LCD测试函数*/
void LCD_TEST(void)
{
    // LCD_RST_CLR();
    // HAL_Delay(50);
    // LCD_RST_SET();
    // HAL_Delay(50);
    /*画线测试*/
    testlines();
    osDelay(1000);
    /*画正方形测试*/
    testdrawrects();
    osDelay(1000);
    /*画圆测试*/
    testfillcircles(15);
    osDelay(1000);
    /*字体测试*/
    tftPrintTest();
}

/*画线测试*/
void testlines(void)
{
    LCD_Clear(GREEN);
    POINT_COLOR=BLACK;
    for (int16_t x=0; x < SSD_VER_RESOLUTION; x+=6)
    {
        LCD_DrawLine(0, 0, x, SSD_HOR_RESOLUTION-1);
        osDelay(3);
    }
    for (int16_t y=0; y < SSD_HOR_RESOLUTION; y+=6)
    {
        LCD_DrawLine(0, 0, SSD_VER_RESOLUTION-1, y);
        osDelay(3);
    }

    LCD_Clear(GREEN);
    POINT_COLOR=BLUE;
    for (int16_t x=0; x < SSD_VER_RESOLUTION; x+=6)
    {
        LCD_DrawLine(SSD_VER_RESOLUTION-1, 0, x, SSD_HOR_RESOLUTION-1);
        osDelay(3);
    }
    for (int16_t y=0; y < SSD_HOR_RESOLUTION; y+=6)
    {
        LCD_DrawLine(SSD_VER_RESOLUTION-1, 0, 0, y);
        osDelay(3);
    }

    LCD_Clear(WHITE);
    POINT_COLOR=RED;
    for (int16_t y=0; y < SSD_HOR_RESOLUTION; y+=6)
    {
        LCD_DrawLine(0, SSD_HOR_RESOLUTION-1, SSD_VER_RESOLUTION-1, y);
        osDelay(3);
    }
    for (int16_t x=0; x < SSD_VER_RESOLUTION; x+=6)
    {
        LCD_DrawLine(0, SSD_HOR_RESOLUTION-1, x, 0);
        osDelay(3);
    }

    LCD_Clear(WHITE);
    POINT_COLOR=MAGENTA;
    for (int16_t x=0; x < SSD_VER_RESOLUTION; x+=6)
    {
        LCD_DrawLine(SSD_VER_RESOLUTION-1, SSD_HOR_RESOLUTION-1, x, 0);
        osDelay(3);
    }
    for (int16_t y=0; y < SSD_HOR_RESOLUTION; y+=6)
    {
        LCD_DrawLine(SSD_VER_RESOLUTION-1, SSD_HOR_RESOLUTION-1, 0, y);
        osDelay(3);
    }
}

/*画正方形测试*/
void testdrawrects(void)
{
    LCD_Clear(WHITE);
    POINT_COLOR=BLACK;
    for (int16_t x=0; x < SSD_VER_RESOLUTION; x+=6)
    {
        LCD_DrawRectangle(SSD_VER_RESOLUTION/2 -x/2, SSD_HOR_RESOLUTION/2 -x/2 , x, x);
    }
}

/*画圆测试*/
void testfillcircles(uint8_t radius)
{
    LCD_Clear(WHITE);
    POINT_COLOR=BLUE;
    for(int16_t x=radius; x < SSD_VER_RESOLUTION; x+=radius*2)
    {
        for(int16_t y=radius; y < SSD_HOR_RESOLUTION; y+=radius*2)
        {
            LCD_Draw_Circle(x, y, radius);
        }
    }
    osDelay(1500);
    LCD_Clear(WHITE);
    POINT_COLOR=MAGENTA;
    radius = radius / 2;
    for(int16_t x=radius; x < SSD_VER_RESOLUTION; x+=radius*2)
    {
        for(int16_t y=radius; y < SSD_HOR_RESOLUTION; y+=radius*2)
        {
            LCD_Draw_Circle(x, y, radius);
        }
    }
}

/*字体测试*/
void tftPrintTest(void)
{
    LCD_Clear(WHITE);
    LCD_SetCursor(0, 30);
    POINT_COLOR=RED;
    LCD_ShowString(0,30,200,16,16,(uint8_t *)"Hello World!");
    POINT_COLOR=YELLOW;
    LCD_ShowString(0,60,200,16,24,(uint8_t *)"Hello World!");
    POINT_COLOR=GREEN;
    LCD_ShowString(0,90,200,16,32,(uint8_t *)"Hello World!");
    POINT_COLOR=BLUE;
    LCD_ShowxNum(0,120,1234,4,24,1);
    osDelay(1500);
    POINT_COLOR=YELLOW;
    LCD_ShowString(0,180,200,16,24,(uint8_t *)"Hello World!");
    POINT_COLOR=GREEN;
    LCD_ShowString(0,210,200,16,32,(uint8_t *)" Want pi?");
    LCD_ShowString(0,240,300,16,32,(uint8_t *)" Print HEX! ZJX ZDY");
    POINT_COLOR=BLUE;
    LCD_ShowString(0,270,200,16,16,(uint8_t *)"Sketch has been");
    LCD_ShowString(0,300,200,16,24,(uint8_t *)"running for: ");
    POINT_COLOR=MAGENTA;
    LCD_ShowString(0,330,200,16,24,(uint8_t *)" seconds.");
    osDelay(2500);
}