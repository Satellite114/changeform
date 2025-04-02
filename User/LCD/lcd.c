

#include "stdint.h"
#include "lcd.h"
#include "lcdfont.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"

uint32_t g_point_color = 0XF800;
uint32_t g_back_color = 0XFFFF;

_lcd_dev lcddev;

/**
 * @brief
 * @param       data:
 * @retval
 */
void lcd_wr_data(volatile uint16_t data)
{
    data = data;
    LCD->LCD_RAM = data;
}

/**
 * @brief
 * @param       regno:
 * @retval
 */
void lcd_wr_regno(volatile uint16_t regno)
{
    regno = regno;
    LCD->LCD_REG = regno;
}

/**
 * @brief
 * @param       regno:
 * @param       data:
 * @retval
 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    LCD->LCD_REG = regno;
    LCD->LCD_RAM = data;
}

uint8_t DRAM_FREQ, CORE_FREQ, SCAN_FREQ, E0VALUE, MPU_Interface=2, FONT;
uint32_t Current_Layer, Draw_Layer, Layer0 = 0, Layer1 = 0, Layer2 = 0, Layer3 = 0;
uint16_t lcdx = 640, lcdy = 480;
volatile uint16_t Bcolor = 0X0000, Fcolor = 0X0000;

#define LCD_CmdWrite(cmd) lcd_wr_regno(cmd)
#define LCD_DataWrite(dat) lcd_wr_data(dat)
#define LCD_DataRead() LCD->LCD_RAM
#define LCD_StatusRead() LCD->LCD_REG
#define OSC_FREQ 11
#define Delaly1ms() HAL_Delay(1)
#define delay_us(x) HAL_Delay(1)
#define DelayMS(ms) HAL_Delay(ms)

void RA8876_HW_Reset()
{
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    DelayMS(100);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    DelayMS(100);
}

void Write_Dir(uint8_t _ucRegAddr, uint8_t _ucRegValue)
{
    LCD_CmdWrite(_ucRegAddr);
    LCD_DataWrite(_ucRegValue);
}

void Enable_PLL(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);

    delay_us(100);
}
void Disable_PLL(void)
{
    /*  0: PLL disable; allow change PLL parameter.
        1: PLL enable; cannot change PLL parameter.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);

    delay_us(100);
    // while( LCD_RegisterRead(0x01)&0x80 );//check PLL was disabled.
}

// 0: inactive (nSS port will goes high)
void nSS_Inactive(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}

void Check_Mem_WR_FIFO_not_Full(void)
{
    /*	0: Memory Write FIFO is not full.
        1: Memory Write FIFO is full.		*/
    do
    {

    } while (LCD_StatusRead() & 0x80);
}
void Check_Mem_WR_FIFO_Empty(void)
{
    /*	0: Memory Write FIFO is not empty.
        1: Memory Write FIFO is empty.		*/
    do
    {

    } while ((LCD_StatusRead() & 0x40) == 0x00);
}
void Check_Mem_RD_FIFO_not_Full(void)
{
    /*	0: Memory Read FIFO is not full.
        1: Memory Read FIFO is full.		*/
    do
    {

    } while (LCD_StatusRead() & 0x20);
}
void Check_Mem_RD_FIFO_not_Empty(void)
{
    /*	0: Memory Read FIFO is not empty.
        1: Memory Read FIFO is empty.
            */
    do
    {

    } while (LCD_StatusRead() & 0x10);
}
void Check_2D_Busy(void)
{
    do
    {
    } while (LCD_StatusRead() & 0x08);
}
void Check_SDRAM_Ready(void)
{
    /*	0: SDRAM is not ready for access
        1: SDRAM is ready for access		*/
    unsigned char temp;
    do
    {
        temp = LCD_StatusRead();
    } while ((temp & 0x04) == 0x00);
}

unsigned char Power_Saving_Status(void)
{
    unsigned char temp;

    if ((LCD_StatusRead() & 0x02) == 0x02)
        temp = 1;
    else
        temp = 0;

    return temp;
}

void Check_Power_is_Normal(void) // �O Normal mode �N���}
{
    /*	0: Normal operation state
        1: Power saving state		*/
    do
    {

    } while (LCD_StatusRead() & 0x02);
}
void Check_Power_is_Saving(void) // �O Saving mode �N���}
{
    /*	0: Normal operation state
        1: Power saving state		*/
    do
    {

    } while ((LCD_StatusRead() & 0x02) == 0x00);
}
void Check_NO_Interrupt(void) // �S�� Interrupt �N���}
{
    /*	0: without interrupt event
        1: interrupt event occur
            */
    do
    {

    } while (LCD_StatusRead() & 0x01);
}
void Check_Interrupt_Occur(void) // �� Interrupt �N���}
{
    /*	0: without interrupt event
        1: interrupt event occur
            */
    do
    {

    } while ((LCD_StatusRead() & 0x01) == 0x00);
}

void Check_Busy_Draw(void)
{
    unsigned char temp;

    //(0)
    //	delay_ms(10);

    //(A)
    do
    {
        temp = LCD_StatusRead();
    } while (temp & 0x08);
    /*
    //(B)
        do
        {
            LCD_CmdWrite(0x67);
            temp=LCD_DataRead();
        }	while(temp&0x80);

    //(C)
        do
        {
            //(1)
            temp=LCD_RegisterRead(0x76);
            //(2)
            //LCD_CmdWrite(0x76);
            //temp=LCD_DataRead();
        }	while(temp&0x80);
    */

    // delay_ms(10);
}

//[00h]=========================================================================

void RA8876_SW_Reset(void) // IC Reset?A??���|�MRegister/Memory?C
{
    unsigned char temp;

    LCD_CmdWrite(0x00);
    temp = LCD_DataRead();
    temp |= 0x01;
    LCD_DataWrite(temp);

    do
    {
        temp = LCD_DataRead();
    } while (temp & 0x01);
}

//[01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h][01h]

void RA8876_Sleep(void)
{
    /*  0: Normal mode.
        1: Sleep mode.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void RA8876_WakeUp(void)
{
    /*  0: Normal mode.
        1: Sleep mode.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Key_Scan_Enable(void)
{
    /*  0: Disable.
        1: Enable.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Key_Scan_Disable(void)
{
    /*  0: Disable.
        1: Enable.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void TFT_24bit(void)
{
    /*  00b: 24-bits output.
        01b: 18-bits output, unused pins are set as GPIO.
        10b: 16-bits output, unused pins are set as GPIO.
        11b: LVDS, all 24-bits unused output pins are set as GPIO.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void TFT_18bit(void)
{
    /*  00b: 24-bits output.
        01b: 18-bits output, unused pins are set as GPIO.
        10b: 16-bits output, unused pins are set as GPIO.
        11b: LVDS, all 24-bits unused output pins are set as GPIO.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void TFT_16bit(void)
{
    /*  00b: 24-bits output.
        01b: 18-bits output, unused pins are set as GPIO.
        10b: 16-bits output, unused pins are set as GPIO.
        11b: LVDS, all 24-bits unused output pins are set as GPIO.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD4;
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void TFT_LVDS(void)
{
    /*  00b: 24-bits output.
        01b: 18-bits output, unused pins are set as GPIO.
        10b: 16-bits output, unused pins are set as GPIO.
        11b: LVDS, all 24-bits unused output pins are set as GPIO.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD4;
    temp |= cSetD3;
    LCD_DataWrite(temp);
}

void RA8876_I2CM_Enable(void)
{
    /*  I2C master Interface Enable/Disable
        0: Disable
        1: Enable*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

void RA8876_I2CM_Disable(void)
{
    /*  I2C master Interface Enable/Disable
        0: Disable
        1: Enable*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}

void Enable_SFlash_SPI(void)
{
    /*  Serial Flash SPI Interface Enable/Disable
        0: Disable
        1: Enable*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}

void Disable_SFlash_SPI(void)
{
    /*  Serial Flash SPI Interface Enable/Disable
        0: Disable
        1: Enable*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD1;
    printf("X=%d\n", temp);
    printf("Y=%d\n", temp);
    LCD_DataWrite(temp);
}
void Host_Bus_8bit(void)
{
    /*  Parallel Host Data Bus Width Selection
        0: 8-bit Parallel Host Data Bus.
        1: 16-bit Parallel Host Data Bus.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Host_Bus_16bit(void)
{
    /*  Parallel Host Data Bus Width Selection
        0: 8-bit Parallel Host Data Bus.
        1: 16-bit Parallel Host Data Bus.*/
    unsigned char temp;
    LCD_CmdWrite(0x01);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h][02h]

