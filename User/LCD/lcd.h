/**
 ****************************************************************************************************
 * @file        lcd.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.2
 * @date        2023-05-31
 * @brief       2.8寸/3.5寸/4.3寸/7寸 TFTLCD(MCU屏) 驱动代码
 *              支持驱动IC型号包括:ILI9341/NT35310/NT35510/SSD1963/ST7789/ST7796/ILI9806 等
 *
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200421
 * 第一次发布
 * V1.1 20200514
 * 1, 新增对ST7789 IC的支持
 * 2, 简化部分代码, 避免长判定
 * V1.2 20230531
 * 1, 新增对ST7796和ILI9806 IC支持
 *
 ****************************************************************************************************
 */

#ifndef __LCD_H
#define __LCD_H

#define FLASHTYPE 0 // 0：容量为128Mb的液晶，显示液晶储存器内部的图片
// 1：容量为1024Mb的液晶，显示液晶储存器内部的图片

#include "stdint.h"

/* FSMC相关参数 定义
 * 注意: 我们默认是通过FSMC块1来连接LCD, 块1有4个片选: FSMC_NE1~4
 *
 * 修改LCD_FSMC_NEX, 对应的LCD_CS_GPIO相关设置也得改
 * 修改LCD_FSMC_AX , 对应的LCD_RS_GPIO相关设置也得改
 */
#define LCD_FSMC_NEX 2/* 使用FSMC_NE4接LCD_CS,取值范围只能是: 1~4 */
#define LCD_FSMC_AX 6  /* 使用FSMC_A10接LCD_RS,取值范围是: 0 ~ 25 */

#define color_brown 0x40c0
#define color_black 0x0000
#define color_white 0xffff
#define color_red 0xf800
#define color_green 0x07e0
#define color_blue 0x001f
#define color_yellow color_red | color_green
#define color_cyan color_green | color_blue
#define color_purple color_red | color_blue

#define color65k_black 0x0000
#define color65k_white 0xffff
#define color65k_red 0xf800
#define color65k_green 0x07e0
#define color65k_blue 0x001f
#define color65k_yellow color65k_red | color65k_green
#define color65k_cyan color65k_green | color65k_blue
#define color65k_purple color65k_red | color65k_blue

#define color65k_grayscale1 2113
#define color65k_grayscale2 2113 * 2
#define color65k_grayscale3 2113 * 3
#define color65k_grayscale4 2113 * 4
#define color65k_grayscale5 2113 * 5
#define color65k_grayscale6 2113 * 6
#define color65k_grayscale7 2113 * 7
#define color65k_grayscale8 2113 * 8
#define color65k_grayscale9 2113 * 9
#define color65k_grayscale10 2113 * 10
#define color65k_grayscale11 2113 * 11
#define color65k_grayscale12 2113 * 12
#define color65k_grayscale13 2113 * 13
#define color65k_grayscale14 2113 * 14
#define color65k_grayscale15 2113 * 15
#define color65k_grayscale16 2113 * 16
#define color65k_grayscale17 2113 * 17
#define color65k_grayscale18 2113 * 18
#define color65k_grayscale19 2113 * 19
#define color65k_grayscale20 2113 * 20
#define color65k_grayscale21 2113 * 21
#define color65k_grayscale22 2113 * 22
#define color65k_grayscale23 2113 * 23
#define color65k_grayscale24 2113 * 24
#define color65k_grayscale25 2113 * 25
#define color65k_grayscale26 2113 * 26
#define color65k_grayscale27 2113 * 27
#define color65k_grayscale28 2113 * 28
#define color65k_grayscale29 2113 * 29
#define color65k_grayscale30 2113 * 30

#define cSetD0 0x01
#define cSetD1 0x02
#define cSetD2 0x04
#define cSetD3 0x08
#define cSetD4 0x10
#define cSetD5 0x20
#define cSetD6 0x40
#define cSetD7 0x80

#define cClrD0 0xfe
#define cClrD1 0xfd
#define cClrD2 0xfb
#define cClrD3 0xf7
#define cClrD4 0xef
#define cClrD5 0xdf
#define cClrD6 0xbf
#define cClrD7 0x7f

