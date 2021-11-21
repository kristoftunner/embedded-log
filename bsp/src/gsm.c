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

void MC60_reset()
{
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_SET);
  HAL_Delay(1500);
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_RESET);
  HAL_Delay(1000);
}

int MC60_sendAT(struct MC60_cmd cmd)
{
	uint8_t txBuffer[100];
	uint8_t rxBuffer[100];
	for(int i = 0; i < 100; i++)
	{
		txBuffer[i] = 0;
		rxBuffer[i] = 0;
	}
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

	if(cmd.cmd == CMD_QICSGP || cmd.cmd == CMD_QIMUX
		|| cmd.cmd == CMD_QIMODE || cmd.cmd == CMD_QIDNSIP
		|| cmd.cmd == CMD_QITCFG)
	{
		cmd.responseLength += cmd.msgLength;
		cmd.offsetOK += cmd.msgLength-1;
	}

	HAL_UART_Transmit(&huart8, (uint8_t*)txBuffer, cmd.msgLength, 1000);

	HAL_UART_Receive(&huart8, (uint8_t*)rxBuffer, cmd.responseLength, 1000);

	if(strncmp(rxBuffer+cmd.offsetOK,"OK",2) == 0)
	{
		return 0;
	}

	return 1;
}

/* helper function for constructing AT command */
struct MC60_cmd MC60_constructCmd(ATCommandType type, const uint8_t * cmd, const uint8_t *writeCmd, uint8_t responseLength, uint8_t offsetOK)
{
    struct MC60_cmd cmdConstructed;
    cmdConstructed.commandType = type;
    cmdConstructed.cmd = cmd;
    cmdConstructed.msgLength = 0;
    if(cmdConstructed.commandType == write)
    {
    	cmdConstructed.writeCmd = writeCmd;
    }

    cmdConstructed.responseLength = responseLength;
    cmdConstructed.offsetOK = offsetOK;
    return cmdConstructed;
}

/* initialize MC60 for TCP/IP communcation */
int MC60_init()
{
    int error = 0;
    struct MC60_cmd gmi = MC60_constructCmd(exec,CMD_GMI,"",RESP_GMI, OK_GMI);
    error |= MC60_sendAT(gmi);
    /* check IP state */
    struct MC60_cmd qistat = MC60_constructCmd(exec, CMD_QISTAT, "", RESP_QISTAT, OK_QISTAT);
    error |= MC60_sendAT(qistat);
    struct MC60_cmd qifcgnt = MC60_constructCmd(write, CMD_QIFGCNT, "0", RESP_QIFGCNT, OK_QIFGCNT);
    error |= MC60_sendAT(qifcgnt);
    struct MC60_cmd qicsgp = MC60_constructCmd(write, CMD_QICSGP,"1,\"APN\",\"USER\",\"PWD\"",RESP_QICSGP, OK_QICSGP); //here set the APN,USER and PWD according to the SIM card
    error |= MC60_sendAT(qicsgp);
    /* visit single server */
    struct MC60_cmd qimux = MC60_constructCmd(write, CMD_QIMUX, "0", RESP_QIMUX, OK_QIMUX);
    error |= MC60_sendAT(qimux);
    /* non-transparent mode*/
    struct MC60_cmd qimode = MC60_constructCmd(write, CMD_QIMODE, "0", RESP_QIMODE, OK_QIMODE);
    error |= MC60_sendAT(qimode);
    /* connect with IP address*/
    struct MC60_cmd qidnspip = MC60_constructCmd(write, CMD_QIDNSIP, "0", RESP_QIDNSIP, OK_QIDNSIP);
    error |= MC60_sendAT(qidnspip);
    /* 3: retry times to resend, 2: 200ms to wait til ack, 512: data packet size, 1: escape sequence is on*/
    struct MC60_cmd qitcfg = MC60_constructCmd(write, CMD_QITCFG, "3,2,512,1", RESP_QITCFG, OK_QITCFG);
    error |= MC60_sendAT(qitcfg);
    
    return error;
}

/* connect to the server */
int MC60_connect(const char *ip, const char *port)
{
    int error = 0;
    uint8_t buffer[100];
    strcpy(buffer,"\"TCP\",\"");
    strcat(buffer,ip);
    strcat(buffer, "\",");
    strcat(buffer,port);
    struct MC60_cmd qiopen = MC60_constructCmd(write, CMD_QIOPEN, buffer, RESP_QIOPEN, OK_QIOPEN);
    /* TODO: check for connect OK needs to be implemented*/
    error |= MC60_sendAT(qiopen);
    
    return error;
}

/* close connection with the server */
int MC60_close()
{
    int error = 0;
    /* check conncetion */
    struct MC60_cmd qisrvc = MC60_constructCmd(read, CMD_QISRVC, "", RESP_QISRVC_READ, OK_QISRVC_READ);
    error |= MC60_sendAT(qisrvc);
    /* TODO: check if we are client in the connection */
    struct MC60_cmd qisrvc_write = MC60_constructCmd(write, CMD_QISRVC, "1", RESP_QISRVC, OK_QISRVC);
    error |= MC60_sendAT(qisrvc_write);
    struct MC60_cmd qideact = MC60_constructCmd(exec, CMD_QIDEACT, "", RESP_QIDEACT, OK_QIDEACT);
    error |= MC60_sendAT(qideact);

    return error;
}

int MC60_recv(uint8_t *data)
{

}