void RGB_8b_8bpp(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void RGB_8b_16bpp(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void RGB_8b_24bpp(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}

void RGB_16b_8bpp(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void RGB_16b_16bpp(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void RGB_16b_24bpp_mode1(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void RGB_16b_24bpp_mode2(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}

void MemRead_Left_Right_Top_Down(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void MemRead_Right_Left_Top_Down(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void MemRead_Top_Down_Left_Right(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void MemRead_Down_Top_Left_Right(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void MemWrite_Left_Right_Top_Down(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD2;
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void MemWrite_Right_Left_Top_Down(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp &= cClrD2;
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void MemWrite_Top_Down_Left_Right(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD2;
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void MemWrite_Down_Top_Left_Right(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x02);
    temp = LCD_DataRead();
    temp |= cSetD2;
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
//[03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h][03h]
void Interrupt_Active_Low(void)
{
    /*  MPU Interrupt active level
        0 : active low.
        1 : active high.*/
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Interrupt_Active_High(void)
{
    /*  MPU Interrupt active level
        0 : active low.
        1 : active high.*/
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Debounce(void)
{
    /*  External interrupt de-bounce
        0 : without de-bounce
        1 : enable de-bounce (1024 OSC clock)*/
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Nodebounce(void)
{
    /*  External interrupt de-bounce
        0 : without de-bounce
        1 : enable de-bounce (1024 OSC clock)*/
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Input_Low_Level_Trigger(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Input_High_Level_Trigger(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Input_Falling_Edge_Trigger(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void ExtInterrupt_Input_Rising_Edge_Trigger(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void LVDS_Format1(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void LVDS_Format2(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Graphic_Mode_8876(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Text_Mode_8876(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Memory_Select_SDRAM(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0; // B
    LCD_DataWrite(temp);
}
void Memory_Select_Graphic_Cursor_RAM(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Memory_Select_Color_Palette_RAM(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[05h]=========================================================================
//[06h]=========================================================================
//[07h]=========================================================================
//[08h]=========================================================================
//[09h]=========================================================================
//[0Ah]=========================================================================
//[0Bh]=========================================================================
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_CmdWrite(0x5F);
    LCD_DataWrite(Xpos);
    LCD_CmdWrite(0x60);
    LCD_DataWrite(Xpos >> 8);
    LCD_CmdWrite(0x61);
    LCD_DataWrite(Ypos);
    LCD_CmdWrite(0x62);
    LCD_DataWrite(Ypos >> 8);
}
void LCD_WriteRAM_Prepare(void)
{
    LCD_CmdWrite(0x04); //
}
void Enable_Resume_Interrupt(void)
{
    /*
    Resume Interrupt Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Disable_Resume_Interrupt(void)
{
    /*
    Resume Interrupt Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Enable_ExtInterrupt_Input(void)
{
    /*
    External Interrupt (PS[0] pin) Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Disable_ExtInterrupt_Input(void)
{
    /*
    External Interrupt (PS[0] pin) Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Enable_I2CM_Interrupt(void)
{
    /*
    I2C Master Interrupt Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Disable_I2CM_Interrupt(void)
{
    /*
    I2C Master Interrupt Enable
    0: Disable.
    1: Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Enable_Vsync_Interrupt(void)
{
    /*
    Vsync time base interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Disable_Vsync_Interrupt(void)
{
    /*
    Vsync time base interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Enable_KeyScan_Interrupt(void)
{
    /*
    Key Scan Interrupt Enable Bit
    0: Disable Key scan interrupt.
    1: Enable Key scan interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Disable_KeyScan_Interrupt(void)
{
    /*
    Key Scan Interrupt Enable Bit
    0: Disable Key scan interrupt.
    1: Enable Key scan interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Enable_DMA_Draw_BTE_Interrupt(void)
{
    /*
    Serial flash DMA Complete | Draw task finished | BTE Process
    Complete etc. Interrupt Enable
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Disable_DMA_Draw_BTE_Interrupt(void)
{
    /*
    Serial flash DMA Complete | Draw task finished | BTE Process
    Complete etc. Interrupt Enable
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Enable_PWM1_Interrupt(void)
{
    /*
    PWM timer 1 Interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Disable_PWM1_Interrupt(void)
{
    /*
    PWM timer 1 Interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Enable_PWM0_Interrupt(void)
{
    /*
    PWM timer 0 Interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Disable_PWM0_Interrupt(void)
{
    /*
    PWM timer 0 Interrupt Enable Bit
    0: Disable Interrupt.
    1: Enable Interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0B);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}

//[0Ch]=========================================================================
unsigned char Read_Interrupt_status(void)
{
    /*
    [Bit7]Read Function ..Resume Interrupt Status
    0: No Resume interrupt happens.
    1: Resume interrupt happens.
    [Bit6]Read Function .. PS[0] pin Interrupt Status
    0: No PS[0] pin interrupt happens.
    1: PS[0] pin interrupt happens.
    [Bit5]Read Function .. I2C master Interrupt Status
    0: No I2C master interrupt happens.
    1: I2C master interrupt happens.
    [Bit4]Read Function .. Vsync Interrupt Status
    0: No interrupt happens.
    1: interrupt happens.
    [Bit3]Read Function ..Key Scan Interrupt Status
    0: No Key Scan interrupt happens.
    1: Key Scan interrupt happens.
    [Bit2]Read Function..Interrupt Status
    0: No interrupt happens.
    1: interrupt happens.
    [Bit1]Read Function..Interrupt Status
    0: No interrupt happens.
    1: interrupt happens.
    [Bit0]Read Function..Interrupt Status
    0: No interrupt happens.
    1: interrupt happens.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    return temp;
}
void Clear_Resume_Interrupt_Flag(void)
{
    /*
    Resume Interrupt flag
    Write Function .. Resume Interrupt Clear Bit
    0: No operation.
    1: Clear Resume interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Clear_ExtInterrupt_Input_Flag(void)
{
    /*
    External Interrupt (PS[0] pin) flag
    Write Function .. PS[0] pin edge Interrupt Clear Bit
    0: No operation.
    1: Clear the PS[0] pin edge interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Clear_I2CM_Interrupt_Flag(void)
{
    /*
    I2C master Interrupt flag
    Write Function.. I2C master Interrupt Clear Bit
    0: No operation.
    1: Clear the I2C master interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Clear_Vsync_Interrupt_Flag(void)
{
    /*
    Vsync Time base interrupt flag
    Write Function ..Vsync Interrupt Clear Bit
    0: No operation.
    1: Clear the interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Clear_KeyScan_Interrupt_Flag(void)
{
    /*
    Key Scan Interrupt flag
    Write Function..Key Scan Interrupt Clear Bit
    0: No operation.
    1: Clear the Key Scan interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Clear_DMA_Draw_BTE_Interrupt_Flag(void)
{
    /*
    Serial flash DMA Complete | Draw task finished | BTE
    Process Complete etc. Interrupt flag
    Write Function.. Interrupt Clear Bit
    0: No operation.
    1: Clear interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Clear_PWM1_Interrupt_Flag(void)
{
    /*
    PWM 1 timer Interrupt flag
    Write Function..Interrupt Clear Bit
    0: No operation.
    1: Clear interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Clear_PWM0_Interrupt_Flag(void)
{
    /*
    PWM 0 timer Interrupt flag
    Write Function..Interrupt Clear Bit
    0: No operation.
    1: Clear interrupt.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0C);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
//[0Dh]=========================================================================
void Mask_Resume_Interrupt_Flag(void)
{
    /*
    Mask Resume Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Mask_ExtInterrupt_Input_Flag(void)
{
    /*
    Mask External Interrupt (PS[0] pin) Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Mask_I2CM_Interrupt_Flag(void)
{
    /*
    Mask I2C Master Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Mask_Vsync_Interrupt_Flag(void)
{
    /*
    Mask Vsync time base interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Mask_KeyScan_Interrupt_Flag(void)
{
    /*
    Mask Key Scan Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Mask_DMA_Draw_BTE_Interrupt_Flag(void)
{
    /*
    Mask Serial flash DMA Complete | Draw task finished | BTE
    Process Complete etc. Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Mask_PWM1_Interrupt_Flag(void)
{
    /*
    Mask PWM timer 1 Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Mask_PWM0_Interrupt_Flag(void)
{
    /*
    Mask PWM timer 0 Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

void Enable_Resume_Interrupt_Flag(void)
{
    /*
    Mask Resume Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Enable_ExtInterrupt_Inpur_Flag(void)
{
    /*
    Mask External Interrupt (PS[0] pin) Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Enable_I2CM_Interrupt_Flag(void)
{
    /*
    Mask I2C Master Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Enable_Vsync_Interrupt_Flag(void)
{
    /*
    Mask Vsync time base interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Enable_KeyScan_Interrupt_Flag(void)
{
    /*
    Mask Key Scan Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Enable_DMA_Draw_BTE_Interrupt_Flag(void)
{
    /*
    Mask Serial flash DMA Complete | Draw task finished | BTE
    Process Complete etc. Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Enable_PWM1_Interrupt_Flag(void)
{
    /*
    Mask PWM timer 1 Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Enable_PWM0_Interrupt_Flag(void)
{
    /*
    Mask PWM timer 0 Interrupt Flag
    0: Enable.
    1: Mask.
    */
    unsigned char temp;
    LCD_CmdWrite(0x0D);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}

//[0Eh]=========================================================================
void Enable_GPIOF_PullUp(void)
{
    /*
    GPIO_F[7:0] Pull-Up Enable (XPDAT[23:19, 15:13])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Enable_GPIOE_PullUp(void)
{
    /*
    GPIO_E[7:0] Pull-Up Enable (XPDAT[12:10, 7:3])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Enable_GPIOD_PullUp(void)
{
    /*
    GPIO_D[7:0] Pull-Up Enable (XPDAT[18, 2, 17, 16, 9, 8, 1,0])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Enable_GPIOC_PullUp(void)
{
    /*
    GPIO_C[6:0] Pull-Up Enable (XSDA, XSCL, XnSFCS1,
    XnSFCS0, XMISO, XMOSI , XSCK)
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Enable_XDB15_8_PullUp(void)
{
    /*
    XDB[15:8] Pull-Up Enable
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Enable_XDB7_0_PullUp(void)
{
    /*
    XDB[7:0] Pull-Up Enable
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Disable_GPIOF_PullUp(void)
{
    /*
    GPIO_F[7:0] Pull-Up Enable (XPDAT[23:19, 15:13])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Disable_GPIOE_PullUp(void)
{
    /*
    GPIO_E[7:0] Pull-Up Enable (XPDAT[12:10, 7:3])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Disable_GPIOD_PullUp(void)
{
    /*
    GPIO_D[7:0] Pull-Up Enable (XPDAT[18, 2, 17, 16, 9, 8, 1,0])
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Disable_GPIOC_PullUp(void)
{
    /*
    GPIO_C[6:0] Pull-Up Enable (XSDA, XSCL, XnSFCS1,
    XnSFCS0, XMISO, XMOSI , XSCK)
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Disable_XDB15_8_PullUp(void)
{
    /*
    XDB[15:8] Pull-Up Enable
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Disable_XDB7_0_PullUp(void)
{
    /*
    XDB[7:0] Pull-Up Enable
    0: Pull-Up Disable
    1: Pull-Up Enable
    */
    unsigned char temp;
    LCD_CmdWrite(0x0E);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
//[0Fh]=========================================================================
void XPDAT18_Set_GPIO_D7(void)
{
    /*
    XPDAT[18] ?V not scan function select
    0: GPIO-D7
    1: KOUT[4]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void XPDAT18_Set_KOUT4(void)
{
    /*
    XPDAT[18] ?V not scan function select
    0: GPIO-D7
    1: KOUT[4]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void XPDAT17_Set_GPIO_D5(void)
{
    /*
    XPDAT[17] ?V not scan function select
    0: GPIO-D5
    1: KOUT[2]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void XPDAT17_Set_KOUT2(void)
{
    /*
    XPDAT[17] ?V not scan function select
    0: GPIO-D5
    1: KOUT[2]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void XPDAT16_Set_GPIO_D4(void)
{
    /*
    XPDAT[16] ?V not scan function select
    0: GPIO-D4
    1: KOUT[1]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void XPDAT16_Set_KOUT1(void)
{
    /*
    XPDAT[16] ?V not scan function select
    0: GPIO-D4
    1: KOUT[1]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void XPDAT9_Set_GPIO_D3(void)
{
    /*
    XPDAT[9] ?V not scan function select
    0: GPIO-D3
    1: KOUT[3]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void XPDAT9_Set_KOUT3(void)
{
    /*
    XPDAT[9] ?V not scan function select
    0: GPIO-D3
    1: KOUT[3]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void XPDAT8_Set_GPIO_D2(void)
{
    /*
    XPDAT[8] ?V not scan function select
    0: GPIO-D2
    1: KIN[3]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void XPDAT8_Set_KIN3(void)
{
    /*
    XPDAT[8] ?V not scan function select
    0: GPIO-D2
    1: KIN[3]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void XPDAT2_Set_GPIO_D6(void)
{
    /*
    XPDAT[2] ?V not scan function select
    0: GPIO-D6
    1: KIN[4]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void XPDAT2_Set_KIN4(void)
{
    /*
    XPDAT[2] ?V not scan function select
    0: GPIO-D6
    1: KIN[4]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void XPDAT1_Set_GPIO_D1(void)
{
    /*
    XPDAT[1] ?V not scan function select
    0: GPIO-D1
    1: KIN[2]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void XPDAT1_Set_KIN2(void)
{
    /*
    XPDAT[1] ?V not scan function select
    0: GPIO-D1
    1: KIN[2]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void XPDAT0_Set_GPIO_D0(void)
{
    /*
    XPDAT[0] ?V not scan function select
    0: GPIO-D0
    1: KIN[1]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void XPDAT0_Set_KIN1(void)
{
    /*
    XPDAT[0] ?V not scan function select
    0: GPIO-D0
    1: KIN[1]
    */
    unsigned char temp;
    LCD_CmdWrite(0x0F);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[10h]=========================================================================
void Enable_PIP1(void)
{
    /*
    PIP 1 window Enable/Disable
    0 : PIP 1 window disable.
    1 : PIP 1 window enable
    PIP 1 window always on top of PIP 2 window.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Disable_PIP1(void)
{
    /*
    PIP 1 window Enable/Disable
    0 : PIP 1 window disable.
    1 : PIP 1 window enable
    PIP 1 window always on top of PIP 2 window.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Enable_PIP2(void)
{
    /*
    PIP 2 window Enable/Disable
    0 : PIP 2 window disable.
    1 : PIP 2 window enable
    PIP 1 window always on top of PIP 2 window.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Disable_PIP2(void)
{
    /*
    PIP 2 window Enable/Disable
    0 : PIP 2 window disable.
    1 : PIP 2 window enable
    PIP 1 window always on top of PIP 2 window.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Select_PIP1_Parameter(void)
{
    /*
    0: To configure PIP 1��s parameters.
    1: To configure PIP 2��s parameters..
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Select_PIP2_Parameter(void)
{
    /*
    0: To configure PIP 1��s parameters.
    1: To configure PIP 2��s parameters..
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Select_Main_Window_8bpp(void)
{
    /*
    Main Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Select_Main_Window_16bpp(void)
{
    /*
    Main Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Select_Main_Window_24bpp(void)
{
    /*
    Main Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp |= cSetD3;
    // temp |= cSetD2;
    LCD_DataWrite(temp);
}
//[11h]=========================================================================
void Select_PIP2_Window_8bpp(void)
{
    /*
    PIP 1 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Select_PIP2_Window_16bpp(void)
{
    /*
    PIP 1 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Select_PIP2_Window_24bpp(void)
{
    /*
    PIP 1 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Select_PIP1_Window_8bpp(void)
{
    /*
    PIP 2 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Select_PIP1_Window_16bpp(void)
{
    /*
    PIP 2 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Select_PIP1_Window_24bpp(void)
{
    /*
    PIP 2 Window Color Depth Setting
    00b: 8-bpp generic TFT, i.e. 256 colors.
    01b: 16-bpp generic TFT, i.e. 65K colors.
    1xb: 24-bpp generic TFT, i.e. 1.67M colors.
    */
    unsigned char temp;
    LCD_CmdWrite(0x11);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}

//[12h]=========================================================================
void PCLK_Rising(void)
{
    /*
    PCLK Inversion
    0: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK falling edge.
    1: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK rising edge.
    */
    unsigned char temp;
    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void PCLK_Falling(void)
{
    /*
    PCLK Inversion
    0: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK falling edge.
    1: PDAT, DE, HSYNC etc. Drive(/ change) at PCLK rising edge.
    */
    unsigned char temp;
    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Display_ON(void)
{
    /*
    Display ON/OFF
    0b: Display Off.
    1b: Display On.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}

void Display_OFF(void)
{
    /*
    Display ON/OFF
    0b: Display Off.
    1b: Display On.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Color_Bar_ON(void)
{
    /*
    Display Test Color Bar
    0b: Disable.
    1b: Enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Color_Bar_OFF(void)
{
    /*
    Display Test Color Bar
    0b: Disable.
    1b: Enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void HSCAN_L_to_R(void)
{
    /*
    Horizontal Scan Direction
    0 : From Left to Right
    1 : From Right to Left
    PIP window will be disabled when HDIR set as 1.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void HSCAN_R_to_L(void)
{
    /*
    Horizontal Scan Direction
    0 : From Left to Right
    1 : From Right to Left
    PIP window will be disabled when HDIR set as 1.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void VSCAN_T_to_B(void)
{
    /*
    Vertical Scan direction
    0 : From Top to Bottom
    1 : From bottom to Top
    PIP window will be disabled when VDIR set as 1.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void VSCAN_B_to_T(void)
{
    /*
    Vertical Scan direction
    0 : From Top to Bottom
    1 : From bottom to Top
    PIP window will be disabled when VDIR set as 1.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void PDATA_Set_RGB(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    LCD_DataWrite(temp);
}
void PDATA_Set_RBG(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void PDATA_Set_GRB(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void PDATA_Set_GBR(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void PDATA_Set_BRG(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void PDATA_Set_BGR(void)
{
    /*
    parallel PDATA[23:0] Output Sequence
    000b : RGB.
    001b : RBG.
    010b : GRB.
    011b : GBR.
    100b : BRG.
    101b : BGR.
    */
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp &= 0xf8;
    temp |= cSetD2;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

void PDATA_IDLE_STATE(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x12);
    temp = LCD_DataRead();
    temp |= 0x07;
    LCD_DataWrite(temp);
}

//[13h]=========================================================================
void HSYNC_Low_Active(void)
{
    /*
    HSYNC Polarity
    0 : Low active.
    1 : High active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void HSYNC_High_Active(void)
{
    /*
    HSYNC Polarity
    0 : Low active.
    1 : High active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void VSYNC_Low_Active(void)
{
    /*
    VSYNC Polarity
    0 : Low active.
    1 : High active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void VSYNC_High_Active(void)
{
    /*
    VSYNC Polarity
    0 : Low active.
    1 : High active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void DE_Low_Active(void)
{
    /*
    DE Polarity
    0 : High active.
    1 : Low active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void DE_High_Active(void)
{
    /*
    DE Polarity
    0 : High active.
    1 : Low active.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Idle_DE_Low(void)
{
    /*
    DE IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��DE�� output is low.
    1 : Pin ��DE�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Idle_DE_High(void)
{
    /*
    DE IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��DE�� output is low.
    1 : Pin ��DE�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Idle_PCLK_Low(void)
{
    /*
    PCLK IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��PCLK�� output is low.
    1 : Pin ��PCLK�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Idle_PCLK_High(void)
{
    /*
    PCLK IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��PCLK�� output is low.
    1 : Pin ��PCLK�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Idle_PDAT_Low(void)
{
    /*
    PDAT IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pins ��PDAT[23:0]�� output is low.
    1 : Pins ��PCLK[23:0]�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Idle_PDAT_High(void)
{
    /*
    PDAT IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pins ��PDAT[23:0]�� output is low.
    1 : Pins ��PCLK[23:0]�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Idle_HSYNC_Low(void)
{
    /*
    HSYNC IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��HSYNC�� output is low.
    1 : Pin ��HSYNC�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Idle_HSYNC_High(void)
{
    /*
    HSYNC IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��HSYNC�� output is low.
    1 : Pin ��HSYNC�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Idle_VSYNC_Low(void)
{
    /*
    VSYNC IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��VSYNC�� output is low.
    1 : Pin ��VSYNC�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Idle_VSYNC_High(void)
{
    /*
    VSYNC IDLE STATE(When STANDBY or DISPLAY OFF )
    0 : Pin ��VSYNC�� output is low.
    1 : Pin ��VSYNC�� output is high.
    */
    unsigned char temp;

    LCD_CmdWrite(0x13);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[14h][15h][1Ah][1Bh]=========================================================================
void LCD_HorizontalWidth_VerticalHeight(unsigned short WX, unsigned short HY)
{
    /*
    [14h] Horizontal Display Width Setting Bit[7:0]
    [15h] Horizontal Display Width Fine Tuning (HDWFT) [3:0]
    The register specifies the LCD panel horizontal display width in
    the unit of 8 pixels resolution.
    Horizontal display width(pixels) = (HDWR + 1) * 8 + HDWFTR

    [1Ah] Vertical Display Height Bit[7:0]
    Vertical Display Height(Line) = VDHR + 1
    [1Bh] Vertical Display Height Bit[10:8]
    Vertical Display Height(Line) = VDHR + 1
    */
    unsigned char temp;
    if (WX < 8)
    {
        LCD_CmdWrite(0x14);
        LCD_DataWrite(0x00);

        LCD_CmdWrite(0x15);
        LCD_DataWrite(WX);

        temp = HY - 1;
        LCD_CmdWrite(0x1A);
        LCD_DataWrite(temp);

        temp = (HY - 1) >> 8;
        LCD_CmdWrite(0x1B);
        LCD_DataWrite(temp);
    }
    else
    {
        temp = (WX / 8) - 1;
        LCD_CmdWrite(0x14);
        LCD_DataWrite(temp);

        temp = WX % 8;
        LCD_CmdWrite(0x15);
        LCD_DataWrite(temp);

        temp = HY - 1;
        LCD_CmdWrite(0x1A);
        LCD_DataWrite(temp);

        temp = (HY - 1) >> 8;
        LCD_CmdWrite(0x1B);
        LCD_DataWrite(temp);
    }
}
//[16h][17h]=========================================================================
void LCD_Horizontal_Non_Display(unsigned short WX)
{
    /*
    [16h] Horizontal Non-Display Period(HNDR) Bit[4:0]
    This register specifies the horizontal non-display period. Also
    called back porch.
    Horizontal non-display period(pixels) = (HNDR + 1) * 8 + HNDFTR

    [17h] Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]
    This register specifies the fine tuning for horizontal non-display
    period; it is used to support the SYNC mode panel. Each level of
    this modulation is 1-pixel.
    Horizontal non-display period(pixels) = (HNDR + 1) * 8 + HNDFTR
    */
    unsigned char temp;
    if (WX < 8)
    {
        LCD_CmdWrite(0x16);
        LCD_DataWrite(0x00);

        LCD_CmdWrite(0x17);
        LCD_DataWrite(WX);
    }
    else
    {
        temp = (WX / 8) - 1;
        LCD_CmdWrite(0x16);
        LCD_DataWrite(temp);

        temp = WX % 8;
        LCD_CmdWrite(0x17);
        LCD_DataWrite(temp);
    }
}

//[18h]=========================================================================
void LCD_HSYNC_Start_Position(unsigned short WX)
{
    /*
    [18h] HSYNC Start Position[4:0]
    The starting position from the end of display area to the
    beginning of HSYNC. Each level of this modulation is 8-pixel.
    Also called front porch.
    HSYNC Start Position(pixels) = (HSTR + 1)x8
    */
    unsigned char temp;
    if (WX < 8)
    {
        LCD_CmdWrite(0x18);
        LCD_DataWrite(0x00);
    }
    else
    {
        temp = (WX / 8) - 1;
        LCD_CmdWrite(0x18);
        LCD_DataWrite(temp);
    }
}
//[19h]=========================================================================
void LCD_HSYNC_Pulse_Width(unsigned short WX)
{
    /*
    [19h] HSYNC Pulse Width(HPW) [4:0]
    The period width of HSYNC.
    HSYNC Pulse Width(pixels) = (HPW + 1)x8
    */
    unsigned char temp;
    if (WX < 8)
    {
        LCD_CmdWrite(0x19);
        LCD_DataWrite(0x00);
    }
    else
    {
        temp = (WX / 8) - 1;
        LCD_CmdWrite(0x19);
        LCD_DataWrite(temp);
    }
}
//[1Ch][1Dh]=========================================================================
void LCD_Vertical_Non_Display(unsigned short HY)
{
    /*
    [1Ch] Vertical Non-Display Period Bit[7:0]
    Vertical Non-Display Period(Line) = (VNDR + 1)

    [1Dh] Vertical Non-Display Period Bit[9:8]
    Vertical Non-Display Period(Line) = (VNDR + 1)
    */
    unsigned char temp;
    temp = HY - 1;
    LCD_CmdWrite(0x1C);
    LCD_DataWrite(temp);

    LCD_CmdWrite(0x1D);
    LCD_DataWrite(temp >> 8);
}
//[1Eh]=========================================================================
void LCD_VSYNC_Start_Position(unsigned short HY)
{
    /*
    [1Eh] VSYNC Start Position[7:0]
    The starting position from the end of display area to the beginning of VSYNC.
    VSYNC Start Position(Line) = (VSTR + 1)
    */
    unsigned char temp;
    temp = HY - 1;
    LCD_CmdWrite(0x1E);
    LCD_DataWrite(temp);
}
//[1Fh]=========================================================================
void LCD_VSYNC_Pulse_Width(unsigned short HY)
{
    /*
    [1Fh] VSYNC Pulse Width[5:0]
    The pulse width of VSYNC in lines.
    VSYNC Pulse Width(Line) = (VPWR + 1)
    */
    unsigned char temp;
    temp = HY - 1;
    LCD_CmdWrite(0x1F);
    LCD_DataWrite(temp);
}
//[20h][21h][22h][23h]=========================================================================
void Main_Image_Start_Address(unsigned long Addr)
{
    /*
    [20h] Main Image Start Address[7:2]
    [21h] Main Image Start Address[15:8]
    [22h] Main Image Start Address [23:16]
    [23h] Main Image Start Address [31:24]
    */
    Write_Dir(0x20, Addr);
    Write_Dir(0x21, Addr >> 8);
    Write_Dir(0x22, Addr >> 16);
    Write_Dir(0x23, Addr >> 24);
}
//[24h][25h]=========================================================================
void Main_Image_Width(unsigned short WX)
{
    /*
    [24h] Main Image Width [7:0]
    [25h] Main Image Width [12:8]
    Unit: Pixel.
    It must be divisible by 4. MIW Bit [1:0] tie to ��0�� internally.
    The value is physical pixel number. Maximum value is 8188 pixels
    */
    Write_Dir(0x24, WX);
    Write_Dir(0x25, WX >> 8);
}
//[26h][27h][28h][29h]=========================================================================
void Main_Window_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [26h] Main Window Upper-Left corner X-coordination [7:0]
    [27h] Main Window Upper-Left corner X-coordination [12:8]
    Reference Main Image coordination.
    Unit: Pixel
    It must be divisible by 4. MWULX Bit [1:0] tie to ��0�� internally.
    X-axis coordination plus Horizontal display width cannot large than 8188.

    [28h] Main Window Upper-Left corner Y-coordination [7:0]
    [29h] Main Window Upper-Left corner Y-coordination [12:8]
    Reference Main Image coordination.
    Unit: Pixel
    Range is between 0 and 8191.
    */
    Write_Dir(0x26, WX);
    Write_Dir(0x27, WX >> 8);

    Write_Dir(0x28, HY);
    Write_Dir(0x29, HY >> 8);
}
//[2Ah][2Bh][2Ch][2Dh]=========================================================================
void PIP_Display_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [2Ah] PIP Window Display Upper-Left corner X-coordination [7:0]
    [2Bh] PIP Window Display Upper-Left corner X-coordination [12:8]
    Reference Main Window coordination.
    Unit: Pixel
    It must be divisible by 4. PWDULX Bit [1:0] tie to ��0�� internally.
    X-axis coordination should less than horizontal display width.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.

    [2Ch] PIP Window Display Upper-Left corner Y-coordination [7:0]
    [2Dh] PIP Window Display Upper-Left corner Y-coordination [12:8]
    Reference Main Window coordination.
    Unit: Pixel
    Y-axis coordination should less than vertical display height.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.
    */
    Write_Dir(0x2A, WX);
    Write_Dir(0x2B, WX >> 8);

    Write_Dir(0x2C, HY);
    Write_Dir(0x2D, HY >> 8);
}
//[2Eh][2Fh][30h][31h]=========================================================================
void PIP_Image_Start_Address(unsigned long Addr)
{
    /*
    [2Eh] PIP Image Start Address[7:2]
    [2Fh] PIP Image Start Address[15:8]
    [30h] PIP Image Start Address [23:16]
    [31h] PIP Image Start Address [31:24]
    */
    Write_Dir(0x2E, Addr);
    Write_Dir(0x2F, Addr >> 8);
    Write_Dir(0x30, Addr >> 16);
    Write_Dir(0x31, Addr >> 24);
}
//[32h][33h]=========================================================================
void PIP_Image_Width(unsigned short WX)
{
    /*
    [32h] PIP Image Width [7:0]
    [33h] PIP Image Width [12:8]
    Unit: Pixel.
    It must be divisible by 4. PIW Bit [1:0] tie to ��0�� internally.
    The value is physical pixel number.
    This width should less than horizontal display width.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.
    */
    Write_Dir(0x32, WX);
    Write_Dir(0x33, WX >> 8);
}
//[34h][35h][36h][37h]=========================================================================
void PIP_Window_Image_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [34h] PIP 1 or 2 Window Image Upper-Left corner X-coordination [7:0]
    [35h] PIP Window Image Upper-Left corner X-coordination [12:8]
    Reference PIP Image coordination.
    Unit: Pixel
    It must be divisible by 4. PWIULX Bit [1:0] tie to ��0�� internally.
    X-axis coordination plus PIP image width cannot large than 8188.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.

    [36h] PIP Windows Display Upper-Left corner Y-coordination [7:0]
    [37h] PIP Windows Image Upper-Left corner Y-coordination [12:8]
    Reference PIP Image coordination.
    Unit: Pixel
    Y-axis coordination plus PIP window height should less than 8191.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.
    */
    Write_Dir(0x34, WX);
    Write_Dir(0x35, WX >> 8);

    Write_Dir(0x36, HY);
    Write_Dir(0x37, HY >> 8);
}
//[38h][39h][3Ah][3Bh]=========================================================================
void PIP_Window_Width_Height(unsigned short WX, unsigned short HY)
{
    /*
    [38h] PIP Window Width [7:0]
    [39h] PIP Window Width [10:8]
    Unit: Pixel.
    It must be divisible by 4. The value is physical pixel number.
    Maximum value is 8188 pixels.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.

    [3Ah] PIP Window Height [7:0]
    [3Bh] PIP Window Height [10:8]
    Unit: Pixel
    The value is physical pixel number. Maximum value is 8191 pixels.
    According to bit of Select Configure PIP 1 or 2 Window��s parameters.
    Function bit will be configured for relative PIP window.
    */
    Write_Dir(0x38, WX);
    Write_Dir(0x39, WX >> 8);

    Write_Dir(0x3A, HY);
    Write_Dir(0x3B, HY >> 8);
}

//[3Ch]=========================================================================
void Enable_Graphic_Cursor(void)
{
    /*
    Graphic Cursor Enable
    0 : Graphic Cursor disable.
    1 : Graphic Cursor enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Disable_Graphic_Cursor(void)
{
    /*
    Graphic Cursor Enable
    0 : Graphic Cursor disable.
    1 : Graphic Cursor enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
//
void Select_Graphic_Cursor_1(void)
{
    /*
    Graphic Cursor Selection Bit
    Select one from four graphic cursor types. (00b to 11b)
    00b : Graphic Cursor Set 1.
    01b : Graphic Cursor Set 2.
    10b : Graphic Cursor Set 3.
    11b : Graphic Cursor Set 4.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Select_Graphic_Cursor_2(void)
{
    /*
    Graphic Cursor Selection Bit
    Select one from four graphic cursor types. (00b to 11b)
    00b : Graphic Cursor Set 1.
    01b : Graphic Cursor Set 2.
    10b : Graphic Cursor Set 3.
    11b : Graphic Cursor Set 4.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Select_Graphic_Cursor_3(void)
{
    /*
    Graphic Cursor Selection Bit
    Select one from four graphic cursor types. (00b to 11b)
    00b : Graphic Cursor Set 1.
    01b : Graphic Cursor Set 2.
    10b : Graphic Cursor Set 3.
    11b : Graphic Cursor Set 4.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Select_Graphic_Cursor_4(void)
{
    /*
    Graphic Cursor Selection Bit
    Select one from four graphic cursor types. (00b to 11b)
    00b : Graphic Cursor Set 1.
    01b : Graphic Cursor Set 2.
    10b : Graphic Cursor Set 3.
    11b : Graphic Cursor Set 4.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
//
void Enable_Text_Cursor(void)
{
    /*
    Text Cursor Enable
    0 : Disable.
    1 : Enable.
    Text cursor & Graphic cursor cannot enable simultaneously.
    Graphic cursor has higher priority then Text cursor if enabled simultaneously.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Disable_Text_Cursor(void)
{
    /*
    Text Cursor Enable
    0 : Disable.
    1 : Enable.
    Text cursor & Graphic cursor cannot enable simultaneously.
    Graphic cursor has higher priority then Text cursor if enabled simultaneously.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
//
void Enable_Text_Cursor_Blinking(void)
{
    /*
    Text Cursor Blinking Enable
    0 : Disable.
    1 : Enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Disable_Text_Cursor_Blinking(void)
{
    /*
    Text Cursor Blinking Enable
    0 : Disable.
    1 : Enable.
    */
    unsigned char temp;

    LCD_CmdWrite(0x3C);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
//[3Dh]=========================================================================
void Blinking_Time_Frames(unsigned char temp)
{
    /*
    Text Cursor Blink Time Setting (Unit: Frame)
    00h : 1 frame time.
    01h : 2 frames time.
    02h : 3 frames time.
    :
    FFh : 256 frames time.
    */
    LCD_CmdWrite(0x3D);
    LCD_DataWrite(temp);
}
//[3Eh]=========================================================================
void Text_Cursor_H_V(unsigned short WX, unsigned short HY)
{
    /*
    [3Eh]
    Text Cursor Horizontal Size Setting[4:0]
    Unit : Pixel
    Zero-based number. Value ��0�� means 1 pixel.
    Note : When font is enlarged, the cursor setting will multiply the
    same times as the font enlargement.
    [3Fh]
    Text Cursor Vertical Size Setting[4:0]
    Unit : Pixel
    Zero-based number. Value ��0�� means 1 pixel.
    Note : When font is enlarged, the cursor setting will multiply the
    same times as the font enlargement.
    */
    LCD_CmdWrite(0x3E);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0x3F);
    LCD_DataWrite(HY);
}
//[40h][41h][42h][43h]=========================================================================
void Graphic_Cursor_XY(unsigned short WX, unsigned short HY)
{
    /*
    [40h] Graphic Cursor Horizontal Location[7:0]
    [41h] Graphic Cursor Horizontal Location[12:8]
    [42h] Graphic Cursor Vertical Location[7:0]
    [43h] Graphic Cursor Vertical Location[12:8]
    Reference main Window coordination.
    */
    Write_Dir(0x40, WX);
    Write_Dir(0x41, WX >> 8);

    Write_Dir(0x42, HY);
    Write_Dir(0x43, HY >> 8);
}
//[44h]=========================================================================
void Set_Graphic_Cursor_Color_1(unsigned char temp)
{
    /*
    [44h] Graphic Cursor Color 0 with 256 Colors
    RGB Format [7:0] = RRRGGGBB.
    */
    Write_Dir(0x44, temp);
}
//[45h]=========================================================================
void Set_Graphic_Cursor_Color_2(unsigned char temp)
{
    /*
    [45h] Graphic Cursor Color 1 with 256 Colors
    RGB Format [7:0] = RRRGGGBB.
    */
    Write_Dir(0x45, temp);
}
//[50h][51h][52h][53h]=========================================================================
void Canvas_Image_Start_address(unsigned long Addr)
{
    /*
    [50h] Start address of Canvas [7:0]
    [51h] Start address of Canvas [15:8]
    [52h] Start address of Canvas [23:16]
    [53h] Start address of Canvas [31:24]
    */
    Write_Dir(0x50, Addr);
    Write_Dir(0x51, Addr >> 8);
    Write_Dir(0x52, Addr >> 16);
    Write_Dir(0x53, Addr >> 24);
}
//[54h][55h]=========================================================================
void Canvas_image_width(unsigned short WX)
{
    /*
    [54h] Canvas image width [7:2]
    [55h] Canvas image width [12:8]
    */
    Write_Dir(0x54, WX);
    Write_Dir(0x55, WX >> 8);
}
//[56h][57h][58h][59h]=========================================================================
void Active_Window_XY(unsigned short WX, unsigned short HY)
{
    /*
    [56h] Active Window Upper-Left corner X-coordination [7:0]
    [57h] Active Window Upper-Left corner X-coordination [12:8]
    [58h] Active Window Upper-Left corner Y-coordination [7:0]
    [59h] Active Window Upper-Left corner Y-coordination [12:8]
    */
    Write_Dir(0x56, WX);
    Write_Dir(0x57, WX >> 8);

    Write_Dir(0x58, HY);
    Write_Dir(0x59, HY >> 8);
}
//[5Ah][5Bh][5Ch][5Dh]=========================================================================
void Active_Window_WH(unsigned short WX, unsigned short HY)
{
    /*
    [5Ah] Width of Active Window [7:0]
    [5Bh] Width of Active Window [12:8]
    [5Ch] Height of Active Window [7:0]
    [5Dh] Height of Active Window [12:8]
    */
    Write_Dir(0x5A, WX);
    Write_Dir(0x5B, WX >> 8);

    Write_Dir(0x5C, HY);
    Write_Dir(0x5D, HY >> 8);
}
//[5Eh]=========================================================================
void Select_Write_Data_Position(void)
{
    /*
    Select to read back Graphic Read/Write position
    0: read back Graphic Write position
    1: read back Graphic Read position
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Select_Read_Data_Position(void)
{
    /*
    Select to read back Graphic Read/Write position
    0: read back Graphic Write position
    1: read back Graphic Read position
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Memory_XY_Mode(void)
{
    /*
    Canvas addressing mode
    0: Block mode (X-Y coordination addressing)
    1: linear mode
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Memory_Linear_Mode(void)
{
    /*
    Canvas addressing mode
    0: Block mode (X-Y coordination addressing)
    1: linear mode
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Memory_8bpp_Mode(void)
{
    /*
    Canvas image��s color depth & memory R/W data width
    In Block Mode:
    00: 8bpp
    01: 16bpp
    1x: 24bpp
    In Linear Mode:
    X0: 8-bits memory data read/write.
    X1: 16-bits memory data read/write
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Memory_16bpp_Mode(void)
{
    /*
    Canvas image��s color depth & memory R/W data width
    In Block Mode:
    00: 8bpp
    01: 16bpp
    1x: 24bpp
    In Linear Mode:
    X0: 8-bits memory data read/write.
    X1: 16-bits memory data read/write
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Memory_24bpp_Mode(void)
{
    /*
    Canvas image��s color depth & memory R/W data width
    In Block Mode:
    00: 8bpp
    01: 16bpp
    1x: 24bpp
    In Linear Mode:
    X0: 8-bits memory data read/write.
    X1: 16-bits memory data read/write
    */
    unsigned char temp;

    LCD_CmdWrite(0x5E);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[5Fh][60h][61h][62h]=========================================================================
void Goto_Pixel_XY(unsigned short WX, unsigned short HY)
{
    /*
    [Write]: Set Graphic Read/Write position
    [Read]: Current Graphic Read/Write position
    Read back is Read position or Write position depends on
    REG[5Eh] bit3, Select to read back Graphic Read/Write position.
    When DPRAM Linear mode:Graphic Read/Write Position [31:24][23:16][15:8][7:0]
    When DPRAM Active window mode:Graphic Read/Write
    Horizontal Position [12:8][7:0],
    Vertical Position [12:8][7:0].
    Reference Canvas image coordination. Unit: Pixel
    */
    Write_Dir(0x5F, WX);
    Write_Dir(0x60, WX >> 8);

    Write_Dir(0x61, HY);
    Write_Dir(0x62, HY >> 8);
}
void Goto_Linear_Addr(unsigned long Addr)
{
    Write_Dir(0x5F, Addr);
    Write_Dir(0x60, Addr >> 8);
    Write_Dir(0x61, Addr >> 16);
    Write_Dir(0x62, Addr >> 24);
}

//[63h][64h][65h][66h]=========================================================================
void Goto_Text_XY(unsigned short WX, unsigned short HY)
{
    /*
    Write: Set Text Write position
    Read: Current Text Write position
    Text Write X-coordination [12:8][7:0]
    Text Write Y-coordination [12:8][7:0]
    Reference Canvas image coordination.
    Unit: Pixel
    */
    Write_Dir(0x63, WX);
    Write_Dir(0x64, WX >> 8);

    Write_Dir(0x65, HY);
    Write_Dir(0x66, HY >> 8);
}
//[67h]=========================================================================
/*
[bit7]Draw Line / Triangle Start Signal
Write Function
0 : Stop the drawing function.
1 : Start the drawing function.
Read Function
0 : Drawing function complete.
1 : Drawing function is processing.
[bit5]Fill function for Triangle Signal
0 : Non fill.
1 : Fill.
[bit1]Draw Triangle or Line Select Signal
0 : Draw Line
1 : Draw Triangle
*/
void Start_Line(void)
{
    LCD_CmdWrite(0x67);
    LCD_DataWrite(0x80);
    Check_Busy_Draw();
}
void Start_Triangle(void)
{
    LCD_CmdWrite(0x67);
    LCD_DataWrite(0x82); // B1000_0010
    Check_Busy_Draw();
}
void Start_Triangle_Fill(void)
{

    LCD_CmdWrite(0x67);
    LCD_DataWrite(0xA2); // B1010_0010
    Check_Busy_Draw();
}
//[68h][69h][6Ah][6Bh]=========================================================================
// �u�_�I
void Line_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [68h] Draw Line/Square/Triangle Start X-coordination [7:0]
    [69h] Draw Line/Square/Triangle Start X-coordination [12:8]
    [6Ah] Draw Line/Square/Triangle Start Y-coordination [7:0]
    [6Bh] Draw Line/Square/Triangle Start Y-coordination [12:8]
    */
    LCD_CmdWrite(0x68);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x69);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6A);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6B);
    LCD_DataWrite(HY >> 8);
}
//[6Ch][6Dh][6Eh][6Fh]=========================================================================
// �u���I
void Line_End_XY(unsigned short WX, unsigned short HY)
{
    /*
    [6Ch] Draw Line/Square/Triangle End X-coordination [7:0]
    [6Dh] Draw Line/Square/Triangle End X-coordination [12:8]
    [6Eh] Draw Line/Square/Triangle End Y-coordination [7:0]
    [6Fh] Draw Line/Square/Triangle End Y-coordination [12:8]
    */
    LCD_CmdWrite(0x6C);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x6D);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6E);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6F);
    LCD_DataWrite(HY >> 8);
}
//[68h]~[73h]=========================================================================
// ?T��-�I1
void Triangle_Point1_XY(unsigned short WX, unsigned short HY)
{
    /*
    [68h] Draw Line/Square/Triangle Start X-coordination [7:0]
    [69h] Draw Line/Square/Triangle Start X-coordination [12:8]
    [6Ah] Draw Line/Square/Triangle Start Y-coordination [7:0]
    [6Bh] Draw Line/Square/Triangle Start Y-coordination [12:8]
    */
    LCD_CmdWrite(0x68);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x69);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6A);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6B);
    LCD_DataWrite(HY >> 8);
}
// ?T��-�I2
void Triangle_Point2_XY(unsigned short WX, unsigned short HY)
{
    /*
    [6Ch] Draw Line/Square/Triangle End X-coordination [7:0]
    [6Dh] Draw Line/Square/Triangle End X-coordination [12:8]
    [6Eh] Draw Line/Square/Triangle End Y-coordination [7:0]
    [6Fh] Draw Line/Square/Triangle End Y-coordination [12:8]
    */
    LCD_CmdWrite(0x6C);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x6D);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6E);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6F);
    LCD_DataWrite(HY >> 8);
}
// ?T��-�I3
void Triangle_Point3_XY(unsigned short WX, unsigned short HY)
{
    /*
    [70h] Draw Triangle Point 3 X-coordination [7:0]
    [71h] Draw Triangle Point 3 X-coordination [12:8]
    [72h] Draw Triangle Point 3 Y-coordination [7:0]
    [73h] Draw Triangle Point 3 Y-coordination [12:8]
    */
    LCD_CmdWrite(0x70);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x71);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x72);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x73);
    LCD_DataWrite(HY >> 8);
}
// ��_�I
void Square_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [68h] Draw Line/Square/Triangle Start X-coordination [7:0]
    [69h] Draw Line/Square/Triangle Start X-coordination [12:8]
    [6Ah] Draw Line/Square/Triangle Start Y-coordination [7:0]
    [6Bh] Draw Line/Square/Triangle Start Y-coordination [12:8]
    */
    LCD_CmdWrite(0x68);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x69);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6A);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6B);
    LCD_DataWrite(HY >> 8);
}
// ����I
void Square_End_XY(unsigned short WX, unsigned short HY)
{
    /*
    [6Ch] Draw Line/Square/Triangle End X-coordination [7:0]
    [6Dh] Draw Line/Square/Triangle End X-coordination [12:8]
    [6Eh] Draw Line/Square/Triangle End Y-coordination [7:0]
    [6Fh] Draw Line/Square/Triangle End Y-coordination [12:8]
    */
    LCD_CmdWrite(0x6C);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x6D);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x6E);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x6F);
    LCD_DataWrite(HY >> 8);
}
//[76h]=========================================================================
/*
[bit7]
Draw Circle / Ellipse / Square /Circle Square Start Signal
Write Function
0 : Stop the drawing function.
1 : Start the drawing function.
Read Function
0 : Drawing function complete.
1 : Drawing function is processing.
[bit6]
Fill the Circle / Ellipse / Square / Circle Square Signal
0 : Non fill.
1 : fill.
[bit5 bit4]
Draw Circle / Ellipse / Square / Ellipse Curve / Circle Square Select
00 : Draw Circle / Ellipse
01 : Draw Circle / Ellipse Curve
10 : Draw Square.
11 : Draw Circle Square.
[bit1 bit0]
Draw Circle / Ellipse Curve Part Select
00 :
01 :
10 :
11 :
*/
void Start_Circle_or_Ellipse(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0x80); // B1000_XXXX
    Check_Busy_Draw();
}
void Start_Circle_or_Ellipse_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xC0); // B1100_XXXX
    Check_Busy_Draw();
}
//
void Start_Left_Down_Curve(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0x90); // B1001_XX00
    Check_Busy_Draw();
}
void Start_Left_Up_Curve(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0x91); // B1001_XX01
    Check_Busy_Draw();
}
void Start_Right_Up_Curve(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0x92); // B1001_XX10
    Check_Busy_Draw();
}
void Start_Right_Down_Curve(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0x93); // B1001_XX11
    Check_Busy_Draw();
}
//
void Start_Left_Down_Curve_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xD0); // B1101_XX00
    Check_Busy_Draw();
}
void Start_Left_Up_Curve_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xD1); // B1101_XX01
    Check_Busy_Draw();
}
void Start_Right_Up_Curve_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xD2); // B1101_XX10
    Check_Busy_Draw();
}
void Start_Right_Down_Curve_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xD3); // B1101_XX11
    Check_Busy_Draw();
}
//
void Start_Square(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xA0); // B1010_XXXX
    Check_Busy_Draw();
}
void Start_Square_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xE0); // B1110_XXXX
    Check_Busy_Draw();
}
void Start_Circle_Square(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xB0); // B1011_XXXX
    Check_Busy_Draw();
}
void Start_Circle_Square_Fill(void)
{
    LCD_CmdWrite(0x76);
    LCD_DataWrite(0xF0); // B1111_XXXX
    Check_Busy_Draw();
}
//[77h]~[7Eh]=========================================================================
// �ꤤ��
void Circle_Center_XY(unsigned short WX, unsigned short HY)
{
    /*
    [7Bh] Draw Circle/Ellipse/Circle Square Center X-coordination [7:0]
    [7Ch] Draw Circle/Ellipse/Circle Square Center X-coordination [12:8]
    [7Dh] Draw Circle/Ellipse/Circle Square Center Y-coordination [7:0]
    [7Eh] Draw Circle/Ellipse/Circle Square Center Y-coordination [12:8]
    */
    LCD_CmdWrite(0x7B);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x7C);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x7D);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x7E);
    LCD_DataWrite(HY >> 8);
}
// ��ꤤ��?
void Ellipse_Center_XY(unsigned short WX, unsigned short HY)
{
    /*
    [7Bh] Draw Circle/Ellipse/Circle Square Center X-coordination [7:0]
    [7Ch] Draw Circle/Ellipse/Circle Square Center X-coordination [12:8]
    [7Dh] Draw Circle/Ellipse/Circle Square Center Y-coordination [7:0]
    [7Eh] Draw Circle/Ellipse/Circle Square Center Y-coordination [12:8]
    */
    LCD_CmdWrite(0x7B);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x7C);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x7D);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x7E);
    LCD_DataWrite(HY >> 8);
}
// ��?b�|
void Circle_Radius_R(unsigned short WX)
{
    /*
    [77h] Draw Circle/Ellipse/Circle Square Major radius [7:0]
    [78h] Draw Circle/Ellipse/Circle Square Major radius [12:8]
    [79h] Draw Circle/Ellipse/Circle Square Minor radius [7:0]
    [7Ah] Draw Circle/Ellipse/Circle Square Minor radius [12:8]
    */
    LCD_CmdWrite(0x77);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x78);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x79);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x7A);
    LCD_DataWrite(WX >> 8);
}

