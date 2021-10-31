#include "ili9613.h"
#include "interface.h"


void Write_Command(uint8_t cmd)
{
    Ili_Reset_Cs();
    Ili_Reset_D();
    Ili_Spi_Send(cmd);
    Ili_Set_Cs();
}

void Write_Data(uint8_t data)
{
    Ili_Reset_Cs();
    Ili_Set_D();
    Ili_Spi_Send(data);
    Ili_Set_Cs();
}

void Write_Data16(uint16_t data)
{
    Ili_Reset_Cs();
    Ili_Set_D();
    Ili_Spi_Send((data >> 8) & 0x00ff);
    Ili_Spi_Send(data & 0x00ff);
    Ili_Spi_Cs();
}

/*Write column, page begin and end address*/
void Set_Address(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{
    Write_Command(ILI9163_CMD_SET_COLUMN_ADDRESS);
    Write_Data16(x1);
    Write_Data16(x2);

    Write_Command(ILI9163-CMD_SET_PAGE_ADDRESS);
    Write_Data16(y1);
    Write_Data16(y2);

    /*Start memory write*/
    Write_Command(ILI9163_CMD_WRITE_MEMORY_START);

}

void Reset()
{
    Ili_dly_ms(50);
    Ili_Reset_HWRST();
    Ili_dly_ms(50);
    Ili_Set_HWRST();
    Ili_dly_ms(120);
}

void Init()
{
    Ili_Set_Cs();
    Ili_Set_HWRST();

    /*Hardware reset of the display*/
    Reset();
    
    Write_command(ILI9163_CMD_EXIT_SLEEP_MODE);
    Ili_dly_ms(5); // Wait for the screen to wake up
    
    Write_Command(ILI9163_CMD_SET_PIXEL_FORMAT);
    Write_Data(0x05); // 16 bits per pixel
   
    Write_Command(ILI9163_CMD_SET_GAMMA_CURVE);
    Write_Data(0x04); // Select gamma curve 3
    
    Write_Command(ILI9163_CMD_GAM_R_SEL);
    Write_Data(0x01); // Gamma adjustment enabled
    
    Write_Command(ILI9163_CMD_POSITIVE_GAMMA_CORRECT);
    Write_Data(0x3f); // 1st Parameter
    Write_Data(0x25); // 2nd Parameter
    Write_Data(0x1c); // 3rd Parameter
    Write_Data(0x1e); // 4th Parameter
    Write_Data(0x20); // 5th Parameter
    Write_Data(0x12); // 6th Parameter
    Write_Data(0x2a); // 7th Parameter
    Write_Data(0x90); // 8th Parameter
    Write_Data(0x24); // 9th Parameter
    Write_Data(0x11); // 10th Parameter
    Write_Data(0x00); // 11th Parameter
    Write_Data(0x00); // 12th Parameter
    Write_Data(0x00); // 13th Parameter
    Write_Data(0x00); // 14th Parameter
    Write_Data(0x00); // 15th Parameter
    
    Write_Command(ILI9163_CMD_NEGATIVE_GAMMA_CORRECT);
    Write_Data(0x20); // 1st Parameter
    Write_Data(0x20); // 2nd Parameter
    Write_Data(0x20); // 3rd Parameter
    Write_Data(0x20); // 4th Parameter
    Write_Data(0x05); // 5th Parameter
    Write_Data(0x00); // 6th Parameter
    Write_Data(0x15); // 7th Parameter
    Write_Data(0xa7); // 8th Parameter
    Write_Data(0x3d); // 9th Parameter
    Write_Data(0x18); // 10th Parameter
    Write_Data(0x25); // 11th Parameter
    Write_Data(0x2a); // 12th Parameter
    Write_Data(0x2b); // 13th Parameter
    Write_Data(0x2b); // 14th Parameter
    Write_Data(0x3a); // 15th Parameter
    
    Write_Command(ILI9163_CMD_FRAME_RATE_CONTROL1);
    Write_Data(0x08); // DIVA = 8
    Write_Data(0x08); // VPA = 8
    
    Write_Command(ILI9163_CMD_DISPLAY_INVERSION);
    Write_Data(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)
   
    Write_Command(ILI9163_CMD_POWER_CONTROL1);
    Write_Data(0x0a); // VRH = 10:  GVDD = 4.30
    Write_Data(0x02); // VC = 2: VCI1 = 2.65
      
    Write_Command(ILI9163_CMD_POWER_CONTROL2);
    Write_Data(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

    Write_Command(ILI9163_CMD_VCOM_CONTROL1);
    Write_Data(0x50); // VMH = 80: VCOMH voltage = 4.5
    Write_Data(0x5b); // VML = 91: VCOML voltage = -0.225
    
    Write_Command(ILI9163_CMD_VCOM_OFFSET_CONTROL);
    Write_Data(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML
    
    Write_Command(ILI9163_CMD_SET_COLUMN_ADDRESS);
    Write_Data(0x00); // XSH
    Write_Data(0x00); // XSL
    Write_Data(0x00); // XEH
    Write_Data(0x7f); // XEL (128 pixels x)
   
    Write_Command(ILI9163_CMD_SET_PAGE_ADDRESS);
    Write_Data(0x00);
    Write_Data(0x00);
    Write_Data(0x00);
    Write_Data(0x7f); // 128 pixels y
    
    // Select display orientation
    Rotation rot = ROT0;
    Set_Rotation(rot);

    // Set the display to on
    Write_Command(ILI9163_CMD_SET_DISPLAY_ON);
    Write_Command(ILI9163_CMD_WRITE_MEMORY_START);
}

void Set_Rotation(Rotationt rotation)
{
    Write_Command(ILI9163_CMD_SET_ADDRESS_MODE);
    Write_Data(rotation);
}

