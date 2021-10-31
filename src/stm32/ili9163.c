/*
 * ili9613.c
 *
 *  Created on: Oct 31, 2021
 *      Author: kristoft
 */


#include "ili9163.h"
#include "interface.h"


void Ili9163_Write_Command(uint8_t cmd)
{
    Ili_Reset_Cs();
    Ili_Reset_D();
    Ili_Spi_Send(cmd);
    Ili_Set_Cs();
}

void Ili9163_Write_Data(uint8_t data)
{
    Ili_Reset_Cs();
    Ili_Set_D();
    Ili_Spi_Send(data);
    Ili_Set_Cs();
}

void Ili9163_Write_Data16(uint16_t data)
{
    Ili_Reset_Cs();
    Ili_Set_D();
    Ili_Spi_Send((data >> 8) & 0x00ff);
    Ili_Spi_Send(data & 0x00ff);
    Ili_Set_Cs();
}

/*Write column, page begin and end address*/
void Ili9163_Set_Address(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{
    Ili9163_Write_Command(ILI9163_CMD_SET_COLUMN_ADDRESS);
    Ili9163_Write_Data16(x1);
    Ili9163_Write_Data16(x2);

    Ili9163_Write_Command(ILI9163_CMD_SET_PAGE_ADDRESS);
    Ili9163_Write_Data16(y1);
    Ili9163_Write_Data16(y2);

    /*Start memory write*/
    Ili9163_Write_Command(ILI9163_CMD_WRITE_MEMORY_START);

}

void Ili9163_Reset()
{
    Ili_dly_ms(50);
    Ili_Reset_HWRST();
    Ili_dly_ms(50);
    Ili_Set_HWRST();
    Ili_dly_ms(120);
}

void Ili9163_Init(struct Ili_Handler ili)
{
    Ili_Set_Cs();
    Ili_Set_HWRST();

    /*Hardware reset of the display*/
    Ili9163_Reset();
    Ili_dly_ms(100);

    Ili9163_Write_Command(ILI9163_CMD_SOFT_RESET);
    Ili_dly_ms(500);

    Ili9163_Write_Command(ILI9163_CMD_EXIT_SLEEP_MODE);
    Ili_dly_ms(5); // Wait for the screen to wake up

    Ili9163_Write_Command(ILI9163_CMD_SET_PIXEL_FORMAT);
    Ili9163_Write_Data(0x05); // 16 bits per pixel

    Ili9163_Write_Command(ILI9163_CMD_SET_GAMMA_CURVE);
    Ili9163_Write_Data(0x04); // Select gamma curve 3

    Ili9163_Write_Command(ILI9163_CMD_GAM_R_SEL);
    Ili9163_Write_Data(0x01); // Gamma adjustment enabled
    Ili_dly_ms(1);

    Ili9163_Write_Command(ILI9163_CMD_ENTER_NORMAL_MODE);

    Ili9163_Write_Command(ILI9163_CMD_POSITIVE_GAMMA_CORRECT);
    Ili9163_Write_Data(0x3f); // 1st Parameter
    Ili9163_Write_Data(0x25); // 2nd Parameter
    Ili9163_Write_Data(0x1c); // 3rd Parameter
    Ili9163_Write_Data(0x1e); // 4th Parameter
    Ili9163_Write_Data(0x20); // 5th Parameter
    Ili9163_Write_Data(0x12); // 6th Parameter
    Ili9163_Write_Data(0x2a); // 7th Parameter
    Ili9163_Write_Data(0x90); // 8th Parameter
    Ili9163_Write_Data(0x24); // 9th Parameter
    Ili9163_Write_Data(0x11); // 10th Parameter
    Ili9163_Write_Data(0x00); // 11th Parameter
    Ili9163_Write_Data(0x00); // 12th Parameter
    Ili9163_Write_Data(0x00); // 13th Parameter
    Ili9163_Write_Data(0x00); // 14th Parameter
    Ili9163_Write_Data(0x00); // 15th Parameter

    Ili9163_Write_Command(ILI9163_CMD_NEGATIVE_GAMMA_CORRECT);
    Ili9163_Write_Data(0x20); // 1st Parameter
    Ili9163_Write_Data(0x20); // 2nd Parameter
    Ili9163_Write_Data(0x20); // 3rd Parameter
    Ili9163_Write_Data(0x20); // 4th Parameter
    Ili9163_Write_Data(0x05); // 5th Parameter
    Ili9163_Write_Data(0x00); // 6th Parameter
    Ili9163_Write_Data(0x15); // 7th Parameter
    Ili9163_Write_Data(0xa7); // 8th Parameter
    Ili9163_Write_Data(0x3d); // 9th Parameter
    Ili9163_Write_Data(0x18); // 10th Parameter
    Ili9163_Write_Data(0x25); // 11th Parameter
    Ili9163_Write_Data(0x2a); // 12th Parameter
    Ili9163_Write_Data(0x2b); // 13th Parameter
    Ili9163_Write_Data(0x2b); // 14th Parameter
    Ili9163_Write_Data(0x3a); // 15th Parameter

    Ili9163_Write_Command(ILI9163_CMD_FRAME_RATE_CONTROL1);
    Ili9163_Write_Data(0x08); // DIVA = 8
    Ili9163_Write_Data(0x08); // VPA = 8

    Ili9163_Write_Command(ILI9163_CMD_DISPLAY_INVERSION);
    Ili9163_Write_Data(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)

    Ili9163_Write_Command(ILI9163_CMD_POWER_CONTROL1);
    Ili9163_Write_Data(0x0a); // VRH = 10:  GVDD = 4.30
    Ili9163_Write_Data(0x02); // VC = 2: VCI1 = 2.65

    Ili9163_Write_Command(ILI9163_CMD_POWER_CONTROL2);
    Ili9163_Write_Data(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

    Ili9163_Write_Command(ILI9163_CMD_VCOM_CONTROL1);
    Ili9163_Write_Data(0x50); // VMH = 80: VCOMH voltage = 4.5
    Ili9163_Write_Data(0x5b); // VML = 91: VCOML voltage = -0.225

    Ili9163_Write_Command(ILI9163_CMD_VCOM_OFFSET_CONTROL);
    Ili9163_Write_Data(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML

    Ili9163_Write_Command(ILI9163_CMD_SET_COLUMN_ADDRESS);
    Ili9163_Write_Data(0x00); // XSH
    Ili9163_Write_Data(0x00); // XSL
    Ili9163_Write_Data(0x00); // XEH
    Ili9163_Write_Data(0x7f); // XEL (128 pixels x)

    Ili9163_Write_Command(ILI9163_CMD_SET_PAGE_ADDRESS);
    Ili9163_Write_Data(0x00);
    Ili9163_Write_Data(0x00);
    Ili9163_Write_Data(0x00);
    Ili9163_Write_Data(0x7f); // 128 pixels y

    // Select display orientation
    Ili9163_Set_Rotation(ili.rot);

    // Set the display to on
    Ili9163_Write_Command(ILI9163_CMD_SET_DISPLAY_ON);
    Ili9163_Write_Command(ILI9163_CMD_WRITE_MEMORY_START);
}

uint8_t Ili9163_Read_ID1()
{
	Ili_Reset_Cs();
	Ili_Reset_D();
	Ili_Spi_Send(ILI9163_CMD_READ_ID1);
    uint8_t temp = Ili_Spi_Read();
	Ili_Set_Cs();
    return temp;
}

void Ili9163_Set_Rotation(enum Rotation rotation)
{
    Ili9163_Write_Command(ILI9163_CMD_SET_ADDRESS_MODE);
    Ili9163_Write_Data(rotation);
}

void Ili9163_Draw_Pixel(struct Ili_Handler ili, uint8_t x, uint8_t y, uint16_t color)
{
	if ((x < 0) || (x >= ili.Width) || (y < 0) || (y >= ili.Height)) return;
	Ili9163_Set_Address(x, y, x + 1, y+1);
	Ili9163_Write_Data16(color);
}

void Ili9163_Draw_Rect(struct Ili_Handler ili, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    if ((x >= ili.Width) || (y >= ili.Height)) return;
	if ((x + w - 1) >= ili.Width) w = ili.Width - x;
	if ((y + h - 1) >= ili.Height) h = ili.Height - y;
	Ili9163_Set_Address(x, y, x + w - 1, y + h - 1);
	for (y = h; y > 0; y--)
		for (x = w; x > 0; x--)
			Ili9163_Write_Data16(color);
}