// ���??b�|
void Ellipse_Radius_RxRy(unsigned short WX, unsigned short HY)
{
    /*
    [77h] Draw Circle/Ellipse/Circle Square Major radius [7:0]
    [78h] Draw Circle/Ellipse/Circle Square Major radius [12:8]
    [79h] Draw Circle/Ellipse/Circle Square Minor radius [7:0]
    [7Ah] Draw Circle/Ellipse/Circle Square Minor radius [12:8]
    */
    LCD_CmdWrite(0x77);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x78);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x79);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x7A);
    LCD_DataWrite(HY >> 8);
}

// ��?��ਤ�b�|
void Circle_Square_Radius_RxRy(unsigned short WX, unsigned short HY)
{
    /*
    [77h] Draw Circle/Ellipse/Circle Square Major radius [7:0]
    [78h] Draw Circle/Ellipse/Circle Square Major radius [12:8]
    [79h] Draw Circle/Ellipse/Circle Square Minor radius [7:0]
    [7Ah] Draw Circle/Ellipse/Circle Square Minor radius [12:8]
    */
    LCD_CmdWrite(0x77);
    LCD_DataWrite(WX);

    LCD_CmdWrite(0x78);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0x79);
    LCD_DataWrite(HY);

    LCD_CmdWrite(0x7A);
    LCD_DataWrite(HY >> 8);
}

