#include "ili9163.h"
#include <stdio.h> // printf
#include <stdarg.h> // va_list, va_start, va_arg, va_end
#include "main.h"
#include "cmsis_os2.h"
#include "stm32f7xx_hal_dma.h"

/* Callback function from SPI DMA transfer*/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_SPI_DMAStop(iHandler->port);
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
	//HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
}

/* Error callback just in case.. */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	__NOP();
}

/* DMA callback: 
* transfering data from touchgfx buffer to driver buffer 
* have to swap the two bytes because the SPI DMA sends the frame data
* in little-endian format
*/
static void ILI9163_DMA_Callback(DMA_HandleTypeDef *DmaHandle)
{
	for(int row = 0; row < ILI9163_HEIGHT; row++)
	{
		for(int col = 0; col < ILI9163_WIDTH; col++)
		{
			uint16_t temp;
			temp = iHandler->frameBuff[row*ILI9163_WIDTH + col];
			iHandler->frameBuff[row*ILI9163_WIDTH + col] = (temp >> 8) | (temp << 8);
		}
	}
	ILI9163_renderFb(&(iHandler->frameBuff));
}

/* Init the handler structure */
void ILI9163_initDriver(ili_handler *handler)
{
	iHandler = handler;
	for(int i = 0; i <sizeof(iHandler->frameBuff)/sizeof(iHandler->frameBuff[0]); i++)
	{
		iHandler->frameBuff[i] = 0;
	}
	HAL_DMA_RegisterCallback(iHandler->dma, HAL_DMA_XFER_CPLT_CB_ID, ILI9163_DMA_Callback);
}

/* Start transferring data from touchgfx framebuffer to driver framebuffer*/
void ILI9163_getFrameBuffer(uint8_t *src)
{
	HAL_StatusTypeDef stat = 0;
	stat = HAL_DMA_Start_IT(iHandler->dma, (uint32_t)src, (uint32_t)&(iHandler->frameBuff), sizeof(iHandler->frameBuff));
}

/* Send command to the ILI9163 chip */
void ILI9163_writeCommand(uint8_t address) {
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 0);
	HAL_GPIO_WritePin(iHandler->dPort, iHandler->dPin, 0);

	HAL_SPI_Transmit(iHandler->port, &address, 1, 10);

	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
}

/* Send 8bit data/parameter of the command */
void ILI9163_writeData(uint8_t data) {
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 0);
	HAL_GPIO_WritePin(iHandler->dPort, iHandler->dPin, 1);

	HAL_SPI_Transmit(iHandler->port, &data, 1, 10);

	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
}

/* Send 16bit data/parameter of the command */
void ILI9163_writeData16(uint16_t word) {
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 0);
	HAL_GPIO_WritePin(iHandler->dPort, iHandler->dPin, 1);

	uint8_t data [2] = {(word >> 8) & 0x00FF, word & 0x00FF};
	HAL_SPI_Transmit(iHandler->port, data, 2, 10);

	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
}

/* set ILI9163 gram end and begin adresses of the next display refreshing*/
void ILI9163_setAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2) {
	ILI9163_writeCommand(ILI9163_CMD_SET_COLUMN_ADDRESS);
	ILI9163_writeData16(x1);
	ILI9163_writeData16(x2);

	ILI9163_writeCommand(ILI9163_CMD_SET_PAGE_ADDRESS);
	ILI9163_writeData16(y1);
	ILI9163_writeData16(y2);

	ILI9163_writeCommand(ILI9163_CMD_WRITE_MEMORY_START);
}

/* Reset the chip */
void ILI9163_reset(void)
{
	HAL_GPIO_WritePin(iHandler->rstPort, iHandler->rstPin, 0);
	HAL_Delay(50);

	HAL_GPIO_WritePin(iHandler->rstPort, iHandler->rstPin, 1);
	HAL_Delay(100);
}

