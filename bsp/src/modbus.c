#include "modbus.h"
#include "main.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_gpio.h"

extern UART_HandleTypeDef huart7;

static int rxFlag = 0;
/**/
void Modbus_init()
{
    //init
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rxFlag = 0;
	__HAL_UART_CLEAR_OREFLAG(huart);
	__HAL_UART_CLEAR_NEFLAG(huart);
	__HAL_UART_CLEAR_FEFLAG(huart);
	__HAL_UART_DISABLE_IT(huart, UART_IT_ERR);
}

/*void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

	//HAL_UART_Receive_IT(&huart7,(uint8_t *)&rxBuffer[0], 5 + 80*2);
}*/

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	__HAL_UART_CLEAR_OREFLAG(huart);
	rxFlag = 0;
	__NOP();
}
MB_StatusTypeDef Modbus_RHR(uint8_t SlaveID, uint16_t StartAddress, uint16_t NumberOfRegs, struct Modbus_messageRHRResponse *response)
{
	MB_StatusTypeDef ret;
	HAL_StatusTypeDef halStat;
	uint8_t rxBuffer[256];

	for(int i = 0; i < 256; i++)
	{
		rxBuffer[i] = 0;
	}
    // Construct the message
    struct Modbus_messageRHR msg;
    msg.slaveAddr = SlaveID;
    msg.functionCode = 0x03;
    msg.startAddr = (StartAddress << 8) | (StartAddress >> 8);
    msg.numberOfRegs = (NumberOfRegs << 8) | (NumberOfRegs >> 8);;
    msg.msgCRC = CRC16((volatile unsigned char*)&msg, 6);

    // Sending the message
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_SET);
    ret = HAL_UART_Transmit(&huart7,(uint8_t*)&msg, sizeof(msg)/sizeof(uint8_t),100);
    HAL_GPIO_WritePin(UART7_DE_GPIO_Port,UART7_DE_Pin,GPIO_PIN_RESET);

    /* Clear the OREFLAG, beacuse the data register of the UART reciever contains
     * a previous packet last byte, and clearing this flag flushes the data register*/
    rxFlag = 1;
	__HAL_UART_CLEAR_OREFLAG(&huart7);
	uint8_t temp = (uint8_t)(huart7.Instance->RDR);
    /* bytes: 1 function code, 1 slave addr, 1 byte count, N bytes, 2 CRC bytes */
    halStat = HAL_UART_Receive_IT(&huart7,(uint8_t *)rxBuffer, 5 + NumberOfRegs*2);

    while(rxFlag == 1);


    if(rxBuffer[1] == 0x83)
    {
    	ret = MB_ERROR;
    	return ret;
    }

    response->slaveAddr = rxBuffer[0];
    response->functionCode = rxBuffer[1];
    response->byteCount = rxBuffer[2];
    for(int i = 0; i < response->byteCount/2; i++)
    {
    	response->payload[i] = (rxBuffer[3+i*2] << 8) | rxBuffer[4+i*2];
    }

    response->crc = CRC16((volatile unsigned char*)(rxBuffer), 3 + response->byteCount);

    unsigned int temp1 = response->crc & 0xff;
    unsigned int temp2 = response->crc >> 8;
    unsigned int temp3 = rxBuffer[3+ response->byteCount];
    unsigned int temp4 = rxBuffer[4+ response->byteCount];


    if(((response->crc & 0xff) == rxBuffer[3 + response->byteCount]) && ((response->crc >> 8) == rxBuffer[4 + response->byteCount]))
    {
    	return 0;
    }

    ret = MB_ERROR;
    return ret;
}