//[84h]=========================================================================
void Set_PWM_Prescaler_1_to_256(unsigned short WX)
{
    /*
    PWM Prescaler Register
    These 8 bits determine prescaler value for Timer 0 and 1.
    Time base is ��Core_Freq / (Prescaler + 1)��
    */
    WX = WX - 1;
    LCD_CmdWrite(0x84);
    LCD_DataWrite(WX);
}
//[85h]=========================================================================
void Select_PWM1_Clock_Divided_By_1(void)
{
    /*
    Select MUX input for PWM Timer 1.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Select_PWM1_Clock_Divided_By_2(void)
{
    /*
    Select MUX input for PWM Timer 1.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Select_PWM1_Clock_Divided_By_4(void)
{
    /*
    Select MUX input for PWM Timer 1.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Select_PWM1_Clock_Divided_By_8(void)
{
    /*
    Select MUX input for PWM Timer 1.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Select_PWM0_Clock_Divided_By_1(void)
{
    /*
    Select MUX input for PWM Timer 0.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Select_PWM0_Clock_Divided_By_2(void)
{
    /*
    Select MUX input for PWM Timer 0.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Select_PWM0_Clock_Divided_By_4(void)
{
    /*
    Select MUX input for PWM Timer 0.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Select_PWM0_Clock_Divided_By_8(void)
{
    /*
    Select MUX input for PWM Timer 0.
    00 = 1; 01 = 1/2; 10 = 1/4 ; 11 = 1/8;
    */
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
//[85h].[bit3][bit2]=========================================================================
/*
XPWM[1] pin function control
0X:	XPWM[1] output system error flag (REG[00h] bit[1:0], Scan bandwidth insufficient + Memory access out of range)
10:	XPWM[1] enabled and controlled by PWM timer 1
11:	XPWM[1] output oscillator clock
//If XTEST[0] set high, then XPWM[1] will become panel scan clock input.
*/
void Select_PWM1_is_ErrorFlag(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Select_PWM1(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Select_PWM1_is_Osc_Clock(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
//[85h].[bit1][bit0]=========================================================================
/*
XPWM[0] pin function control
0X: XPWM[0] becomes GPIO-C[7]
10: XPWM[0] enabled and controlled by PWM timer 0
11: XPWM[0] output core clock
*/
void Select_PWM0_is_GPIO_C7(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Select_PWM0(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Select_PWM0_is_Core_Clock(void)
{
    unsigned char temp;

    LCD_CmdWrite(0x85);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
//[86h]=========================================================================
//[86h]PWM1
void Enable_PWM1_Inverter(void)
{
    /*
    PWM Timer 1 output inverter on/off.
    Determine the output inverter on/off for Timer 1.
    0 = Inverter off
    1 = Inverter on for PWM1
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Disable_PWM1_Inverter(void)
{
    /*
    PWM Timer 1 output inverter on/off.
    Determine the output inverter on/off for Timer 1.
    0 = Inverter off
    1 = Inverter on for PWM1
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Auto_Reload_PWM1(void)
{
    /*
    PWM Timer 1 auto reload on/off
    Determine auto reload on/off for Timer 1.
    0 = One-shot
    1 = Interval mode(auto reload)
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void One_Shot_PWM1(void)
{
    /*
    PWM Timer 1 auto reload on/off
    Determine auto reload on/off for Timer 1.
    0 = One-shot
    1 = Interval mode(auto reload)
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Start_PWM1(void)
{
    /*
    PWM Timer 1 start/stop
    Determine start/stop for Timer 1.
    0 = Stop
    1 = Start for Timer 1
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Stop_PWM1(void)
{
    /*
    PWM Timer 1 start/stop
    Determine start/stop for Timer 1.
    0 = Stop
    1 = Start for Timer 1
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
//[86h]PWM0
void Enable_PWM0_Dead_Zone(void)
{
    /*
    PWM Timer 0 Dead zone enable
    Determine the dead zone operation. 0 = Disable. 1 = Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Disable_PWM0_Dead_Zone(void)
{
    /*
    PWM Timer 0 Dead zone enable
    Determine the dead zone operation. 0 = Disable. 1 = Enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD3;
    LCD_DataWrite(temp);
}
void Enable_PWM0_Inverter(void)
{
    /*
    PWM Timer 0 output inverter on/off
    Determine the output inverter on/off for Timer 0.
    0 = Inverter off
    1 = Inverter on for PWM0
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Disable_PWM0_Inverter(void)
{
    /*
    PWM Timer 0 output inverter on/off
    Determine the output inverter on/off for Timer 0.
    0 = Inverter off
    1 = Inverter on for PWM0
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Auto_Reload_PWM0(void)
{
    /*
    PWM Timer 0 auto reload on/off
    Determine auto reload on/off for Timer 0.
    0 = One-shot
    1 = Interval mode(auto reload)
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void One_Shot_PWM0(void)
{
    /*
    PWM Timer 1 auto reload on/off
    Determine auto reload on/off for Timer 1.
    0 = One-shot
    1 = Interval mode(auto reload)
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}
void Start_PWM0(void)
{
    /*
    PWM Timer 0 start/stop
    Determine start/stop for Timer 0.
    0 = Stop
    1 = Start for Timer 0
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Stop_PWM0(void)
{
    /*
    PWM Timer 0 start/stop
    Determine start/stop for Timer 0.
    0 = Stop
    1 = Start for Timer 0
    */
    unsigned char temp;
    LCD_CmdWrite(0x86);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
//[87h]=========================================================================
void Set_Timer0_Dead_Zone_Length(unsigned char temp)
{
    /*
    Timer 0 Dead zone length register
    These 8 bits determine the dead zone length. The 1 unit time of
    the dead zone length is equal to that of timer 0.
    */
    LCD_CmdWrite(0x87);
    LCD_DataWrite(temp);
}
//[88h][89h]=========================================================================
void Set_Timer0_Compare_Buffer(unsigned short WX)
{
    /*
    Timer 0 compare buffer register
    Compare buffer register total has 16 bits.
    When timer counter equal or less than compare buffer register will cause PWM out
    high level if inv_on bit is off.
    */
    LCD_CmdWrite(0x88);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0x89);
    LCD_DataWrite(WX >> 8);
}
//[8Ah][8Bh]=========================================================================
void Set_Timer0_Count_Buffer(unsigned short WX)
{
    /*
    Timer 0 count buffer register
    Count buffer register total has 16 bits.
    When timer counter equal to 0 will cause PWM timer reload Count buffer register if reload_en bit set as enable.
    It may read back timer counter��s real time value when PWM timer start.
    */
    LCD_CmdWrite(0x8A);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0x8B);
    LCD_DataWrite(WX >> 8);
}
//[8Ch][8Dh]=========================================================================
void Set_Timer1_Compare_Buffer(unsigned short WX)
{
    /*
    Timer 0 compare buffer register
    Compare buffer register total has 16 bits.
    When timer counter equal or less than compare buffer register will cause PWM out
    high level if inv_on bit is off.
    */
    LCD_CmdWrite(0x8C);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0x8D);
    LCD_DataWrite(WX >> 8);
}
//[8Eh][8Fh]=========================================================================
void Set_Timer1_Count_Buffer(unsigned short WX)
{
    /*
    Timer 0 count buffer register
    Count buffer register total has 16 bits.
    When timer counter equal to 0 will cause PWM timer reload Count buffer register if reload_en bit set as enable.
    It may read back timer counter��s real time value when PWM timer start.
    */
    LCD_CmdWrite(0x8E);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0x8F);
    LCD_DataWrite(WX >> 8);
}

//[90h]~[B5h]=========================================================================

//[90h]=========================================================================
void BTE_Enable(void)
{
    /*
    BTE Function Enable
    0 : BTE Function disable.
    1 : BTE Function enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x90);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}

//[90h]=========================================================================
void BTE_Disable(void)
{
    /*
    BTE Function Enable
    0 : BTE Function disable.
    1 : BTE Function enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0x90);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}

//[90h]=========================================================================
void Check_BTE_Busy(void)
{
    /*
    BTE Function Status
    0 : BTE Function is idle.
    1 : BTE Function is busy.
    */
    unsigned char temp;
    do
    {
        temp = LCD_StatusRead();
    } while (temp & 0x08);
}
//[90h]=========================================================================
void Pattern_Format_8X8(void)
{
    /*
    Pattern Format
    0 : 8X8
    1 : 16X16
    */
    unsigned char temp;
    LCD_CmdWrite(0x90);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
//[90h]=========================================================================
void Pattern_Format_16X16(void)
{
    /*
    Pattern Format
    0 : 8X8
    1 : 16X16
    */
    unsigned char temp;
    LCD_CmdWrite(0x90);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[91h]=========================================================================
void BTE_ROP_Code(unsigned char setx)
{
    /*
    BTE ROP Code[Bit7:4]

    0000 : 0(Blackness)
    0001 : ~S0.~S1 or ~ ( S0+S1 )
    0010 : ~S0.S1
    0011 : ~S0
    0100 : S0.~S1
    0101 : ~S1
    0110 : S0^S1
    0111 : ~S0+~S1 or ~ ( S0.S1 )
    1000 : S0.S1
    1001 : ~ ( S0^S1 )
    1010 : S1
    1011 : ~S0+S1
    1100 : S0
    1101 : S0+~S1
    1110 : S0+S1
    1111 : 1 ( Whiteness )
    */
    unsigned char temp;
    LCD_CmdWrite(0x91);
    temp = LCD_DataRead();
    temp &= 0x0f;
    temp |= (setx << 4);
    LCD_DataWrite(temp);
}

//[91h]=========================================================================
void BTE_Operation_Code(unsigned char setx)
{
    /*
    BTE Operation Code[Bit3:0]

    0000 : MPU Write BTE with ROP.
    0001 : MPU Read BTE w/o ROP.
    0010 : Memory copy (move) BTE in positive direction with ROP.
    0011 : Memory copy (move) BTE in negative direction with ROP.
    0100 : MPU Transparent Write BTE. (w/o ROP.)
    0101 : Transparent Memory copy (move) BTE in positive direction (w/o ROP.)
    0110 : Pattern Fill with ROP.
    0111 : Pattern Fill with key-chroma
    1000 : Color Expansion
    1001 : Color Expansion with transparency
    1010 : Move BTE in positive direction with Alpha blending
    1011 : MPU Write BTE with Alpha blending
    1100 : Solid Fill
    1101 : Reserved
    1110 : Reserved
    1111 : Reserved
    */
    unsigned char temp;
    LCD_CmdWrite(0x91);
    temp = LCD_DataRead();
    temp &= 0xf0;
    temp |= setx;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S0_Color_8bpp(void)
{
    /*
    S0 Color Depth
    00 : 256 Color
    01 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD6;
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S0_Color_16bpp(void)
{
    /*
    S0 Color Depth
    00 : 256 Color
    01 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD6;
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S0_Color_24bpp(void)
{
    /*
    S0 Color Depth
    00 : 256 Color
    01 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp |= cSetD6;
    // temp |= cSetD5 ;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S1_Color_8bpp(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S1_Color_16bpp(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_S1_Color_24bpp(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp |= cSetD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}

//[92h]=========================================================================
void BTE_S1_Color_Constant(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD4;
    temp |= cSetD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

//[92h]=========================================================================
void BTE_S1_Color_8bit_Alpha(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp |= cSetD4;
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}

//[92h]=========================================================================
void BTE_S1_Color_16bit_Alpha(void)
{
    /*
    S1 Color Depth
    000 : 256 Color
    001 : 64k Color
    010 : 16M Color
    011 : Constant Color
    100 : 8 bit pixel alpha blending
    101 : 16 bit pixel alpha blending
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp |= cSetD4;
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

//[92h]=========================================================================
void BTE_Destination_Color_8bpp(void)
{
    /*
    Destination Color Depth
    00 : 256 Color
    01 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_Destination_Color_16bpp(void)
{
    /*
    Destination Color Depth
    00 : 256 Color
    01 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
//[92h]=========================================================================
void BTE_Destination_Color_24bpp(void)
{
    /*
    Destination Color Depth
    00 : 256 Color
    10 : 64k Color
    1x : 16M Color
    */
    unsigned char temp;
    LCD_CmdWrite(0x92);
    temp = LCD_DataRead();
    temp |= cSetD1;
    // temp |= cSetD0 ;
    LCD_DataWrite(temp);
}

//[93h][94h][95h][96h]=========================================================================
void BTE_S0_Memory_Start_Address(unsigned long Addr)
{
    /*
    [93h] BTE S0 Memory Start Address [7:0]
    [94h] BTE S0 Memory Start Address [15:8]
    [95h] BTE S0 Memory Start Address [23:16]
    [96h] BTE S0 Memory Start Address [31:24]
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0x93, Addr);
    Write_Dir(0x94, Addr >> 8);
    Write_Dir(0x95, Addr >> 16);
    Write_Dir(0x96, Addr >> 24);
}

//[97h][98h]=========================================================================
void BTE_S0_Image_Width(unsigned short WX)
{
    /*
    [97h] BTE S0 Image Width [7:0]
    [98h] BTE S0 Image Width [12:8]
    Unit: Pixel.
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0x97, WX);
    Write_Dir(0x98, WX >> 8);
}

//[99h][9Ah][9Bh][9Ch]=========================================================================
void BTE_S0_Window_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [99h] BTE S0 Window Upper-Left corner X-coordination [7:0]
    [9Ah] BTE S0 Window Upper-Left corner X-coordination [12:8]
    [9Bh] BTE S0 Window Upper-Left corner Y-coordination [7:0]
    [9Ch] BTE S0 Window Upper-Left corner Y-coordination [12:8]
    */
    Write_Dir(0x99, WX);
    Write_Dir(0x9A, WX >> 8);

    Write_Dir(0x9B, HY);
    Write_Dir(0x9C, HY >> 8);
}

//[9Dh][9Eh][9Fh][A0h]=========================================================================
void BTE_S1_Memory_Start_Address(unsigned long Addr)
{
    /*
    [9Dh] BTE S1 Memory Start Address [7:0]
    [9Eh] BTE S1 Memory Start Address [15:8]
    [9Fh] BTE S1 Memory Start Address [23:16]
    [A0h] BTE S1 Memory Start Address [31:24]
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0x9D, Addr);
    Write_Dir(0x9E, Addr >> 8);
    Write_Dir(0x9F, Addr >> 16);
    Write_Dir(0xA0, Addr >> 24);
}

// Input data format:R3G3B2
void S1_Constant_color_256(unsigned char temp)
{
    LCD_CmdWrite(0x9D);
    LCD_DataWrite(temp);

    LCD_CmdWrite(0x9E);
    LCD_DataWrite(temp << 3);

    LCD_CmdWrite(0x9F);
    LCD_DataWrite(temp << 6);
}

// Input data format:R5G6B6
void S1_Constant_color_65k(unsigned short temp)
{
    LCD_CmdWrite(0x9D);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0x9E);
    LCD_DataWrite(temp >> 3);

    LCD_CmdWrite(0x9F);
    LCD_DataWrite(temp << 3);
}

// Input data format:R8G8B8
void S1_Constant_color_16M(unsigned long temp)
{
    LCD_CmdWrite(0x9D);
    LCD_DataWrite(temp >> 16);

    LCD_CmdWrite(0x9E);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0x9F);
    LCD_DataWrite(temp);
}

//[A1h][A2h]=========================================================================
void BTE_S1_Image_Width(unsigned short WX)
{
    /*
    [A1h] BTE S1 Image Width [7:0]
    [A2h] BTE S1 Image Width [12:8]
    Unit: Pixel.
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0xA1, WX);
    Write_Dir(0xA2, WX >> 8);
}

//[A3h][A4h][A5h][A6h]=========================================================================
void BTE_S1_Window_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [A3h] BTE S1 Window Upper-Left corner X-coordination [7:0]
    [A4h] BTE S1 Window Upper-Left corner X-coordination [12:8]
    [A5h] BTE S1 Window Upper-Left corner Y-coordination [7:0]
    [A6h] BTE S1 Window Upper-Left corner Y-coordination [12:8]
    */
    Write_Dir(0xA3, WX);
    Write_Dir(0xA4, WX >> 8);

    Write_Dir(0xA5, HY);
    Write_Dir(0xA6, HY >> 8);
}

//[A7h][A8h][A9h][AAh]=========================================================================
void BTE_Destination_Memory_Start_Address(unsigned long Addr)
{
    /*
    [A7h] BTE Destination Memory Start Address [7:0]
    [A8h] BTE Destination Memory Start Address [15:8]
    [A9h] BTE Destination Memory Start Address [23:16]
    [AAh] BTE Destination Memory Start Address [31:24]
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0xA7, Addr);
    Write_Dir(0xA8, Addr >> 8);
    Write_Dir(0xA9, Addr >> 16);
    Write_Dir(0xAA, Addr >> 24);
}

//[ABh][ACh]=========================================================================
void BTE_Destination_Image_Width(unsigned short WX)
{
    /*
    [ABh] BTE Destination Image Width [7:0]
    [ACh] BTE Destination Image Width [12:8]
    Unit: Pixel.
    Bit [1:0] tie to ��0�� internally.
    */
    Write_Dir(0xAB, WX);
    Write_Dir(0xAC, WX >> 8);
}

//[ADh][AEh][AFh][B0h]=========================================================================
void BTE_Destination_Window_Start_XY(unsigned short WX, unsigned short HY)
{
    /*
    [ADh] BTE Destination Window Upper-Left corner X-coordination [7:0]
    [AEh] BTE Destination Window Upper-Left corner X-coordination [12:8]
    [AFh] BTE Destination Window Upper-Left corner Y-coordination [7:0]
    [B0h] BTE Destination Window Upper-Left corner Y-coordination [12:8]
    */
    Write_Dir(0xAD, WX);
    Write_Dir(0xAE, WX >> 8);

    Write_Dir(0xAF, HY);
    Write_Dir(0xB0, HY >> 8);
}

//[B1h][B2h][B3h][B4h]===============================================================

void BTE_Window_Size(unsigned short WX, unsigned short WY)

{
    /*
    [B1h] BTE Window Width [7:0]
    [B2h] BTE Window Width [12:8]

    [B3h] BTE Window Height [7:0]
    [B4h] BTE Window Height [12:8]
    */
    Write_Dir(0xB1, WX);
    Write_Dir(0xB2, WX >> 8);

    Write_Dir(0xB3, WY);
    Write_Dir(0xB4, WY >> 8);
}

//[B5h]=========================================================================
void BTE_Alpha_Blending_Effect(unsigned char temp)
{
    /*
    Window Alpha Blending effect for S0 & S1
    The value of alpha in the color code ranges from 0.0 to 1.0,
    where 0.0 represents a fully transparent color, and 1.0
    represents a fully opaque color.
    00h: 0
    01h: 1/32
    02h: 2/32
    :
    1Eh: 30/32
    1Fh: 31/32
    2Xh: 1
    Output Effect = (S0 image x (1 - alpha setting value)) + (S1 image x alpha setting value)
    */
    LCD_CmdWrite(0xB5);
    LCD_DataWrite(temp);
}

//[B6h]=========================================================================
void Start_SFI_DMA(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB6);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

void Check_Busy_SFI_DMA(void)
{
    LCD_CmdWrite(0xB6);
    do
    {
    } while ((LCD_DataRead() & 0x01) == 0x01);
}

//[B7h]=========================================================================
void Select_SFI_0(void)
{
    /*[bit7]
    Serial Flash/ROM I/F # Select
    0: Serial Flash/ROM 0 I/F is selected.
    1: Serial Flash/ROM 1 I/F is selected.
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Select_SFI_1(void)
{
    /*[bit7]
    Serial Flash/ROM I/F # Select
    0: Serial Flash/ROM 0 I/F is selected.
    1: Serial Flash/ROM 1 I/F is selected.
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Select_SFI_Font_Mode(void)
{
    /*[bit6]
    Serial Flash /ROM Access Mode
    0: Font mode ?V for external cgrom
    1: DMA mode ?V for cgram , pattern , bootstart image or osd
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Select_SFI_DMA_Mode(void)
{
    /*[bit6]
    Serial Flash /ROM Access Mode
    0: Font mode ?V for external cgrom
    1: DMA mode ?V for cgram , pattern , bootstart image or osd
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Select_SFI_24bit_Address(void)
{
    /*[bit5]
    Serial Flash/ROM Address Mode
    0: 24 bits address mode
    1: 32 bits address mode
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void Select_SFI_32bit_Address(void)
{
    /*[bit5]
    Serial Flash/ROM Address Mode
    0: 24 bits address mode
    1: 32 bits address mode
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void Select_SFI_Waveform_Mode_0(void)
{
    /*[bit4]
    Serial Flash/ROM Waveform Mode
    Mode 0.
    Mode 3.
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Select_SFI_Waveform_Mode_3(void)
{
    /*[bit4]
    Serial Flash/ROM Waveform Mode
    Mode 0.
    Mode 3.
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Select_SFI_0_DummyRead(void)
{
    /*[bit3][bit2]
    Serial Flash /ROM Read Cycle 0 RW
    00b: no dummy cycle mode
    01b: 1 dummy cycle mode
    10b: 2 dummy cycle mode
    11b: 4 dummy cycle mode
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= 0xF3;
    LCD_DataWrite(temp);
}
void Select_SFI_8_DummyRead(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= 0xF3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Select_SFI_16_DummyRead(void)
{

    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= 0xF3;
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
void Select_SFI_24_DummyRead(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= 0x0c;
    LCD_DataWrite(temp);
}
void Select_SFI_Single_Mode(void)
{
    /*[bit1][bit0]
    Serial Flash /ROM I/F Data Latch Mode Select
    0Xb: Single Mode
    10b: Dual Mode 0.
    11b: Dual Mode 1.
    */
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= 0xFC;
    LCD_DataWrite(temp);
}
void Select_SFI_Dual_Mode0(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp &= 0xFC;
    temp |= cSetD1;
    LCD_DataWrite(temp);
}
void Select_SFI_Dual_Mode1(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB7);
    temp = LCD_DataRead();
    temp |= 0x03;
    LCD_DataWrite(temp);
}

// REG[BAh] SPI master Status Register (SPIMSR)
unsigned char Tx_FIFO_Empty_Flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x80) == 0x80)
        return 1;
    else
        return 0;
}
unsigned char Rx_FIFO_Empty_Flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x20) == 0x20)
        return 1;
    else
        return 0;
}

unsigned char SPI_Master_FIFO_Data_Get(void)
{
    unsigned char temp;

    while (Rx_FIFO_Empty_Flag() == 1)
        ; // ���O?Ū����U����
    LCD_CmdWrite(0xB8);
    temp = LCD_DataRead();
    // while(Rx_FIFO_full_flag()); //�s��g?J16����?Ƥ~�ݭn
    return temp;
}

// REG[B8h] SPI master Tx /Rx FIFO Data Register (SPIDR)
unsigned char SPI_Master_FIFO_Data_Put(unsigned char Data)
{
     unsigned char temp;
    LCD_CmdWrite(0xB8);
    LCD_DataWrite(Data);

    // volatile unsigned char test;
    // test=LCD_DataRead();
    // LCD_DataWrite(0X00);
    // test=LCD_DataRead();
    // test=test;
    // test=test;

    while (Tx_FIFO_Empty_Flag() == 0)
        ;
    temp = SPI_Master_FIFO_Data_Get();
    return temp;
}

// REG[B9h] SPI master Control Register (SPIMCR2)
void Mask_SPI_Master_Interrupt_Flag(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}

void Select_nSS_drive_on_xnsfcs0(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp &= cClrD5;
    LCD_DataWrite(temp);
}

void Select_nSS_drive_on_xnsfcs1(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD5;
    LCD_DataWrite(temp);
}

// 1: active (nSS port will goes low)
void nSS_Active(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}