/* Initialization of the ILI9163 chip */
void ILI9163_init(int rotation) {
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 1);
	HAL_GPIO_WritePin(iHandler->rstPort, iHandler->rstPin, 1);

	ILI9163_reset(); // Hardware reset the LCD

	ILI9163_writeCommand(ILI9163_CMD_EXIT_SLEEP_MODE);
	HAL_Delay(5); // Wait for the screen to wake up

	ILI9163_writeCommand(ILI9163_CMD_SET_PIXEL_FORMAT);
	ILI9163_writeData(0x05); // 16 bpp

	ILI9163_writeCommand(ILI9163_CMD_SET_GAMMA_CURVE);
	ILI9163_writeData(0x04); // Gamma curve 3

	ILI9163_writeCommand(ILI9163_CMD_GAM_R_SEL);
	ILI9163_writeData(0x01); // Gamma curve enable

	ILI9163_writeCommand(ILI9163_CMD_POSITIVE_GAMMA_CORRECT);
	ILI9163_writeData(0x3f);
	ILI9163_writeData(0x25);
	ILI9163_writeData(0x1c);
	ILI9163_writeData(0x1e);
	ILI9163_writeData(0x20);
	ILI9163_writeData(0x12);
	ILI9163_writeData(0x2a);
	ILI9163_writeData(0x90);
	ILI9163_writeData(0x24);
	ILI9163_writeData(0x11);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);

	ILI9163_writeCommand(ILI9163_CMD_NEGATIVE_GAMMA_CORRECT);
	ILI9163_writeData(0x20);
	ILI9163_writeData(0x20);
	ILI9163_writeData(0x20);
	ILI9163_writeData(0x20);
	ILI9163_writeData(0x05);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x15);
	ILI9163_writeData(0xa7);
	ILI9163_writeData(0x3d);
	ILI9163_writeData(0x18);
	ILI9163_writeData(0x25);
	ILI9163_writeData(0x2a);
	ILI9163_writeData(0x2b);
	ILI9163_writeData(0x2b);
	ILI9163_writeData(0x3a);


	ILI9163_writeCommand(ILI9163_CMD_FRAME_RATE_CONTROL1);
	ILI9163_writeData(0x08); // DIVA = 8
	ILI9163_writeData(0x02); // VPA = 8

	ILI9163_writeCommand(ILI9163_CMD_FRAME_RATE_CONTROL2);
	ILI9163_writeData(0x08); // DIVA = 8
	ILI9163_writeData(0x02); // VPA = 8

	ILI9163_writeCommand(ILI9163_CMD_FRAME_RATE_CONTROL3);
	ILI9163_writeData(0x08); // DIVA = 8
	ILI9163_writeData(0x02); // VPA = 8

	ILI9163_writeCommand(ILI9163_CMD_DISPLAY_INVERSION);
	ILI9163_writeData(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)

	/* This bit may cause minor compatibility issues, so it's commented out. Beware.
	ILI9163_writeCommand(ILI9163_CMD_POWER_CONTROL1);
	ILI9163_writeData(0x0a); // VRH = 10:  GVDD = 4.30
	ILI9163_writeData(0x02); // VC = 2: VCI1 = 2.65
	ILI9163_writeCommand(ILI9163_CMD_POWER_CONTROL2);
	ILI9163_writeData(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1
	ILI9163_writeCommand(ILI9163_CMD_VCOM_CONTROL1);
	ILI9163_writeData(0x24); // VMH = 80: VCOMH voltage = 4.5
	ILI9163_writeData(0x48); // VML = 91: VCOML voltage = -0.225
	ILI9163_writeCommand(ILI9163_CMD_VCOM_OFFSET_CONTROL);
	ILI9163_writeData(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML
	*/

	ILI9163_writeCommand(ILI9163_CMD_SET_COLUMN_ADDRESS);
	ILI9163_writeData(0x00); // XSH
	ILI9163_writeData(0x00); // XSL
	ILI9163_writeData(0x00); // XEH
	ILI9163_writeData(ILI9163_HEIGHT-1); // XEL (128 pixels x)

	ILI9163_writeCommand(ILI9163_CMD_SET_PAGE_ADDRESS);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);
	ILI9163_writeData(0x00);
	ILI9163_writeData(ILI9163_WIDTH-1); // 160 pixels y

	ILI9163_writeCommand(ILI9163_CMD_SET_ADDRESS_MODE);
	if(rotation)
		ILI9163_writeData(0x80 | 0x20);
	else
		ILI9163_writeData(0x40 | 0x20);

	ILI9163_writeCommand(ILI9163_CMD_ENTER_NORMAL_MODE);
	ILI9163_writeCommand(ILI9163_CMD_SET_DISPLAY_ON);
	ILI9163_writeCommand(ILI9163_CMD_WRITE_MEMORY_START);

}

/* render function used to render touchgfx framebuffer */
void ILI9163_renderFb(uint16_t *framebuff)
{
	ILI9163_setAddress(0, 0, ILI9163_WIDTH, ILI9163_HEIGHT);
	HAL_GPIO_WritePin(iHandler->csPort, iHandler->csPin, 0);
	HAL_GPIO_WritePin(iHandler->dPort, iHandler->dPin, 1);
	HAL_SPI_Transmit_DMA(iHandler->port, (uint8_t*)framebuff, BUFSIZE*2);
}
