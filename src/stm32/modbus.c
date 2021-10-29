#include "modbus.h"
#include "main.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_gpio.h"

extern UART_HandleTypeDef huart7;

/**/
void Modbus_init()
{
    //init 
}

MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs)
{
	MB_StatusTypeDef ret;
	uint8_t rxBuffer[256];
    // Construct the message
    struct ModBus_message_RHR msg;
    msg.SlaveAddr = SlaveID;
    msg.FunctionCode = 0x03;
    msg.StartAddr = StartAddress;
    msg.NumberOfRegs = NumberOfRegs;

    msg.MsgCRC = CRC16((volatile unsigned char*)&msg, 6);

    // Sending the message
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_SET);
    ret = HAL_UART_Transmit(&huart7,(uint8_t*)&msg, sizeof(msg)/sizeof(uint8_t),5000);
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_RESET);

    /*HAL_UART_Receive(&huart7, (uint8_t *)rxBuffer, 4 + NumberOfRegs*2,5000);

    if(rxBuffer[1] == 0x83)
    {
    	ret = MB_ERROR;
    	return ret;
    }

    struct Modbus_message_RHR_response resp;
    resp.SlaveAddr = rxBuffer[0];
    resp.FunctionCode = rxBuffer[1];
    resp.ByteCount = rxBuffer[2];
    resp.payload = &rxBuffer[3];*/
}