// Interrupt enable for FIFO overflow error [OVFIRQEN]
void OVFIRQEN_Enable(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}
// Interrupt enable for while Tx FIFO empty & SPI engine/FSM idle
void EMTIRQEN_Enable(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

// At CPOL=0 the base value of the clock is zero
// o  For CPHA=0, data are read on the clock's rising edge (low->high transition) and
// data are changed on a falling edge (high->low clock transition).
// o  For CPHA=1, data are read on the clock's falling edge and data are changed on a
// rising edge.

// At CPOL=1 the base value of the clock is one (inversion of CPOL=0)
// o  For CPHA=0, data are read on clock's falling edge and data are changed on a
// rising edge.
// o  For CPHA=1, data are read on clock's rising edge and data are changed on a
// falling edge.

void Reset_CPOL(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp &= cClrD1;
    LCD_DataWrite(temp);
}

void Set_CPOL(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD1;
    LCD_DataWrite(temp);
}

void Reset_CPHA(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}

void Set_CPHA(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xB9);
    temp = LCD_DataRead();
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

unsigned char Tx_FIFO_Full_Flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x40) == 0x40)
        return 1;
    else
        return 0;
}

unsigned char Rx_FIFO_full_flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x10) == 0x10)
        return 1;
    else
        return 0;
}

unsigned char OVFI_Flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x08) == 0x08)
        return 1;
    else
        return 0;
}

void Clear_OVFI_Flag(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xBA);
    temp = LCD_DataRead();
    temp |= cSetD3;
    LCD_DataWrite(temp);
}

unsigned char EMTI_Flag(void)
{
    LCD_CmdWrite(0xBA);
    if ((LCD_DataRead() & 0x04) == 0x04)
        return 1;
    else
        return 0;
}

void Clear_EMTI_Flag(void)
{
    unsigned char temp;
    LCD_CmdWrite(0xBA);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

// REG[BB] SPI Clock period (SPIDIV)
void SPI_Clock_Period(unsigned char temp)
{
    LCD_CmdWrite(0xBB);
    LCD_DataWrite(temp);
}

//[BCh][BDh][BEh][BFh]=========================================================================
void SFI_DMA_Source_Start_Address(unsigned long Addr)
{
    /*
    DMA Source START ADDRESS
    This bits index serial flash address [7:0][15:8][23:16][31:24]
    */
    LCD_CmdWrite(0xBC);
    LCD_DataWrite(Addr);
    LCD_CmdWrite(0xBD);
    LCD_DataWrite(Addr >> 8);
    LCD_CmdWrite(0xBE);
    LCD_DataWrite(Addr >> 16);
    LCD_CmdWrite(0xBF);
    LCD_DataWrite(Addr >> 24);
}
//[C0h][C1h][C2h][C3h]=========================================================================
void SFI_DMA_Destination_Start_Address(unsigned long Addr)
{
    /*
    DMA Destination START ADDRESS
    [1:0]Fix at 0
    This bits index SDRAM address [7:0][15:8][23:16][31:24]
    */
    LCD_CmdWrite(0xC0);
    LCD_DataWrite(Addr);
    LCD_CmdWrite(0xC1);
    LCD_DataWrite(Addr >> 8);
    LCD_CmdWrite(0xC2);
    LCD_DataWrite(Addr >> 16);
    LCD_CmdWrite(0xC3);
    LCD_DataWrite(Addr >> 24);
}
//[C0h][C1h][C2h][C3h]=========================================================================
void SFI_DMA_Destination_Upper_Left_Corner(unsigned short WX, unsigned short HY)
{
    /*
    C0h
    This register defines DMA Destination Window Upper-Left corner
    X-coordination [7:0] on Canvas area.
    When REG DMACR bit 1 = 1 (Block Mode)
    This register defines Destination address [7:2] in SDRAM.
    C1h
    When REG DMACR bit 1 = 0 (Linear Mode)
    This register defines DMA Destination Window Upper-Left corner
    X-coordination [12:8] on Canvas area.
    When REG DMACR bit 1 = 1 (Block Mode)
    This register defines Destination address [15:8] in SDRAM.
    C2h
    When REG DMACR bit 1 = 0 (Linear Mode)
    This register defines DMA Destination Window Upper-Left corner
    Y-coordination [7:0] on Canvas area.
    When REG DMACR bit 1 = 1 (Block Mode)
    This register defines Destination address [23:16] in SDRAM.
    C3h
    When REG DMACR bit 1 = 0 (Linear Mode)
    This register defines DMA Destination Window Upper-Left corner
    Y-coordination [12:8] on Canvas area.
    When REG DMACR bit 1 = 1 (Block Mode)
    This register defines Destination address [31:24] in SDRAM.
    */

    LCD_CmdWrite(0xC0);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0xC1);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0xC2);
    LCD_DataWrite(HY);
    LCD_CmdWrite(0xC3);
    LCD_DataWrite(HY >> 8);
}

//[C6h][C7h][C8h][C9h]=========================================================================
void SFI_DMA_Transfer_Number(unsigned long Addr)
{
    /*
    Unit : Pixel
    When REG DMACR bit 1 = 0 (Linear Mode)
    DMA Transfer Number [7:0][15:8][23:16][31:24]

    When REG DMACR bit 1 = 1 (Block Mode)
    DMA Block Width [7:0][15:8]
    DMA Block HIGH[7:0][15:8]
    */
    LCD_CmdWrite(0xC6);
    LCD_DataWrite(Addr);
    LCD_CmdWrite(0xC7);
    LCD_DataWrite(Addr >> 8);
    LCD_CmdWrite(0xC8);
    LCD_DataWrite(Addr >> 16);
    LCD_CmdWrite(0xC9);
    LCD_DataWrite(Addr >> 24);
}
void SFI_DMA_Transfer_Width_Height(unsigned short WX, unsigned short HY)
{
    /*
    When REG DMACR bit 1 = 0 (Linear Mode)
    DMA Transfer Number [7:0][15:8][23:16][31:24]

    When REG DMACR bit 1 = 1 (Block Mode)
    DMA Block Width [7:0][15:8]
    DMA Block HIGH[7:0][15:8]
    */
    LCD_CmdWrite(0xC6);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0xC7);
    LCD_DataWrite(WX >> 8);

    LCD_CmdWrite(0xC8);
    LCD_DataWrite(HY);
    LCD_CmdWrite(0xC9);
    LCD_DataWrite(HY >> 8);
}
//[CAh][CBh]=========================================================================
void SFI_DMA_Source_Width(unsigned short WX)
{
    /*
    DMA Source Picture Width [7:0][12:8]
    Unit: pixel
    */
    LCD_CmdWrite(0xCA);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0xCB);
    LCD_DataWrite(WX >> 8);
}

//[CCh]=========================================================================

void Font_Select_UserDefine_Mode(void)
{
    /*[bit7-6]
    User-defined Font /CGROM Font Selection Bit in Text Mode
    00 : Internal CGROM
    01 : Genitop serial flash
    10 : User-defined Font
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void CGROM_Select_Internal_CGROM(void)
{
    /*[bit7-6]
    User-defined Font /CGROM Font Selection Bit in Text Mode
    00 : Internal CGROM
    01 : Genitop serial flash
    10 : User-defined Font
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void CGROM_Select_Genitop_FontROM(void)
{
    /*[bit7-6]
    User-defined Font /CGROM Font Selection Bit in Text Mode
    00 : Internal CGROM
    01 : Genitop serial flash
    10 : User-defined Font
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Font_Select_8x16_16x16(void)
{
    /*[bit5-4]
    Font Height Setting
    00b : 8x16 / 16x16.
    01b : 12x24 / 24x24.
    10b : 16x32 / 32x32.
    *** User-defined Font width is decided by font code. Genitop
    serial flash��s font width is decided by font code or GT Font ROM
    control register.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Font_Select_12x24_24x24(void)
{
    /*[bit5-4]
    Font Height Setting
    00b : 8x16 / 16x16.
    01b : 12x24 / 24x24.
    10b : 16x32 / 32x32.
    *** User-defined Font width is decided by font code. Genitop
    serial flash��s font width is decided by font code or GT Font ROM
    control register.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD5;
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Font_Select_16x32_32x32(void)
{
    /*[bit5-4]
    Font Height Setting
    00b : 8x16 / 16x16.
    01b : 12x24 / 24x24.
    10b : 16x32 / 32x32.
    *** User-defined Font width is decided by font code. Genitop
    serial flash��s font width is decided by font code or GT Font ROM
    control register.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp |= cSetD5;
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Internal_CGROM_Select_ISOIEC8859_1(void)
{
    /*
    Font Selection for internal CGROM
    When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
    8x16 character sets with the standard coding of ISO/IEC 8859-1~4,
    which supports English and most of European country languages.
    00b : ISO/IEC 8859-1.
    01b : ISO/IEC 8859-2.
    10b : ISO/IEC 8859-3.
    11b : ISO/IEC 8859-4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Internal_CGROM_Select_ISOIEC8859_2(void)
{
    /*
    Font Selection for internal CGROM
    When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
    8x16 character sets with the standard coding of ISO/IEC 8859-1~4,
    which supports English and most of European country languages.
    00b : ISO/IEC 8859-1.
    01b : ISO/IEC 8859-2.
    10b : ISO/IEC 8859-3.
    11b : ISO/IEC 8859-4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Internal_CGROM_Select_ISOIEC8859_3(void)
{
    /*
    Font Selection for internal CGROM
    When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
    8x16 character sets with the standard coding of ISO/IEC 8859-1~4,
    which supports English and most of European country languages.
    00b : ISO/IEC 8859-1.
    01b : ISO/IEC 8859-2.
    10b : ISO/IEC 8859-3.
    11b : ISO/IEC 8859-4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Internal_CGROM_Select_ISOIEC8859_4(void)
{
    /*
    Font Selection for internal CGROM
    When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
    8x16 character sets with the standard coding of ISO/IEC 8859-1~4,
    which supports English and most of European country languages.
    00b : ISO/IEC 8859-1.
    01b : ISO/IEC 8859-2.
    10b : ISO/IEC 8859-3.
    11b : ISO/IEC 8859-4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCC);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
//[CDh]=========================================================================
void Enable_Font_Alignment(void)
{
    /*
    Full Alignment Selection Bit
    0 : Full alignment disable.
    1 : Full alignment enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD7;
    LCD_DataWrite(temp);
}
void Disable_Font_Alignment(void)
{
    /*
    Full Alignment Selection Bit
    0 : Full alignment disable.
    1 : Full alignment enable.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD7;
    LCD_DataWrite(temp);
}
void Font_Background_select_Transparency(void)
{
    /*
    Font Transparency
    0 : Font with background color.
    1 : Font with background transparency.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD6;
    LCD_DataWrite(temp);
}
void Font_Background_select_Color(void)
{
    /*
    Font Transparency
    0 : Font with background color.
    1 : Font with background transparency.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD6;
    LCD_DataWrite(temp);
}
void Font_0_degree(void)
{
    /*
    Font Rotation
    0 : Normal
    Text direction from left to right then from top to bottom
    1 : Counterclockwise 90 degree & horizontal flip
    Text direction from top to bottom then from left to right
    (it should accommodate with set VDIR as 1)
    This attribute can be changed only when previous font write
    finished (core_busy = 0)
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD4;
    LCD_DataWrite(temp);
}
void Font_90_degree(void)
{
    /*
    Font Rotation
    0 : Normal
    Text direction from left to right then from top to bottom
    1 : Counterclockwise 90 degree & horizontal flip
    Text direction from top to bottom then from left to right
    (it should accommodate with set VDIR as 1)
    This attribute can be changed only when previous font write
    finished (core_busy = 0)
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD4;
    LCD_DataWrite(temp);
}
void Font_Width_X1(void)
{
    /*
    Horizontal Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Font_Width_X2(void)
{
    /*
    Horizontal Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Font_Width_X3(void)
{
    /*
    Horizontal Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Font_Width_X4(void)
{
    /*
    Horizontal Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD3;
    temp |= cSetD2;
    LCD_DataWrite(temp);
}
void Font_Height_X1(void)
{
    /*
    Vertical Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Font_Height_X2(void)
{
    /*
    Vertical Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp &= cClrD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}
void Font_Height_X3(void)
{
    /*
    Vertical Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp &= cClrD0;
    LCD_DataWrite(temp);
}
void Font_Height_X4(void)
{
    /*
    Vertical Font Enlargement
    00b : X1.
    01b : X2.
    10b : X3.
    11b : X4.
    */
    unsigned char temp;
    LCD_CmdWrite(0xCD);
    temp = LCD_DataRead();
    temp |= cSetD1;
    temp |= cSetD0;
    LCD_DataWrite(temp);
}

//[CEh]=========================================================================
void GTFont_Select_GT21L16TW_GT21H16T1W(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT23L16U2W(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp &= cClrD6;
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT23L24T3Y_GT23H24T3Y(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT23L24M1Z(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp &= cClrD7;
    temp |= cSetD6;
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT23L32S4W_GT23H32S4W(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp &= cClrD6;
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT20L24F6Y(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp &= cClrD6;
    temp |= cSetD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT21L24S1W(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp |= cSetD6;
    temp &= cClrD5;
    LCD_DataWrite(temp);
}
void GTFont_Select_GT22L16A1Y(void)
{
    /*
    GT Serial Font ROM Select
    000b: GT21L16TW / GT21H16T1W
    001b: GT23L16U2W
    010b: GT23L24T3Y / GT23H24T3Y
    011b: GT23L24M1Z
    100b: GT23L32S4W / GT23H32S4W
    101b: GT20L24F6Y
    110b: GT21L24S1W
    111b: GT22L16A1Y
    */
    unsigned char temp;
    LCD_CmdWrite(0xCE);
    temp = LCD_DataRead();
    temp |= cSetD7;
    temp |= cSetD6;
    temp |= cSetD5;
    LCD_DataWrite(temp);
}

//[CFh]=========================================================================
void Set_GTFont_Decoder(unsigned char temp)
{
    /*
    [bit7-3]
    FONT ROM Coding Setting
    For specific GT serial Font ROM, the coding method must be set for decoding.
    00000b: GB2312
    00001b: GB12345/GB18030
    00010b: BIG5
    00011b: UNICODE
    00100b: ASCII
    00101b: UNI-Japanese
    00110b: JIS0208
    00111b: Latin/Greek/ Cyrillic / Arabic/Thai/Hebrew
    01000b: Korea
    10001b: ISO-8859-1
    10010b: ISO-8859-2
    10011b: ISO-8859-3
    10100b: ISO-8859-4
    10101b: ISO-8859-5
    10110b: ISO-8859-6
    10111b: ISO-8859-7
    11000b: ISO-8859-8
    11001b: ISO-8859-9
    11010b: ISO-8859-10
    11011b: ISO-8859-11
    11100b: ISO-8859-12
    11101b: ISO-8859-13
    11110b: ISO-8859-14
    11111b: ISO-8859-15

    [bit1-0]
    ASCII / Latin/Greek/ Cyrillic / Arabic
            (ASCII)		(Latin/Greek/Cyrillic)	(Arabic)
    00b		Normal			Normal 					NA
    01b		Arial 		Variable Width 			Presentation Forms-A
    10b		Roman 			NA 					Presentation Forms-B
    11b		Bold			NA 						NA
    */
    LCD_CmdWrite(0xCF);
    LCD_DataWrite(temp);
}
//[D0h]=========================================================================
void Font_Line_Distance(unsigned char temp)
{
    /*[bit4-0]
    Font Line Distance Setting
    Setting the font character line distance when setting memory font
    write cursor auto move. (Unit: pixel)
    */
    LCD_CmdWrite(0xD0);
    LCD_DataWrite(temp);
}
//[D1h]=========================================================================
void Set_Font_to_Font_Width(unsigned char temp)
{
    /*[bit5-0]
    Font to Font Width Setting (Unit: pixel)
    */
    LCD_CmdWrite(0xD1);
    LCD_DataWrite(temp);
}
//[D2h]~[D4h]=========================================================================
void Foreground_RGB(unsigned char RED, unsigned char GREEN, unsigned char BLUE)
{
    /*
    [D2h] Foreground Color - Red, for draw, text or color expansion
    [D3h] Foreground Color - Green, for draw, text or color expansion
    [D4h] Foreground Color - Blue, for draw, text or color expansion
    */
    LCD_CmdWrite(0xD2);
    LCD_DataWrite(RED);

    LCD_CmdWrite(0xD3);
    LCD_DataWrite(GREEN);

    LCD_CmdWrite(0xD4);
    LCD_DataWrite(BLUE);
}

// Input data format:R3G3B2
void Foreground_color_256(unsigned char temp)
{
    LCD_CmdWrite(0xD2);
    LCD_DataWrite(temp);

    LCD_CmdWrite(0xD3);
    LCD_DataWrite(temp << 3);

    LCD_CmdWrite(0xD4);
    LCD_DataWrite(temp << 6);
}
// Read data format:R5G6B6
uint16_t Read_Foreground_color_65k(void)
{
    uint16_t temp;
    uint16_t color;
    LCD_CmdWrite(0xD2);
    temp = LCD_DataRead();
    color = temp >> 3;
    LCD_CmdWrite(0xD3);
    temp = LCD_DataRead();
    color = (color << 11) + ((temp >> 2) << 5);
    LCD_CmdWrite(0xD4);
    temp = LCD_DataRead();
    color = color + (temp >> 3);
    ;

    return color;
}
// Input data format:R5G6B5
void Foreground_color_65k(unsigned short temp)
{
    LCD_CmdWrite(0xD2);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0xD3);
    LCD_DataWrite(temp >> 3);

    LCD_CmdWrite(0xD4);
    LCD_DataWrite(temp << 3);
}

// Input data format:R8G8B8
void Foreground_color_16M(unsigned long temp)
{
    LCD_CmdWrite(0xD2);
    LCD_DataWrite(temp >> 16);

    LCD_CmdWrite(0xD3);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0xD4);
    LCD_DataWrite(temp);
}

//[D5h]~[D7h]=========================================================================
/*
[D5h] Background Color - Red, for Text or color expansion
[D6h] Background Color - Green, for Text or color expansion
[D7h] Background Color - Blue, for Text or color expansion
*/
void Background_RGB(unsigned char RED, unsigned char GREEN, unsigned char BLUE)
{

    LCD_CmdWrite(0xD5);
    LCD_DataWrite(RED);

    LCD_CmdWrite(0xD6);
    LCD_DataWrite(GREEN);

    LCD_CmdWrite(0xD7);
    LCD_DataWrite(BLUE);
}

// Input data format:R3G3B2
void Background_color_256(unsigned char temp)
{
    LCD_CmdWrite(0xD5);
    LCD_DataWrite(temp);

    LCD_CmdWrite(0xD6);
    LCD_DataWrite(temp << 3);

    LCD_CmdWrite(0xD7);
    LCD_DataWrite(temp << 6);
}

// Input data format:R5G6B6
void Background_color_65k(unsigned short temp)
{
    LCD_CmdWrite(0xD5);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0xD6);
    LCD_DataWrite(temp >> 3);

    LCD_CmdWrite(0xD7);
    LCD_DataWrite(temp << 3);
}
// Read data format:R5G6B6
uint16_t Read_Background_color_65k(void)
{
    uint16_t temp;
    uint16_t color;
    LCD_CmdWrite(0xD5);
    temp = LCD_DataRead();
    color = temp >> 3;
    LCD_CmdWrite(0xD6);
    temp = LCD_DataRead();
    color = (color << 11) + ((temp >> 2) << 5);
    LCD_CmdWrite(0xD7);
    temp = LCD_DataRead();
    color = color + (temp >> 3);
    ;

    return color;
}
// Input data format:R8G8B8
void Background_color_16M(unsigned long temp)
{
    LCD_CmdWrite(0xD5);
    LCD_DataWrite(temp >> 16);

    LCD_CmdWrite(0xD6);
    LCD_DataWrite(temp >> 8);

    LCD_CmdWrite(0xD7);
    LCD_DataWrite(temp);
}

//[DBh]~[DEh]=========================================================================
void CGRAM_Start_address(unsigned long Addr)
{
    /*
    CGRAM START ADDRESS [31:0]
    */
    LCD_CmdWrite(0xDB);
    LCD_DataWrite(Addr);
    LCD_CmdWrite(0xDC);
    LCD_DataWrite(Addr >> 8);
    LCD_CmdWrite(0xDD);
    LCD_DataWrite(Addr >> 16);
    LCD_CmdWrite(0xDE);
    LCD_DataWrite(Addr >> 24);
}

//[DFh]=========================================================================
/*
[bit7] Enter Power saving state
0: Normal state.
1: Enter power saving state.
[bit1][bit0] Power saving Mode definition
00: NA
01: Standby Mode
10: Suspend Mode
11: Sleep Mode
*/
void Power_Normal_Mode(void)
{
    LCD_CmdWrite(0xDF);
    LCD_DataWrite(0x00);
}
void Power_Saving_Standby_Mode(void)
{
    LCD_CmdWrite(0xDF);
    LCD_DataWrite(0x01);
    LCD_CmdWrite(0xDF);
    LCD_DataWrite(0x81);
}
void Power_Saving_Suspend_Mode(void)
{
    LCD_CmdWrite(0xDF);
    //	LCD_DataWrite(0x02);
    //	LCD_CmdWrite(0xDF);
    LCD_DataWrite(0x82);
}
void Power_Saving_Sleep_Mode(void)
{
    LCD_CmdWrite(0xDF);
    //	LCD_DataWrite(0x03);
    //	LCD_CmdWrite(0xDF);
    LCD_DataWrite(0x83);
}

//[E5h]~[E6h]=========================================================================
void RA8876_I2CM_Clock_Prescale(unsigned short WX)
{
    /*
    I2C Master Clock Pre-scale [7:0]
    I2C Master Clock Pre-scale [15:8]
    */
    LCD_CmdWrite(0xE5);
    LCD_DataWrite(WX);
    LCD_CmdWrite(0xE6);
    LCD_DataWrite(WX >> 8);
}
//[E7h]=========================================================================
void RA8876_I2CM_Transmit_Data(unsigned char temp)
{
    /*
    I2C Master Transmit[7:0]
    */
    LCD_CmdWrite(0xE7);
    LCD_DataWrite(temp);
}
//[E8h]=========================================================================
unsigned char RA8876_I2CM_Receiver_Data(void)
{
    /*
    I2C Master Receiver [7:0]
    */
    unsigned char temp;
    LCD_CmdWrite(0xE8);
    temp = LCD_DataRead();
    return temp;
}
//[E9h]=========================================================================
/*
[bit7] START
Generate (repeated) start condition and be cleared by hardware automatically
Note : This bit is always read as 0.
[bit6] STOP
Generate stop condition and be cleared by hardware automatically
Note : This bit is always read as 0.
[bit5]
READ(READ and WRITE can��t be used simultaneously)
Read form slave and be cleared by hardware automatically
Note : This bit is always read as 0.
[bit4]
WRITE(READ and WRITE can��t be used simultaneously)
Write to slave and be cleared by hardware automatically
Note : This bit is always read as 0.
[bit3] ACKNOWLEDGE
When as a I2C master receiver
0 : Sent ACK.
1 : Sent NACK.
Note : This bit is always read as 0.
[bit0] Noise Filter
0 : Enable.
1 : Disable.
*/

void RA8876_I2CM_Stop(void)
{
    LCD_CmdWrite(0xE9);
#ifdef Disable_I2CM_Noise_Filter
    LCD_DataWrite(0x40);
#endif

#ifdef Enable_I2CM_Noise_Filter
    LCD_DataWrite(0x41);
#endif
}
void RA8876_I2CM_Read_With_Ack(void)
{

    LCD_CmdWrite(0xE9);
#ifdef Disable_I2CM_Noise_Filter
    LCD_DataWrite(0x20);
#endif
#ifdef Enable_I2CM_Noise_Filter
    LCD_DataWrite(0x21);
#endif
}

void RA8876_I2CM_Read_With_Nack(void)
{

    LCD_CmdWrite(0xE9);
#ifdef Disable_I2CM_Noise_Filter
    LCD_DataWrite(0x68);
#endif
#ifdef Enable_I2CM_Noise_Filter
    LCD_DataWrite(0x69);
#endif
}

void RA8876_I2CM_Write_With_Start(void)
{
    LCD_CmdWrite(0xE9);
#ifdef Disable_I2CM_Noise_Filter
    LCD_DataWrite(0x90);
#endif

#ifdef Enable_I2CM_Noise_Filter
    LCD_DataWrite(0x91);
#endif
}

void RA8876_I2CM_Write(void)
{
    LCD_CmdWrite(0xE9);
#ifdef Disable_I2CM_Noise_Filter
    LCD_DataWrite(0x10);
#endif
#ifdef Enable_I2CM_Noise_Filter
    LCD_DataWrite(0x11);
#endif
}

//[EAh]=========================================================================
/*
 0=Ack
 1=Nack
*/
unsigned char RA8876_I2CM_Check_Slave_ACK(void)
{
    unsigned char temp;
    /*[bit7]
    Received acknowledge from slave
    0 : Acknowledge received.
    1 : No Acknowledge received.
    */
    LCD_CmdWrite(0xEA);
    temp = LCD_DataRead();
    if ((temp & 0x80) == 0x80)
        return 1;
    else
        return 0;
}

/*
 0=Idle
 1=Busy
*/
unsigned char RA8876_I2CM_Bus_Busy(void)
{
    unsigned char temp;

    /*[bit6]
    I2C Bus is Busy
    0 : Idle.
    1 : Busy.
    */
    LCD_CmdWrite(0xEA);
    temp = LCD_DataRead();
    if ((temp & 0x40) == 0x40)
        return 1;
    else
        return 0;
}

/*
 0=Complete
 1=Transferring
*/
unsigned char RA8876_I2CM_transmit_Progress(void)
{
    unsigned char temp;
    /*[bit6]
     0=Complete
     1=Transferring
    */
    LCD_CmdWrite(0xEA);
    temp = LCD_DataRead();
    if ((temp & 0x02) == 0x02)
        return 1;
    else
        return 0;
}

/*
0= Arbitration win
1= Arbitration lost
*/
unsigned char RA8876_I2CM_Arbitration(void)
{
    unsigned char temp;
    /*[bit6]
    I2C Bus is Busy
    0 : Idle.
    1 : Busy.
    */
    LCD_CmdWrite(0xEA);
    temp = LCD_DataRead();
    temp &= 0x01;
    return temp;
}

void Graphic_Mode(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp &= cClrD2;
    LCD_DataWrite(temp);
}
void Text_Mode(void)
{
    unsigned char temp;
    LCD_CmdWrite(0x03);
    temp = LCD_DataRead();
    temp |= cSetD2;
    LCD_DataWrite(temp);
}

void Show_String(uint8_t *str)
{
    Text_Mode();
    LCD_CmdWrite(0x04);
    while (*str != '\0')
    {
        LCD_DataWrite(*str);
        Check_Mem_WR_FIFO_not_Full();
        ++str;
    }
    Check_2D_Busy();

    Graphic_Mode(); // back to graphic mode
}
void Font_Init(void)
{
    Select_SFI_1();
    Select_SFI_Font_Mode();
    Select_SFI_24bit_Address();
    Select_SFI_Waveform_Mode_0();
    Select_SFI_0_DummyRead();
    Select_SFI_Single_Mode();
    SPI_Clock_Period(2); // Freq must setting <=20MHZ

    Enable_SFlash_SPI();

    Set_GTFont_Decoder(0x01);
}

void FLASH_Read_128Mb(unsigned char *pBuffer, unsigned int ReadAddr, unsigned int NumByteToRead) // ��Һ���ڲ�flash��ȡͼƬλ����Ϣ�����?128Mb������
{

    Select_nSS_drive_on_xnsfcs0();
    nSS_Inactive();
    SPI_Clock_Period(1);
    // Read ID
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x0B);
    SPI_Master_FIFO_Data_Put((ReadAddr & 0xFF0000) >> 16);
    SPI_Master_FIFO_Data_Put((ReadAddr & 0xFF00) >> 8);
    SPI_Master_FIFO_Data_Put(ReadAddr & 0xFF);
    SPI_Master_FIFO_Data_Put(0x00);
    while (NumByteToRead--) /* while there is data to be read */
    {

        *pBuffer = SPI_Master_FIFO_Data_Put(0xff);

        pBuffer++;
    }

    nSS_Inactive();
}

unsigned char W25N01_Read_Status_Register2(void)
{
    unsigned char temp;

    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x0F);
    SPI_Master_FIFO_Data_Put(0xB0);
    delay_us(1);
    temp = SPI_Master_FIFO_Data_Put(0xff); // dummy cycle and read back value
    nSS_Inactive();

    return (temp);
}

void W25N01_Write_Enable(void)
{
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x06);
    nSS_Inactive();
}