#define cClrD1D0 0xfc
#define cClrD1SetD0 0x01
#define cSetD1ClrD0 0x02
#define cSetD1D0 0x03
#define cClrD3D2 0xf3
#define cClrD3SetD2 0x04
#define cSetD3ClrD2 0x08
#define cSetD3D2 0x0c

#define cClrD2D1D0 0xf8
#define cClrD2D1SetD0 0x01
#define cClrD2SetD1ClrD0 0x02
#define cClrD2SetD1D0 0x03
#define cSetD2ClrD1D0 0x04
#define cSetD2ClrD1SetD0 0x05

#define cClrD6D5D4 0x8f
#define cClrD6D5SetD4 0x10
#define cClrD6SetD5ClrD4 0x20
#define cClrD6SetD5D4 0x30
#define cSetD6ClrD5D4 0x40
#define cSetD6ClrD5SetD4 0x50
#define cSetD6D5ClrD4 0x60
#define cSetD6D5D4 0x70
#define LCDXSIZE 480
#define LCDYSIZE 272
#define RA8876_DMA_CTRL 0xB6
#define RA8876_DMA_START 1
#define RA8876_SFL_CTRL 0xB7
#define RA8876_SERIAL_FLASH_SELECT0 0
#define RA8876_SERIAL_FLASH_SELECT1 1
#define RA8876_SERIAL_FLASH_FONT_MODE 0
#define RA8876_SERIAL_FLASH_DMA_MODE 1
#define RA8876_SERIAL_FLASH_ADDR_24BIT 0
#define RA8876_SERIAL_FLASH_ADDR_32BIT 1
#define RA8876_STANDARD_SPI_MODE 0
#define RA8876_FOLLOW_RA8876_MODE 1
#define RA8876_SPI_NORMAL_READ 0       // COMMAND 03h
#define RA8876_SPI_FAST_READ_8DUMMY 4  // COMMAND 0Bh
#define RA8876_SPI_FAST_READ_16DUMMY 8 // COMMAND 1Bh
#define RA8876_SPI_DUAL_READ_8DUMMY 2  // COMMAND 3Bh
#define RA8876_2XIO_READ_MODE_4DUMMY 3 // COMMAND BBh


#define VS64480M56_2 5   // 640*480分辨率

/******************************************************************************************/

/* LCD重要参数集 */
typedef struct
{
    uint16_t width;   /* LCD 宽度 */
    uint16_t height;  /* LCD 高度 */
    uint16_t id;      /* LCD ID */
    uint8_t dir;      /* 横屏还是竖屏控制：0，竖屏；1，横屏。 */
    uint16_t wramcmd; /* 开始写gram指令 */
    uint16_t setxcmd; /* 设置x坐标指令 */
    uint16_t setycmd; /* 设置y坐标指令 */
} _lcd_dev;

/* LCD参数 */
extern _lcd_dev lcddev; /* 管理LCD重要参数 */

/* LCD的画笔颜色和背景色 */
extern uint32_t g_point_color; /* 默认红色 */
extern uint32_t g_back_color;  /* 背景颜色.默认为白色 */

/* LCD地址结构体 */
typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE (uint32_t)((0X60000000 + (0X4000000 * (LCD_FSMC_NEX - 1))) | (((1 << LCD_FSMC_AX) * 2) - 2))
#define LCD ((LCD_TypeDef *)LCD_BASE)



// #define LCD_BASE 	((uint32_t)(0x64000000 | 0x0000007E))
// #define LCD 			((LCD_TypeDef *) LCD_BASE)



/******************************************************************************************/
/* 函数申明 */

void lcd_wr_data(volatile uint16_t data);          /* LCD写数据 */
void lcd_wr_regno(volatile uint16_t regno);        /* LCD写寄存器编号/地址 */
void lcd_write_reg(uint16_t regno, uint16_t data); /* LCD写寄存器的值 */

