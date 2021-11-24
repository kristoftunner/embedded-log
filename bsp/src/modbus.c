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

MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs, struct Modbus_messageRHRResponse *response)
{
	MB_StatusTypeDef ret;
	uint8_t rxBuffer[256];
	for(int i = 0; i < 256; i++)
	{
		rxBuffer[i] = 0;
	}
    // Construct the message
    struct Modbus_messageRHR msg;
    msg.SlaveAddr = SlaveID;
    msg.FunctionCode = 0x03;
    msg.StartAddr = (StartAddress << 8) | (StartAddress >> 8);
    msg.NumberOfRegs = (NumberOfRegs << 8) | (NumberOfRegs >> 8);;
    msg.MsgCRC = CRC16((volatile unsigned char*)&msg, 6);

    // Sending the message
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_SET);
    ret = HAL_UART_Transmit(&huart7,(uint8_t*)&msg, sizeof(msg)/sizeof(uint8_t),5000);
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_RESET);
    HAL_Delay(1);

    // bytes: 1 function code, 1 slave addr, 1 byte count, N bytes, 2 CRC bytes
    HAL_UART_Receive(&huart7, (uint8_t *)rxBuffer, 6 + NumberOfRegs*2,100);

    if(rxBuffer[1] == 0x83)
    {
    	ret = MB_ERROR;
    	return ret;
    }


    response->SlaveAddr = rxBuffer[1];
    response->FunctionCode = rxBuffer[2];
    response->ByteCount = rxBuffer[3];
    for(int i = 0; i < response->ByteCount/2; i++)
    {
    	response->payload[i] = (rxBuffer[4+i*2] << 8) | rxBuffer[5+i*2];
    }

    response->crc = CRC16((volatile unsigned char*)(rxBuffer+1), 3 + response->ByteCount);

    if(!((response->crc & 0xff) == rxBuffer[4 + response->ByteCount]) && ((response->crc >> 8) == rxBuffer[5 + response->ByteCount]))
    {
    	ret = MB_ERROR;
    	return ret;
    }

    return ret;
}
