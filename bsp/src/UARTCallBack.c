/*
 * UARTCallBack.c
 *
 *  Created on: 29 Nov 2021
 *      Author: usr_tunnerk
 */

#include "gsm.h"
#include "modbus.h"
#include "main.h"

extern int rxFlag;
extern int msgRecv;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Clear all the error flags for the next UART receiption */
	rxFlag = 0;
	__HAL_UART_CLEAR_OREFLAG(huart);
	__HAL_UART_CLEAR_NEFLAG(huart);
	__HAL_UART_CLEAR_FEFLAG(huart);
	__HAL_UART_DISABLE_IT(huart, UART_IT_ERR);
	if(gHandler->port == huart)
	{
		gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr] = gHandler->dataRX[0];

		gsm_checkMessage();
	}
	/*if(gHandler->port == huart)
	{
		gsm_bufferAdd(&(gHandler->cmd), gHandler->dataRX);
		if(gsm_checkMessage(&(gHandler->cmd)) == 0)
		{
			msgRecv = 1;
			return;
		}
		else
		{
			HAL_UART_Receive_IT(gHandler->port, (uint8_t *)gHandler->dataRX, 1);
		}
	}*/
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