void W25N01_Reset(void);
void W25N01_Clear_BUF(void);
void W25N01_Set_ECC(void);
void Set_Backlight(uint8_t bl);
void GUI_CleanScreen(void);
void Display_ON(void);
void Display_OFF(void);
void Set_Color(uint16_t bc, uint16_t fc);
void LCD_Select(uint8_t lcdnum);
extern uint8_t MPU_Interface;
#if 0
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color); /* 画点(32位颜色,兼容LTDC) */

void lcd_clear(uint16_t color);                                                              /* LCD清屏 */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);                    /* 填充实心圆 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);                   /* 画圆 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color);                   /* 画水平线 */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);              /* 设置窗口 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);           /* 纯色填充矩形(32位颜色,兼容LTDC) */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);    /* 彩色填充矩形 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);      /* 画直线 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color); /* 画矩形 */

void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);                     /* 显示一个字符 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color);                   /* 显示数字 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color);    /* 扩展显示数字 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color); /* 显示字符串 */

#endif

void GUI_Point(uint16_t x, uint16_t y);                                                               // ��ʾһ����
void GUI_Circle(uint16_t x, uint16_t y, uint16_t r);                                                  // ��ʾ����Բ
void GUI_CircleFill(uint16_t x, uint16_t y, uint16_t r);                                              // ��ʾʵ��Բ
void GUI_Ellipse(uint16_t x, uint16_t y, uint16_t r1, uint16_t r2);                                   // ��ʾ������Բ
void GUI_EllipseFill(uint16_t x, uint16_t y, uint16_t r1, uint16_t r2);                               // ��ʾʵ����Բ������07
void GUI_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);      // ��ʾ���������Σ�����08
void GUI_Fill_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3); // ��ʾʵ�������Σ�����09
void GUI_Rectangle(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h);                                 // ��ʾ���ľ��Σ�����10
void GUI_RectangleFill(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h);                             // ��ʾʵ�ľ��Σ�����11
void GUI_Rectangle_R(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h, uint16_t r);                   // ��ʾ����Բ�Ǿ��Σ�����12
void GUI_RectangleFill_R(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h, uint16_t r);               // ��ʾʵ��Բ�Ǿ���
void GUI_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);                                    // ��ʾֱ��
void Dis_Image_Mix_1024Mb(uint16_t picnum, uint16_t x, uint16_t y);
void Dis_Image_Mix_128Mb(uint16_t picnum, uint16_t x, uint16_t y);


void Dis_Image_Mix(uint16_t picnum, uint16_t x, uint16_t y);
void Draw_Picture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, unsigned long numbers, const unsigned char *datap);
void Disp_FloatNum(uint8_t mode, uint32_t x, uint32_t y, uint8_t fontsize, uint8_t w, double value, unsigned char *format, uint16_t B_color, uint16_t F_color); // ��ʾ���������ͻ����Ը����Լ��������޸ĳ���
void Layer_Copy(unsigned long slayer, unsigned long dlayer, uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy, uint16_t w, uint16_t h);
void PIP2(unsigned long layer, uint16_t dx, uint16_t dy, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h);
void PIP1(unsigned long layer, uint16_t dx, uint16_t dy, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h);
void Set_Backlight(unsigned char bl);
void Set_Color(uint16_t bc, uint16_t fc);
void cnconfig(void);
void Display_Text(uint16_t x, uint16_t y, unsigned char tongtou, unsigned char *str);
void GUI_Point(uint16_t x, uint16_t y);
void Set_Font_Distance(uint16_t x, uint16_t y);

void Set_Font(unsigned char font);

void inverse(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void Sel_Layer(unsigned long clayer, unsigned long dlayer); // clayer:��ǰͼ��  dlayer��д��ͼ��

void Nandflash_Config(void);

void Geometric_Drawing(void);
void W25N01_Set_BUF(void);
void W25N01_Reset(void);
void W25N01_Clear_BUF(void);

uint16_t GUI_ReadPoint(uint16_t x, uint16_t y);

void Active_Window_WH(unsigned short WX, unsigned short HY);
void Active_Window_XY(unsigned short WX, unsigned short HY);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_WriteRAM_Prepare(void);
void Graphic_Mode_8876(void);
void test(uint16_t *buf, uint16_t width, uint16_t height,uint16_t x, uint16_t y);
#endif