//**************************************************************//
//**************************************************************//
void W25N01_Write_Status_Register2(unsigned char data)
{

    W25N01_Write_Enable();
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x1F);
    SPI_Master_FIFO_Data_Put(0xB0);
    SPI_Master_FIFO_Data_Put(data);
    nSS_Inactive();
}

void W25N01_Clear_BUF(void)
{
    unsigned char temp;
    temp = W25N01_Read_Status_Register2();
    temp &= 0xf7;
    W25N01_Write_Status_Register2(temp);
    delay_us(500);
}
void W25N01_Set_BUF(void)
{
    unsigned char temp;

    temp = W25N01_Read_Status_Register2();
    temp &= 0xff;
    W25N01_Write_Status_Register2(temp);
    delay_us(500);
}

void FLASH_Read_1024GMb(unsigned char *UpdataValue, unsigned short ReadAddr) // ��Һ���ڲ�flash��ȡͼƬλ����Ϣ�����?1024Mb������
{

    uint16_t i = 0;

    W25N01_Set_BUF();

    Select_nSS_drive_on_xnsfcs0();
    nSS_Inactive();
    SPI_Clock_Period(1);

    nSS_Active();

    SPI_Master_FIFO_Data_Put(0x13);
    SPI_Master_FIFO_Data_Put(0xff);
    SPI_Master_FIFO_Data_Put(0);
    SPI_Master_FIFO_Data_Put(0);
    nSS_Inactive();
    DelayMS(10);
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x03);

    SPI_Master_FIFO_Data_Put(0);
    SPI_Master_FIFO_Data_Put(0);
    SPI_Master_FIFO_Data_Put(0xff);

    for (i = 0; i < (ReadAddr + 12); i++)
    {
        if ((i >= ReadAddr) & (i < (ReadAddr + 12)))
        {
            *UpdataValue = SPI_Master_FIFO_Data_Put(0xff);
            UpdataValue++;
        }
        else
        {
            SPI_Master_FIFO_Data_Put(0xff);
        }
    }

    nSS_Inactive();

    W25N01_Clear_BUF();
}

/*
��ʾ�Զ���ͼƬ
x:X�����ַ
x:Y�����ַ
w:��ʾͼƬ�Ŀ���
h:��ʾͼƬ�ĸ߶�
numbers:��ʾͼƬ���ֽ���
*datap��ͼƬ�����ָ��
ע�⣺�Ƽ��á�image2lcd����������ͼƬ���飬�����ʽ�Ǹ�λ��ǰ��RGB565��ʽ
*/
void Draw_Picture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, unsigned long numbers, const unsigned char *datap)
{
    unsigned long i;
    uint16_t temp;
    Graphic_Mode_8876();

    Active_Window_WH(w, h);
    Active_Window_XY(x, y);
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare();

    for (i = 0; i < numbers;)
    {
        if (MPU_Interface == 2)
        {
            temp = (uint16_t)datap[i];
            temp = (temp << 8) + datap[i + 1];

            LCD_DataWrite(temp);
        }
        else
        {
            LCD_DataWrite(datap[i + 1]);
            LCD_DataWrite(datap[i]);
        }
        // Check_Mem_WR_FIFO_not_Full(); //���MCU�ٶȱȽϿ죬Ҫ�����������������һ��72M��STM32��������ʲô�ӿڣ�������Ҫ����Ρ�
        i = i + 2;
    }
    Active_Window_WH(lcdx, lcdy);
    Active_Window_XY(0, 0);
}

void Disp_FloatNum(uint8_t mode, uint32_t x, uint32_t y, uint8_t fontsize, uint8_t w, double value, unsigned char *format, uint16_t B_color, uint16_t F_color) // ��ʾ���������ͻ����Ը����Լ��������޸ĳ���
{

    unsigned char temp[10];
    uint16_t tempb, tempf;
    tempf = Read_Foreground_color_65k();
    tempb = Read_Background_color_65k();
    Select_SFI_1();
    Select_SFI_Font_Mode();

    Select_SFI_Waveform_Mode_0();
    Select_SFI_0_DummyRead();
    Select_SFI_Single_Mode();
    SPI_Clock_Period(4); // Freq must setting <=20MHZ
    GTFont_Select_GT23L32S4W_GT23H32S4W();

    Enable_SFlash_SPI();
    Memory_XY_Mode();
    Background_color_65k(B_color);
    if (mode == 0)
        Font_Background_select_Color();
    if (mode == 1)
        Font_Background_select_Transparency();

    if (fontsize == 16)
        Font_Select_8x16_16x16();
    if (fontsize == 24)
        Font_Select_12x24_24x24();
    if (fontsize == 32)
        Font_Select_16x32_32x32();

    sprintf((char *)temp, format, value);
    Foreground_color_65k(B_color);
    GUI_RectangleFill(x, y, w, fontsize);
    Foreground_color_65k(F_color);
    Goto_Text_XY(x, y);
    Show_String(temp);
    Foreground_color_65k(tempf);
    Foreground_color_65k(tempb);
}

/*******************************************************************************
 * ������  : һ����ɫ��ʽ��ʾ1024MB�ڵ�ͼƬ
 * ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ
 * ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼��������б���Ӧ��X,YΪ�ڸ�λ����ʾ������ ��Filter_ColorΪ����
 * ���         : None
 * ����         : None
 **********/
void Dis_Png_mix_1024Mb(uint16_t picnum, uint16_t x, uint16_t y, uint16_t Filter_Color)
{
    unsigned long picx = 0, picy = 0, fadd = 0;
    unsigned char buf3[12];
    uint16_t temp_color = 0x0000;
    temp_color = Read_Background_color_65k(); // ����Ŀǰ����ɫ
    FLASH_Read_1024GMb(buf3, picnum * 12);

    fadd = (unsigned long)buf3[0];
    fadd = (fadd << 8) + buf3[1];
    fadd = (fadd << 8) + buf3[2];
    fadd = (fadd << 8) + buf3[3];

    picx = (unsigned long)buf3[4];
    picx = (picx << 8) + buf3[5];
    picx = (picx << 8) + buf3[6];
    picx = (picx << 8) + buf3[7];

    picy = (unsigned long)buf3[8];
    picy = (picy << 8) + buf3[9];
    picy = (picy << 8) + buf3[10];
    picy = (picy << 8) + buf3[11];

    if ((picx != 0) & (picy != 0) & (picnum < 200))
    {

        Select_SFI_0();
        Enable_SFlash_SPI();

        Select_SFI_DMA_Mode();
        Select_SFI_24bit_Address();
        Select_SFI_8_DummyRead();
        Memory_Linear_Mode();
        Select_SFI_Waveform_Mode_3();
        Select_SFI_Dual_Mode0();

        SPI_Clock_Period(1);
        nSS_Active();
        SPI_Master_FIFO_Data_Put(0x13);
        SPI_Master_FIFO_Data_Put(0xff);
        SPI_Master_FIFO_Data_Put((fadd / 2048) >> 8);
        SPI_Master_FIFO_Data_Put(fadd / 2048);
        nSS_Inactive();
        DelayMS(10);
        SPI_Clock_Period(0);

        SFI_DMA_Transfer_Number(picx * picy * 2);
        // Canvas_Image_Start_address(Layer3);
        SFI_DMA_Destination_Start_Address(Layer3);

        Start_SFI_DMA();
        Check_Busy_SFI_DMA();

        BTE_Destination_Color_16bpp();
        BTE_Destination_Memory_Start_Address(Draw_Layer);
        BTE_Destination_Image_Width(lcdx);
        BTE_Destination_Window_Start_XY(x, y); // x,y
        BTE_Window_Size(picx, picy);

        BTE_S0_Color_16bpp();
        BTE_S0_Memory_Start_Address(Layer3);
        BTE_S0_Image_Width(picx);
        BTE_S0_Window_Start_XY(0, 0); // x,y

        BTE_S1_Color_16bpp();
        BTE_S1_Memory_Start_Address(Draw_Layer);
        BTE_S1_Image_Width(lcdx);
        BTE_S1_Window_Start_XY(0, 0);
        BTE_ROP_Code(14);
        BTE_Operation_Code(5); // BTE move
        Background_color_65k(Filter_Color);
        BTE_Enable();
        Check_BTE_Busy();
        //	Canvas_Image_Start_address(Current_Layer);
        Background_color_65k(temp_color);
    }
}

//**************************************************************//
// write disable
//**************************************************************//
void W25N01_Write_Disable(void)
{
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x04);
    nSS_Inactive();
}
void W25N01_Write_Status_Register1(unsigned char data)
{
    W25N01_Write_Enable();
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x1F);
    SPI_Master_FIFO_Data_Put(0xA0);
    SPI_Master_FIFO_Data_Put(data);
    nSS_Inactive();
}

//**************************************************************//
//**************************************************************//
unsigned char W25N01_Read_Status_Register3(void)
{
    unsigned char temp;

    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x0F);
    SPI_Master_FIFO_Data_Put(0xC0);
    delay_us(1);
    temp = SPI_Master_FIFO_Data_Put(0xff); // dummy cycle and read back value
    nSS_Inactive();

    return (temp);
}
void W25N01_Set_ECC(void)
{
    unsigned char temp;

    temp = W25N01_Read_Status_Register2();
    temp |= 0x10;
    W25N01_Write_Status_Register2(temp);
    delay_us(500);
}

void W25N01_Reset(void)
{

    Select_nSS_drive_on_xnsfcs0();
    nSS_Inactive();

    nSS_Active();
    SPI_Master_FIFO_Data_Put(0xff); // spi nand reset
    nSS_Inactive();
    DelayMS(10);
}

void RA8876_PLL_Initial(void)
{

    if (50 < SCAN_FREQ)
    {
        Write_Dir(0x05, 0x02); // PLL Divided by 2
        Write_Dir(0x06, (SCAN_FREQ * 2 / OSC_FREQ) - 1);
    }
    if ((25 < SCAN_FREQ) && (SCAN_FREQ <= 50))
    {
        Write_Dir(0x05, 0x04); // PLL Divided by 4
        Write_Dir(0x06, (SCAN_FREQ * 4 / OSC_FREQ) - 1);
    }
    if ((12 < SCAN_FREQ) && (SCAN_FREQ <= 25))
    {
        Write_Dir(0x05, 0x06); // PLL Divided by 8
        Write_Dir(0x06, (SCAN_FREQ * 8 / OSC_FREQ) - 1);
    }
    if ((7 < SCAN_FREQ) && (SCAN_FREQ <= 12))
    {
        Write_Dir(0x05, 0x08); // PLL Divided by 16
        Write_Dir(0x06, (SCAN_FREQ * 16 / OSC_FREQ) - 1);
    }
    if (SCAN_FREQ <= 7)
    {
        Write_Dir(0x05, 0x0A); // PLL Divided by 32
        Write_Dir(0x06, (SCAN_FREQ * 32 / OSC_FREQ) - 1);
    }

    // Set SDRAM clock
    if (50 < DRAM_FREQ)
    {
        Write_Dir(0x07, 0x02); // PLL Divided by 2
        Write_Dir(0x08, (DRAM_FREQ * 2 / OSC_FREQ) - 1);
    }
    if ((25 < DRAM_FREQ) && (DRAM_FREQ <= 50))
    {
        Write_Dir(0x07, 0x04); // PLL Divided by 4
        Write_Dir(0x08, (DRAM_FREQ * 4 / OSC_FREQ) - 1);
    }
    if ((12 < DRAM_FREQ) && (DRAM_FREQ <= 25))
    {
        Write_Dir(0x07, 0x06); // PLL Divided by 8
        Write_Dir(0x08, (DRAM_FREQ * 8 / OSC_FREQ) - 1);
    }

    // Set Core clock
    if (50 < CORE_FREQ)
    {
        Write_Dir(0x09, 0x02); // PLL Divided by 2
        Write_Dir(0x0A, (CORE_FREQ * 2 / OSC_FREQ) - 1);
    }
    if ((25 < CORE_FREQ) && (CORE_FREQ <= 50))
    {
        Write_Dir(0x09, 0x04); // PLL Divided by 4
        Write_Dir(0x0A, (CORE_FREQ * 4 / OSC_FREQ) - 1);
    }
    if ((12 < CORE_FREQ) && (CORE_FREQ <= 25))
    {
        Write_Dir(0x09, 0x06); // PLL Divided by 8
        Write_Dir(0x0A, (CORE_FREQ * 8 / OSC_FREQ) - 1);
    }

    LCD_CmdWrite(0x01);
    LCD_DataWrite(0x00);
    Delaly1ms();
    LCD_DataWrite(0x80);
    Delaly1ms();
}

void RA8876_SDRAM_initail(void)
{

    unsigned short Auto_Refresh;

    Auto_Refresh = (64 * DRAM_FREQ * 1000) / (8192);

    Write_Dir(0xe0, E0VALUE);

    Write_Dir(0xe1, 0x02);
    Write_Dir(0xe2, Auto_Refresh);
    Write_Dir(0xe3, Auto_Refresh >> 8);
    Write_Dir(0xe4, 0x01);

    Check_SDRAM_Ready();

    Delaly1ms();
}

void Select_LCD_Sync_Mode(void)
{
    /*
    To Control panel's synchronous signals
    0: Sync Mode: Enable XVSYNC, XHSYNC, XDE
    1: DE Mode: Only XDE enable, XVSYNC & XHSYNC in idle state
    */
    unsigned char temp;
    LCD_CmdWrite(0x10);
    temp = LCD_DataRead();
    temp &= cClrD0;
    LCD_DataWrite(temp);
}

