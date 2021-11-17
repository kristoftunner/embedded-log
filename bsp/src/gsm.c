/*
 * gsm.c
 *
 *  Created on: 17 Nov 2021
 *      Author: usr_tunnerk
 */
#include <string.h>
#include <stdint.h>
#include "gsm.h"

#include "main.h"

extern UART_HandleTypeDef huart8;

int MC90_sendAT(struct MC60_cmd cmd)
{
	uint8_t txBuffer[100];
	uint8_t rxBuffer[100];
	strcpy(txBuffer, "AT+");
	cmd.msgLength += 3;
	strcat(txBuffer, cmd.cmd);
	cmd.msgLength += strlen(cmd.cmd);

	if(cmd.commandType==write)
	{
		strcat(txBuffer,"=");
		strcat(txBuffer, cmd.writeCmd);
		cmd.msgLength += strlen(cmd.writeCmd) + 1;
	}

	strcat(txBuffer,"\r");
	cmd.msgLength += 1;

	HAL_UART_Transmit(&huart8, (uint8_t*)txBuffer, cmd.msgLength, 1000);

	HAL_UART_Receive(&huart8, (uint8_t*)rxBuffer, cmd.responseLengt, 1000);

	if(strncmp(rxBuffer+cmd.offsetOK,"OK",2) == 0)
	{
		return 0;
	}

	return -1;
}
