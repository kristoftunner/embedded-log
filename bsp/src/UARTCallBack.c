/*
 * UARTCallBack.c
 *
 *  Created on: 29 Nov 2021
 *      Author: usr_tunnerk
 */

#include "gsm.h"
#include "modbus.h"
#include "main.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Clear all the error flags for the next UART receiption */
	__HAL_UART_CLEAR_OREFLAG(huart);
	__HAL_UART_CLEAR_NEFLAG(huart);
	__HAL_UART_CLEAR_FEFLAG(huart);
	__HAL_UART_DISABLE_IT(huart, UART_IT_ERR);
	if(gHandler->port == huart)
	{
		if(gHandler->cmd.dataReadyFlag == 0 && ((gHandler->mqttPubSubStatus == MQTT_INITIAL) || gHandler->mqttPubSubStatus == MQTT_PUBLISHING))
			gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr] = gHandler->dataRX[0];
		else
			gHandler->cmd.subrscribeBuffer[gHandler->cmd.subscribeDataPtr] = gHandler->dataRX[0];
		gsm_processMessage();
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	__HAL_UART_CLEAR_OREFLAG(huart);
	__NOP();
}