void RA8873_InitHard56(void)
{
    RA8876_HW_Reset();
    RA8876_PLL_Initial();
    RA8876_SDRAM_initail();
    TFT_24bit();

    Host_Bus_8bit();
    RGB_16b_16bpp();
    MemWrite_Left_Right_Top_Down();
    Graphic_Mode();
    Memory_Select_SDRAM();

    //**[10h]**//
    Select_LCD_Sync_Mode(); // Enable XVSYNC, XHSYNC, XDE.
                            //	Select_LCD_DE_Mode();	// XVSYNC & XHSYNC in idle state.

    PCLK_Falling();
    // PCLK_Rising();

    VSCAN_T_to_B();
    PDATA_Set_RGB();

    HSYNC_Low_Active();
    VSYNC_Low_Active();
    DE_High_Active();
    // DE_Low_Active();

    LCD_HorizontalWidth_VerticalHeight(640, 480); // INNOLUX 800x480?C
    LCD_Horizontal_Non_Display(136);              // INNOLUX800x480?A46?C
    LCD_HSYNC_Start_Position(16);                 // INNOLUX800x480?A16~354?C
    LCD_HSYNC_Pulse_Width(10);                    // INNOLUX800x480?A1~40?C
    LCD_Vertical_Non_Display(11);                 // INNOLUX800x480?A23?C
    LCD_VSYNC_Start_Position(32);                 // INNOLUX800x480?A1~147?C
    LCD_VSYNC_Pulse_Width(2);                     // INNOLUX800x480?A1~20?C
}
void RA8873_InitHard70(void)
{
    RA8876_HW_Reset();
    RA8876_PLL_Initial();
    RA8876_SDRAM_initail();
    TFT_24bit();

    if (MPU_Interface == 2) // ����õ�FSMC 16λ�Ļ���Ҫ���ó�16λ�ӿڣ����඼��8bit�ӿ�
    {
        Host_Bus_16bit();
    }
    else
        Host_Bus_8bit();
    RGB_16b_16bpp();
    MemWrite_Left_Right_Top_Down();
    Graphic_Mode();
    Memory_Select_SDRAM();

    //**[10h]**//
    Select_LCD_Sync_Mode(); // Enable XVSYNC, XHSYNC, XDE.
    //	Select_LCD_DE_Mode();	// XVSYNC & XHSYNC in idle state.

    PCLK_Falling();
    // PCLK_Rising();

    VSCAN_T_to_B();
    PDATA_Set_RGB();

    HSYNC_Low_Active();
    VSYNC_Low_Active();
    DE_High_Active();
    // DE_Low_Active();

    LCD_HorizontalWidth_VerticalHeight(800, 480); // INNOLUX 800x480?C
    LCD_Horizontal_Non_Display(46);               // INNOLUX800x480?A46?C
    LCD_HSYNC_Start_Position(210);                // INNOLUX800x480?A16~354?C
    LCD_HSYNC_Pulse_Width(10);                    // INNOLUX800x480?A1~40?C
    LCD_Vertical_Non_Display(23);                 // INNOLUX800x480?A23?C
    LCD_VSYNC_Start_Position(22);                 // INNOLUX800x480?A1~147?C
    LCD_VSYNC_Pulse_Width(10);                    // INNOLUX800x480?A1~20?C
}

void screeninit(void)
{
    Current_Layer = Layer1;
    Draw_Layer = Layer1;
    Select_Main_Window_16bpp();
    Canvas_Image_Start_address(Current_Layer);
    Canvas_image_width(lcdx);

    Active_Window_XY(0, 0); // write/draw
    Active_Window_WH(lcdx, lcdy);

    Main_Image_Start_Address(Current_Layer);
    Main_Image_Width(lcdx);

    Main_Window_Start_XY(0, 0);

    Memory_XY_Mode();
    Memory_16bpp_Mode();
    // Memory_24bpp_Mode();
    Select_Main_Window_16bpp();

    Enable_SFlash_SPI();
    Select_SFI_1();
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
    Select_SFI_Waveform_Mode_3();
    Select_SFI_Dual_Mode1();
    SPI_Clock_Period(0);

    Select_PWM1_Clock_Divided_By_1();
    Select_PWM1();
    Set_Timer1_Count_Buffer(52000);
    Set_Timer1_Compare_Buffer(20000);
    CGROM_Select_Genitop_FontROM();
    GTFont_Select_GT23L32S4W_GT23H32S4W();
    Font_Width_X1();
    Font_Height_X1();
    Foreground_color_65k(Fcolor);
    Background_color_65k(Bcolor);
}

/*******************************************************************************
 * ������  : ����ǰ��ɫ�ͱ���ɫ
 * ����    : ����Һ��ǰ��ɫ�ͱ���ɫ
 * ����    : ����ǰ��ɫBC ����ɫFC
 * ���?    : ǰ��ɫFcolor ����ɫBcolor
 * ����    : None
 *******************************************************************************/
void Set_Color(uint16_t bc, uint16_t fc) // ����bcΪ����ɫ��fcΪǰ��ɫ
{
    Bcolor = bc, Fcolor = fc;
    Foreground_color_65k(Bcolor); //
    Line_Start_XY(0, 0);
    Line_End_XY(lcdx - 1, lcdy - 1);
    Start_Square_Fill();
    Foreground_color_65k(Fcolor);
}

void LCD_Select(uint8_t lcdnum)
{
    switch (lcdnum)
    {

    case 0x05: // 5.6�� 640*480�ֱ���
    {
        lcdx = 640;
        lcdy = 480;
        Layer0 = 0;
        Layer1 = 0x180000;
        Layer2 = 0x380000;
        Layer3 = 0x580000;
        DRAM_FREQ = 80, CORE_FREQ = 80, SCAN_FREQ = 30;
        E0VALUE = 0x28;
        RA8873_InitHard56();
        screeninit();
    }
    break;
    }
}

/*******************************************************************************
 * ������  : ���ñ�������
 * ����    : ����Һ����������
 * ����          : �趨�������� ��Χ0~100
 * ���?         : None
 * ����         : None
 *******************************************************************************/
void Set_Backlight(uint8_t bl) // ���ñ������ȣ���Χ0~100
{
    Set_PWM_Prescaler_1_to_256(1);
    Select_PWM0_Clock_Divided_By_1();
    Select_PWM0();
    Set_Timer0_Count_Buffer(1000);
    Set_Timer0_Compare_Buffer(bl * 60);
    Start_PWM0();
}

void GUI_CleanScreen(void) // �ñ���ɫ����
{
    Foreground_color_65k(Bcolor); //
    Line_Start_XY(0, 0);
    Line_End_XY(lcdx - 1, lcdy - 1);
    Start_Square_Fill();
    Foreground_color_65k(Fcolor);
}

#if 0

void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
    Line_Start_XY(x, y);     /* ���ù��λ��? */
    lcd_write_ram_prepare(); /* ��ʼд��GRAM */
    LCD->LCD_RAM = color;
}

/**
 * @brief       ���ô���(��RGB����Ч),���Զ����û������굽�������Ͻ�(sx,sy).
 * @param       sx,sy:������ʼ����(���Ͻ�)
 * @param       width,height:���ڿ��Ⱥ͸߶�,�������?0!!
 *   @note      ������?:width*height.
 *
 * @retval      ��
 */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    Line_Start_XY(sx, sy);
    Line_Start_XY(sx + width, sy + height);
}

/**
 * @brief       ��������
 * @param       color: Ҫ��������ɫ
 * @retval      ��
 */
void lcd_clear(uint16_t color)
{
}

/**
 * @brief       ��ָ����������䵥�����?
 * @param       (sx,sy),(ex,ey):�����ζԽ�����,�����С�?:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:Ҫ������ɫ(32λ��ɫ,�������LTDC)
 * @retval      ��
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++)
    {
        lcd_set_cursor(sx, i);   /* ���ù��λ��? */
        lcd_write_ram_prepare(); /* ��ʼд��GRAM */

        for (j = 0; j < xlen; j++)
        {
            LCD->LCD_RAM = color; /* ��ʾ��ɫ */
        }
    }
}

/**
 * @brief       ��ָ�����������ָ����ɫ��?
 * @param       (sx,sy),(ex,ey):�����ζԽ�����,�����С�?:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: Ҫ������ɫ�����׵�ַ
 * @retval      ��
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t height, width;
    uint16_t i, j;
    width = ex - sx + 1;  /* �õ����Ŀ��� */
    height = ey - sy + 1; /* �߶� */

    for (i = 0; i < height; i++)
    {
        lcd_set_cursor(sx, sy + i); /* ���ù��λ��? */
        lcd_write_ram_prepare();    /* ��ʼд��GRAM */

        for (j = 0; j < width; j++)
        {
            LCD->LCD_RAM = color[i * width + j]; /* д������ */
        }
    }
}

/**
 * @brief       ����
 * @param       x1,y1: �������?
 * @param       x2,y2: �յ�����
 * @param       color: �ߵ���ɫ
 * @retval      ��
 */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1; /* ������������ */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0)
        incx = 1; /* ���õ������� */
    else if (delta_x == 0)
        incx = 0; /* ��ֱ�� */
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; /* ˮƽ�� */
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x; /* ѡȡ�������������� */
    else
        distance = delta_y;

    for (t = 0; t <= distance + 1; t++) /* �������? */
    {
        lcd_draw_point(row, col, color); /* ���� */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * @brief       ��ˮƽ��
 * @param       x,y: �������?
 * @param       len  : �߳���
 * @param       color: ���ε���ɫ
 * @retval      ��
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
    if ((len == 0) || (x > lcddev.width) || (y > lcddev.height))
        return;

    lcd_fill(x, y, x + len - 1, y, color);
}

/**
 * @brief       ������
 * @param       x1,y1: �������?
 * @param       x2,y2: �յ�����
 * @param       color: ���ε���ɫ
 * @retval      ��
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief       ��Բ
 * @param       x,y  : Բ��������
 * @param       r    : �뾶
 * @param       color: Բ����ɫ
 * @retval      ��
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1); /* �ж��¸���λ�õı�־ */

    while (a <= b)
    {
        lcd_draw_point(x0 + a, y0 - b, color); /* 5 */
        lcd_draw_point(x0 + b, y0 - a, color); /* 0 */
        lcd_draw_point(x0 + b, y0 + a, color); /* 4 */
        lcd_draw_point(x0 + a, y0 + b, color); /* 6 */
        lcd_draw_point(x0 - a, y0 + b, color); /* 1 */
        lcd_draw_point(x0 - b, y0 + a, color);
        lcd_draw_point(x0 - a, y0 - b, color); /* 2 */
        lcd_draw_point(x0 - b, y0 - a, color); /* 7 */
        a++;

        /* ʹ��Bresenham�㷨��Բ */
        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

/**
 * @brief       ���ʵ���?
 * @param       x,y: Բ��������
 * @param       r    : �뾶
 * @param       color: Բ����ɫ
 * @retval      ��
 */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
    uint32_t i;
    uint32_t imax = ((uint32_t)r * 707) / 1000 + 1;
    uint32_t sqmax = (uint32_t)r * (uint32_t)r + (uint32_t)r / 2;
    uint32_t xr = r;

    lcd_draw_hline(x - r, y, 2 * r, color);

    for (i = 1; i <= imax; i++)
    {
        if ((i * i + xr * xr) > sqmax)
        {
            /* draw lines from outside */
            if (xr > imax)
            {
                lcd_draw_hline(x - i + 1, y + xr, 2 * (i - 1), color);
                lcd_draw_hline(x - i + 1, y - xr, 2 * (i - 1), color);
            }

            xr--;
        }

        /* draw lines from inside (center) */
        lcd_draw_hline(x - xr, y + i, 2 * xr, color);
        lcd_draw_hline(x - xr, y - i, 2 * xr, color);
    }
}

/**
 * @brief       ��ָ��λ����ʾһ���ַ�
 * @param       x,y  : ����
 * @param       chr  : Ҫ��ʾ���ַ�:" "--->"~"
 * @param       size : ������? 12/16/24/32
 * @param       mode : ���ӷ�ʽ(1); �ǵ��ӷ�ʽ(0);
 * @param       color : �ַ�����ɫ;
 * @retval      ��
 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* �õ�����һ���ַ���Ӧ������ռ���ֽ��� */
    chr = chr - ' ';                                        /* �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩ */

    switch (size)
    {
    case 12:
        pfont = (uint8_t *)asc2_1206[chr]; /* ����1206���� */
        break;

    case 16:
        pfont = (uint8_t *)asc2_1608[chr]; /* ����1608���� */
        break;

    case 24:
        pfont = (uint8_t *)asc2_2412[chr]; /* ����2412���� */
        break;

    case 32:
        pfont = (uint8_t *)asc2_3216[chr]; /* ����3216���� */
        break;

    default:
        return;
    }

    for (t = 0; t < csize; t++)
    {
        temp = pfont[t]; /* ��ȡ�ַ��ĵ������� */

        for (t1 = 0; t1 < 8; t1++) /* һ���ֽ�8���� */
        {
            if (temp & 0x80) /* ��Ч��,��Ҫ��ʾ */
            {
                lcd_draw_point(x, y, color); /* �������?,Ҫ��ʾ�����? */
            }
            else if (mode == 0) /* ��Ч��,����ʾ */
            {
                lcd_draw_point(x, y, g_back_color); /* ������ɫ,�൱������㲻���?(ע�ⱳ��ɫ��ȫ�ֱ�������) */
            }

            temp <<= 1; /* ��λ, �Ա��ȡ��һ��λ��״�? */
            y++;

            if (y >= lcddev.height)
                return; /* �������� */

            if ((y - y0) == size) /* ��ʾ��һ����? */
            {
                y = y0; /* y���긴λ */
                x++;    /* x�������? */

                if (x >= lcddev.width)
                    return; /* x���곬������ */

                break;
            }
        }
    }
}

/**
 * @brief       ƽ������, m^n
 * @param       m: ����
 * @param       n: ָ��
 * @retval      m��n�η�
 */
static uint32_t lcd_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)
        result *= m;

    return result;
}

/**
 * @brief       ��ʾlen������
 * @param       x,y : ��ʼ����
 * @param       num : ��ֵ(0 ~ 2^32)
 * @param       len : ��ʾ���ֵ�λ��
 * @param       size: ѡ������ 12/16/24/32
 * @param       color : ���ֵ���ɫ;
 * @retval      ��
 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) /* ������ʾλ��ѭ�� */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* ��ȡ��Ӧλ������ */

        if (enshow == 0 && t < (len - 1)) /* û��ʹ����ʾ,�һ���λҪ��ʾ */
        {
            if (temp == 0)
            {
                lcd_show_char(x + (size / 2) * t, y, ' ', size, 0, color); /* ��ʾ�ո�,ռλ */
                continue;                                                  /* �����¸�һλ */
            }
            else
            {
                enshow = 1; /* ʹ����ʾ */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, 0, color); /* ��ʾ�ַ� */
    }
}

/**
 * @brief       ��չ��ʾlen������(��λ��0Ҳ��ʾ)
 * @param       x,y : ��ʼ����
 * @param       num : ��ֵ(0 ~ 2^32)
 * @param       len : ��ʾ���ֵ�λ��
 * @param       size: ѡ������ 12/16/24/32
 * @param       mode: ��ʾģʽ
 *              [7]:0,�����?;1,���?0.
 *              [6:1]:����
 *              [0]:0,�ǵ�����ʾ;1,������ʾ.
 * @param       color : ���ֵ���ɫ;
 * @retval      ��
 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++) /* ������ʾλ��ѭ�� */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10; /* ��ȡ��Ӧλ������ */

        if (enshow == 0 && t < (len - 1)) /* û��ʹ����ʾ,�һ���λҪ��ʾ */
        {
            if (temp == 0)
            {
                if (mode & 0X80) /* ��λ��Ҫ���?0 */
                {
                    lcd_show_char(x + (size / 2) * t, y, '0', size, mode & 0X01, color); /* ��0ռλ */
                }
                else
                {
                    lcd_show_char(x + (size / 2) * t, y, ' ', size, mode & 0X01, color); /* �ÿո�ռλ */
                }

                continue;
            }
            else
            {
                enshow = 1; /* ʹ����ʾ */
            }
        }

        lcd_show_char(x + (size / 2) * t, y, temp + '0', size, mode & 0X01, color);
    }
}

/**
 * @brief       ��ʾ�ַ���
 * @param       x,y         : ��ʼ����
 * @param       width,height: ������?
 * @param       size        : ѡ������ 12/16/24/32
 * @param       p           : �ַ����׵�ַ
 * @param       color       : �ַ�������ɫ;
 * @retval      ��
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' ')) /* �ж��ǲ��ǷǷ��ַ�! */
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)
            break; /* �˳� */

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

#endif

void GUI_Point(uint16_t x, uint16_t y) // ��һ�㣬x��yΪ����ֵ
{
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare();

    LCD_DataWrite(Fcolor & 0x00ff);
    LCD_DataWrite(Fcolor >> 8);
}

void GUI_Circle(uint16_t x, uint16_t y, uint16_t r) // ��ʾ����Բ
{
    Circle_Center_XY(x, y);
    Circle_Radius_R(r);
    Start_Circle_or_Ellipse();
}

void GUI_CircleFill(uint16_t x, uint16_t y, uint16_t r) // ��ʾʵ��Բ
{
    Circle_Center_XY(x, y);
    Circle_Radius_R(r);
    Start_Circle_or_Ellipse_Fill();
}

void GUI_Ellipse(uint16_t x, uint16_t y, uint16_t r1, uint16_t r2) // ��ʾ������Բ
{
    Circle_Center_XY(x, y);
    Ellipse_Radius_RxRy(r1, r2);
    Start_Circle_or_Ellipse();
}
/*******************************************************************************
 * ������  : ��ʾʵ����Բ
 * ����    : ��Һ��������ʾһ��ʵ����Բ
 * ����          : �趨ʵ����ԲԲ������ X Y ,���귶Χ����Һ���ֱ���
 *                ����ʵ����Բ�뾶R1���뾶R2
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_EllipseFill(uint16_t x, uint16_t y, uint16_t r1, uint16_t r2) // ��ʾʵ����Բ
{
    Circle_Center_XY(x, y);
    Ellipse_Radius_RxRy(r1, r2);
    Start_Circle_or_Ellipse_Fill();
}
/*******************************************************************************
 * ������  : ��ʾ����������
 * ����    : ��Һ��������ʾһ��ʵ�������� ,���귶Χ����Һ���ֱ���
 * ����          : ���ÿ��������ε�һ��������X1 Y1
 *               �����ÿ��������εڶ���������X2 Y2
 *								�����ÿ��������εڶ���������X3 Y3
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3) // ��ʾ����������
{
    Triangle_Point1_XY(x1, y1);
    Triangle_Point2_XY(x2, y2);
    Triangle_Point3_XY(x3, y3);
    Start_Triangle();
}
/*******************************************************************************
 * ������  : ��ʾʵ��������
 * ����    : ��Һ��������ʾһ��ʵ�������� ,���귶Χ����Һ���ֱ���
 * ����          : ����ʵ�������ε�һ��������X1 Y1
 *               ������ʵ�������εڶ���������X2 Y2
 *								������ʵ�������εڶ���������X3 Y3
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_Fill_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3) // ��ʾʵ��������
{
    Triangle_Point1_XY(x1, y1);
    Triangle_Point2_XY(x2, y2);
    Triangle_Point3_XY(x3, y3);
    Start_Triangle_Fill();
}
/*******************************************************************************
 * ������  : ��ʾ���ľ���
 * ����    : ��Һ��������ʾһ�����ľ��� ,���귶Χ����Һ���ֱ���
 * ����          : ���ÿ��ľ������Ͻǵ�һ��������
 *									���þ��εĳ�W�Ϳ�H
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_Rectangle(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h) // ��ʾ���ľ���
{
    Line_Start_XY(xs, ys);
    Line_End_XY(xs + w - 1, ys + h - 1);
    Start_Square();
}
/*******************************************************************************
 * ������  : ��ʾʵ�ľ���
 * ����    : ��Һ��������ʾһ��ʵ�ľ��� ,���귶Χ����Һ���ֱ���
 * ����          : ����ʵ�ľ������Ͻǵ�һ��������
 *									���þ��εĳ�W�Ϳ�H
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_RectangleFill(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h) // ��ʾʵ�ľ���
{
    Line_Start_XY(xs, ys);
    Line_End_XY(xs + w - 1, ys + h - 1);
    Start_Square_Fill();
}
/*******************************************************************************
 * ������  : ��ʾ����Բ�Ǿ���
 * ����    : ��Һ��������ʾһ������Բ�Ǿ��� �����귶Χ����Һ���ֱ���
 * ����          : ������ʾ����Բ�Ǿ������Ͻǵ�һ��������
 *									���ÿ���Բ�Ǿ��εĳ��Ϳ�
 *                 ����Բ��R ,RԲ�ǲ������ڳ�W���߿�H��һ��
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_Rectangle_R(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h, uint16_t r) // ��ʾ����Բ�Ǿ��Σ�rԲ�ǲ�������w����h��һ��
{
    Line_Start_XY(xs, ys);
    Line_End_XY(xs + w - 1, ys + h - 1);
    Ellipse_Radius_RxRy(r, r);
    Start_Circle_Square();
}
/*******************************************************************************
 * ������  : ��ʾʵ��Բ�Ǿ���
 * ����    : ��Һ��������ʾһ������Բ�Ǿ��� �����귶Χ����Һ���ֱ���
 * ����          : ������ʾʵ��Բ�Ǿ������Ͻǵ�һ��������
 *									����ʵ��Բ�Ǿ��εĳ��Ϳ�
 *                 ����Բ��R ,RԲ�ǲ������ڳ�W���߿�H��һ��
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_RectangleFill_R(uint16_t xs, uint16_t ys, uint16_t w, uint16_t h, uint16_t r) // ��ʾʵ��Բ�Ǿ��Σ�rԲ�ǲ�������w����h��һ��
{
    Line_Start_XY(xs, ys);
    Line_End_XY(xs + w - 1, ys + h - 1);
    Ellipse_Radius_RxRy(r, r);
    Start_Circle_Square_Fill();
}
/*******************************************************************************
 * ������  : ��ֱ��
 * ����    : ��Һ��������ʾһ��ֱ�� �����귶Χ����Һ���ֱ���
 * ����          : ����ֱ�ߵĵ�һ���������X1 Y1
 *									����ֱ�ߵĵڶ����������X2 Y2
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void GUI_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) // ��ʾֱ��
{
    Line_Start_XY(x1, y1);
    Line_End_XY(x2, y2);
    Start_Line();
}

/*******************************************************************************
 * ������  : ��ʾ128MB�ڵ�ͼƬ���ƶ�ͼ��
 * ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ�� ���귶Χ����Һ���ֱ���
 * ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼��������б���Ӧ��X,YΪ�ڸ�λ����ʾ������ ��layerΪָ����ͼ��
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Dis_Png_mix_128Mb(uint16_t picnum, uint16_t x, uint16_t y, uint16_t layer) // 128Mb����������ʾͼƬ��ָ��ͼ��
{
    unsigned long picx = 0, picy = 0, fadd = 0;
    unsigned char buf3[12];
    FLASH_Read_128Mb(buf3, picnum * 12, 12);

    fadd = (unsigned long)buf3[0];
    fadd = (fadd << 8) + buf3[1];
    fadd = (fadd << 8) + buf3[2];
    fadd = (fadd << 8) + buf3[3];

    picx = (unsigned long)buf3[4];
    picx = (picx << 8) + buf3[5];
    picx = (picx << 8) + buf3[6];
    picx = (picx << 8) + buf3[7];

    picy = (unsigned long)buf3[8];
    picy = (picy << 8) + buf3[9];
    picy = (picy << 8) + buf3[10];
    picy = (picy << 8) + buf3[11];

    if ((picx != 0) & (picy != 0) & (picnum < 200))
    {
        BTE_Destination_Color_16bpp();
        Enable_SFlash_SPI();
        Select_SFI_0();
        Select_SFI_DMA_Mode();
        Select_SFI_24bit_Address();
        Select_SFI_Waveform_Mode_3();
        Select_SFI_Dual_Mode0();
        SPI_Clock_Period(0);
        Canvas_Image_Start_address(layer);

        SFI_DMA_Destination_Start_Address(layer);
        Memory_XY_Mode();
        SFI_DMA_Source_Width(picx);
        SFI_DMA_Transfer_Width_Height(picx, picy);
        SFI_DMA_Destination_Upper_Left_Corner(x, y);
        SFI_DMA_Source_Start_Address(fadd);

        Start_SFI_DMA();
        Check_Busy_SFI_DMA();

        // Canvas_Image_Start_address(Layer1);
    }
}
/*******************************************************************************
 * ������  : ��ʾ1024MB�ڵ�ͼƬ
 * ����    : ��Һ��������ʾһ��ͼƬ
 * ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼��������б���Ӧ��X,YΪ�ڸ�λ����ʾ������
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Dis_Image_mix_1024Mb(uint16_t picnum, uint16_t x, uint16_t y) // 1024Mb����������ʾͼƬ����ǰ��Ļ
{
    unsigned char buf3[12];
    unsigned long picx = 0, picy = 0, fadd = 0;
    FLASH_Read_1024GMb(buf3, picnum * 12);

    fadd = (unsigned long)buf3[0];
    fadd = (fadd << 8) + buf3[1];
    fadd = (fadd << 8) + buf3[2];
    fadd = (fadd << 8) + buf3[3];

    picx = (unsigned long)buf3[4];
    picx = (picx << 8) + buf3[5];
    picx = (picx << 8) + buf3[6];
    picx = (picx << 8) + buf3[7];

    picy = (unsigned long)buf3[8];
    picy = (picy << 8) + buf3[9];
    picy = (picy << 8) + buf3[10];
    picy = (picy << 8) + buf3[11];

    if ((picx != 0) & (picy != 0) & (picnum < 200))
    {

        Select_SFI_0();
        Enable_SFlash_SPI();

        Select_SFI_DMA_Mode();
        Select_SFI_24bit_Address();
        Select_SFI_8_DummyRead();
        Memory_Linear_Mode();
        Select_SFI_Waveform_Mode_3();
        Select_SFI_Dual_Mode0();

        SPI_Clock_Period(1);
        nSS_Active();
        SPI_Master_FIFO_Data_Put(0x13);
        SPI_Master_FIFO_Data_Put(0xff);
        SPI_Master_FIFO_Data_Put((fadd / 2048) >> 8);
        SPI_Master_FIFO_Data_Put(fadd / 2048);
        nSS_Inactive();
        DelayMS(10);
        SPI_Clock_Period(0);

        SFI_DMA_Transfer_Number(picx * picy * 2);
        SFI_DMA_Destination_Start_Address(Layer3);

        Start_SFI_DMA();
        Check_Busy_SFI_DMA();

        BTE_Destination_Color_16bpp();
        BTE_Destination_Memory_Start_Address(Draw_Layer);
        BTE_Destination_Image_Width(lcdx);
        BTE_Destination_Window_Start_XY(x, y); // x,y
        BTE_Window_Size(picx, picy);

        BTE_S0_Color_16bpp();
        BTE_S0_Memory_Start_Address(Layer3);
        BTE_S0_Image_Width(picx);
        BTE_S0_Window_Start_XY(0, 0); // x,y

        BTE_ROP_Code(12);
        BTE_Operation_Code(2); // BTE move
        BTE_Enable();
        Check_BTE_Busy();
        // Canvas_Image_Start_address(0);
    }
}

/*******************************************************************************
 * ������  : ���ݲ�ͬ�Ĵ�����������ѡ��ͬ����ʾͼƬ����
 * ����    : ��Һ��������ʾһ��ͼƬ ,���귶Χ����Һ���ֱ���
 **����          :picnumΪ��¼�������������ͼƬ��ţ�����¼��������б���Ӧ��X,YΪ�ڸ�λ����ʾ������
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Dis_Image_Mix(uint16_t picnum, uint16_t x, uint16_t y)
{
    if (FLASHTYPE == 0) // ����Ϊ128Mb��Һ������ʾҺ���������ڲ���ͼƬ
        Dis_Image_Mix_128Mb(picnum, x, y);
    if (FLASHTYPE == 1) // ����Ϊ1024Mb��Һ������ʾҺ���������ڲ���ͼƬ
        Dis_Image_mix_1024Mb(picnum, x, y);
}

void Dis_Image_Mix_128Mb(uint16_t picnum, uint16_t x, uint16_t y) // 128Mb储存器，显示图片到当前屏幕
{
    unsigned long picx = 0, picy = 0, fadd = 0;
    unsigned char buf3[12];
    FLASH_Read_128Mb(buf3, picnum * 12, 12);

    fadd = (unsigned long)buf3[0];
    fadd = (fadd << 8) + buf3[1];
    fadd = (fadd << 8) + buf3[2];
    fadd = (fadd << 8) + buf3[3];

    picx = (unsigned long)buf3[4];
    picx = (picx << 8) + buf3[5];
    picx = (picx << 8) + buf3[6];
    picx = (picx << 8) + buf3[7];

    picy = (unsigned long)buf3[8];
    picy = (picy << 8) + buf3[9];
    picy = (picy << 8) + buf3[10];
    picy = (picy << 8) + buf3[11];

    if ((picx != 0) & (picy != 0) & (picnum < 200))
    {
        BTE_Destination_Color_16bpp();
        Enable_SFlash_SPI();
        Select_SFI_0();
        Select_SFI_DMA_Mode();
        Select_SFI_24bit_Address();
        Select_SFI_Waveform_Mode_3();
        Select_SFI_Dual_Mode0();
        SPI_Clock_Period(0);
        Canvas_Image_Start_address(Layer3);

        SFI_DMA_Destination_Start_Address(Layer3);
        Memory_XY_Mode();
        SFI_DMA_Source_Width(picx);
        SFI_DMA_Transfer_Width_Height(picx, picy);
        SFI_DMA_Destination_Upper_Left_Corner(x, y);
        SFI_DMA_Source_Start_Address(fadd);

        Start_SFI_DMA();
        Check_Busy_SFI_DMA();
        BTE_Destination_Color_16bpp();
        BTE_Destination_Memory_Start_Address(Draw_Layer);
        BTE_Destination_Image_Width(lcdx);
        BTE_Destination_Window_Start_XY(x, y);
        BTE_Window_Size(picx, picy);

        BTE_S0_Color_16bpp();
        BTE_S0_Memory_Start_Address(Layer3);
        BTE_S0_Image_Width(lcdx);
        BTE_S0_Window_Start_XY(x, y);

        BTE_ROP_Code(12);
        BTE_Operation_Code(2); // BTE move
        BTE_Enable();
        Check_BTE_Busy();
        Canvas_Image_Start_address(Draw_Layer);
    }
}

/*******************************************************************************
 * ������  : �Թ���ɫ��ʾ1024MB�ڵ�ͼƬ
 * ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ ,���귶Χ����Һ���ֱ���
 * ����    ��picnumΪ��¼�������������ͼƬ��ţ�����¼��������б���Ӧ��X,YΪ�ڸ�λ����ʾ������ ��colorΪ����ɫ
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Dis_Png_Mix(uint16_t picnum, uint16_t x, uint16_t y, uint16_t color)
{
    if (FLASHTYPE == 0) // ����Ϊ128Mb��Һ������ʾҺ���������ڲ���ͼƬ
        Dis_Png_mix_128Mb(picnum, x, y, color);
    if (FLASHTYPE == 1) // ����Ϊ1024Mb��Һ������ʾҺ���������ڲ���ͼƬ
        Dis_Png_mix_1024Mb(picnum, x, y, color);
}
/*******************************************************************************
* ������  : ��ʼ�����ֹ���
* ����    : ��ʼ�����ֹ���
* ����          : NONE

* ���         : None
* ����         : None
*******************************************************************************/
void cnconfig(void)
{
    Enable_SFlash_SPI();
    Select_SFI_1();

    Select_SFI_24bit_Address();
    Select_SFI_Waveform_Mode_3();
    Select_SFI_Dual_Mode1();
    SPI_Clock_Period(0);
}
/*******************************************************************************
 * ������  : ��ʾ����
 * ����    : ��Һ��������ʾ����
 * ����          : ����������ʾ����λ��X Y
 *				 tongtou:�������������Ƿ�ͨ͸
 *str:��ʾ����������
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Display_Text(uint16_t x, uint16_t y, unsigned char tongtou, unsigned char *str)
{
    Select_SFI_1();
    Select_SFI_Font_Mode();

    Select_SFI_Waveform_Mode_0();
    Select_SFI_0_DummyRead();
    Select_SFI_Single_Mode();
    SPI_Clock_Period(4); // Freq must setting <=20MHZ
    GTFont_Select_GT23L32S4W_GT23H32S4W();
    Set_GTFont_Decoder(1); // �������ַ����壬��ο�˵����
    Enable_SFlash_SPI();
    Memory_XY_Mode();

    if (tongtou == 0)
        Font_Background_select_Color();
    if (tongtou == 1)
        Font_Background_select_Transparency();
    Goto_Text_XY(x, y);
    Show_String(str);
}

/*******************************************************************************
 * ������  : ��������
 * ����    : ��������
 * ����          : 1����16����2����24����3����32����
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Set_Font(unsigned char font) // ��������
{
    switch (font)
    {
    case 0x01:
    {
        Font_Select_8x16_16x16();
        FONT = 1;
    }
    break;
    case 0x02:
    {
        Font_Select_12x24_24x24();
        FONT = 2;
    }
    break;
    case 0x03:
    {
        Font_Select_16x32_32x32();
        FONT = 3;
    }
    break;
    }
}
/*******************************************************************************
 * ������  : �������ּ��
 * ����    : �������ּ�ļ��
 * ����          : �������ּ����Ҽ��X
 *									�������ּ����¼��Y
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void Set_Font_Distance(uint16_t x, uint16_t y) // �������ּ��
{
    Font_Line_Distance(x);
    Set_Font_to_Font_Width(y);
}
/*******************************************************************************
 * ������  : ָ����Ļλ�÷�ɫ��ʾ
 * ����    : ��Һ��ָ��λ�÷�ɫ��ʾ
 * ����          : �������Ͻ�����X1 Y1
 *									�������½�����X2 Y2
 *
 * ���         : None
 * ����         : None
 *******************************************************************************/
void inverse(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) // ��Ļ������
{
    Memory_XY_Mode();
    BTE_Destination_Color_16bpp();
    BTE_Destination_Memory_Start_Address(Layer1);
    BTE_Destination_Image_Width(lcdx);
    BTE_Destination_Window_Start_XY(xs, ys);
    BTE_Window_Size(xe - xs, ye - ys);

    BTE_S0_Color_16bpp();
    BTE_S0_Memory_Start_Address(Layer1);
    BTE_S0_Image_Width(lcdx);
    BTE_S0_Window_Start_XY(xs, ys);

    BTE_ROP_Code(3);
    BTE_Operation_Code(2); // BTE move
    BTE_Enable();
    Check_BTE_Busy();
}

void Sel_Layer(unsigned long clayer, unsigned long dlayer) // clayer:��ǰͼ��  dlayer��д��ͼ��
{
    Canvas_Image_Start_address(dlayer);
    Draw_Layer = dlayer;
    Main_Image_Start_Address(clayer);
    Current_Layer = clayer;
}

void Nandflash_Config(void) // ���1024Mb ͼƬ��������ã�128Mb�Ĳ���Ҫ����
{
    unsigned char temp;

    Select_nSS_drive_on_xnsfcs0();

    nSS_Active();
    SPI_Master_FIFO_Data_Put(0xff); // spi nand reset
    nSS_Inactive();

    // configuration register/status register-2
    // read status register-2
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x0F); //
    SPI_Master_FIFO_Data_Put(0xB0); //
    temp = SPI_Master_FIFO_Data_Put(0xff);
    nSS_Inactive();
    temp &= 0xf7; // clear bit 3 to set BUF = 0
    temp |= 0x10; // set bit 4 to ECC-Enable
    // To write the status register bits,a standard write enable(06h)
    // instruction must have previously been executed
    nSS_Active();
    SPI_Master_FIFO_Data_Put(temp); //
    nSS_Inactive();
    // write status register-2

    nSS_Active();

    SPI_Master_FIFO_Data_Put(0x1F); //
    SPI_Master_FIFO_Data_Put(0xB0); //
    SPI_Master_FIFO_Data_Put(temp); //
    nSS_Inactive();
    DelayMS(10);
    nSS_Active();
    SPI_Master_FIFO_Data_Put(0x0F); //
    SPI_Master_FIFO_Data_Put(0xB0); //
    temp = SPI_Master_FIFO_Data_Put(0xff);
    nSS_Inactive();

    Select_nSS_drive_on_xnsfcs0();
}

void Geometric_Drawing(void)
{
    unsigned long i, j, h;
    unsigned long resx1, resy1, resx2, resy2, resx3, resy3;

    h = 0;
    do
    {
        resx1 = rand() % lcdx;
        resy1 = rand() % lcdy;

        resx2 = rand() % lcdx;
        resy2 = rand() % lcdy;

        resx3 = rand() % lcdx;
        resy3 = rand() % lcdy;

        i = rand() % 65536;
        Foreground_color_65k(i);

        Triangle_Point1_XY(resx1, resy1);
        Triangle_Point2_XY(resx2, resy2);
        Triangle_Point3_XY(resx3, resy3);

        j = rand() % 3;
        if (j)
            Start_Triangle();
        else
            Start_Triangle_Fill();
        DelayMS(1);
        h++;
    } while (h < 100);

    h = 0;
    do
    {
        resx1 = rand() % lcdx;
        resy1 = rand() % lcdy;

        resx2 = rand() % lcdx;
        resy2 = rand() % lcdy;

        resx3 = rand() % lcdx;
        resy3 = rand() % lcdy;

        i = rand() % 65536;
        Foreground_color_65k(i);

        Triangle_Point1_XY(resx1, resy1);
        Triangle_Point2_XY(resx2, resy2);
        Triangle_Point3_XY(resx3, resy3);

        j = rand() % 3;
        if (j)
            Start_Triangle();
        else
            Start_Triangle_Fill();
        h++;
    } while (h < 1000);

    //-----drawing circle & circle fill-----

    Foreground_color_65k(color_blue);

    Active_Window_WH(lcdx, lcdy);
    h = 0;
    do
    {
        i = rand() % 65536;
        Foreground_color_65k(i);

        resx1 = rand() % lcdx;
        resy1 = rand() % lcdy;
        i = rand() % 200;

        Circle_Center_XY(resx1, resy1);
        Circle_Radius_R(i);

        j = rand() % 3;
        if (j)
            Start_Circle_or_Ellipse();
        else
            Start_Circle_or_Ellipse_Fill();
        h++;
        DelayMS(1);
    } while (h < 100);

    h = 0;
    do
    {
        i = rand() % 65536;
        Foreground_color_65k(i);

        resx1 = rand() % lcdx;
        resy1 = rand() % lcdy;
        i = rand() % 200;

        Circle_Center_XY(resx1, resy1);
        Circle_Radius_R(i);

        j = rand() % 3;
        if (j)
            Start_Circle_or_Ellipse();
        else
            Start_Circle_or_Ellipse_Fill();
        h++;
    } while (h < 1000);
}

uint16_t GUI_ReadPoint(uint16_t x, uint16_t y) // ��һ�㣬x��yΪ����ֵ
{
    uint16_t readcolor;
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare();
    if (MPU_Interface == 2)
    {
        LCD_DataRead();
        readcolor = LCD_DataRead();
    }
    else
    {
        LCD_DataRead();
        LCD_DataRead();
        readcolor = LCD_DataRead();
        readcolor = (readcolor << 8) + LCD_DataRead();
    }

    return readcolor;
}

void Layer_Copy(unsigned long slayer, unsigned long dlayer, uint16_t sx, uint16_t sy, uint16_t dx, uint16_t dy, uint16_t w, uint16_t h)
{

    BTE_Destination_Color_16bpp();
    BTE_Destination_Memory_Start_Address(dlayer);
    BTE_Destination_Image_Width(lcdx);
    BTE_Destination_Window_Start_XY(dx, dy);
    BTE_Window_Size(w, h);

    BTE_S0_Color_16bpp();
    BTE_S0_Memory_Start_Address(slayer);
    BTE_S0_Image_Width(lcdx);
    BTE_S0_Window_Start_XY(sx, sy);

    BTE_ROP_Code(12);
    BTE_Operation_Code(2); // BTE move
    BTE_Enable();
    Check_BTE_Busy();
    Canvas_Image_Start_address(Layer1);
}

void PIP1(unsigned long layer, uint16_t dx, uint16_t dy, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h)
{
    Select_PIP1_Parameter();
    PIP_Image_Start_Address(layer);
    PIP_Image_Width(lcdx);
    PIP_Window_Image_Start_XY(sx, sy);
    PIP_Window_Width_Height(w, h);
    PIP_Display_Start_XY(dx, dy);
    Enable_PIP1();
}
/*******************************************************************************
 * ������  : ���л�����2
 * ����    : ��ʾ���л�����2
 * ����          :sx,syΪԴͼ������Ͻ����꣬dx,dyΪĿ��ͼ������Ͻ����꣬w,hΪҪ���л��Ŀ��͸߶�
 * ���         : None
 * ����         : None
 *******************************************************************************/
void PIP2(unsigned long layer, uint16_t dx, uint16_t dy, uint16_t sx, uint16_t sy, uint16_t w, uint16_t h)
{
    Select_PIP2_Parameter();
    PIP_Image_Start_Address(layer);
    PIP_Image_Width(lcdx);
    PIP_Window_Image_Start_XY(sx, sy);
    PIP_Window_Width_Height(w, h);
    PIP_Display_Start_XY(dx, dy);
    Enable_PIP2();
}

void test(uint16_t *buf, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
    Display_OFF();
    Canvas_Image_Start_address(0);
    Canvas_image_width(640);
    Active_Window_XY(0, 0);
    Active_Window_WH(640, 480);
    //  Select_Write_Data_Position();
    //  Memory_XY_Mode();

    LCD_WriteRAM_Prepare();
    Check_BTE_Busy();

    for (uint16_t i = 0; i < width * height; i++)
    {
        LCD->LCD_RAM = buf[i];
    }
    Main_Image_Start_Address(0);
    Main_Image_Width(640);
    Main_Window_Start_XY(0, 0);
    Display_ON();
}
