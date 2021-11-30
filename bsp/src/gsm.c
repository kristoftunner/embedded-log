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

static uint8_t txBuffer[256];
static uint8_t rxBuffer[256];

int msgRecv = 0;

void MC60_reset()
{
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_SET);
  HAL_Delay(1500);
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_RESET);
  HAL_Delay(1000);
}



int MC60_sendAT(gsm_cmd cmd)
{
	uint8_t txBuffer[100];
	for(int i = 0; i < 100; i++)
	{
		txBuffer[i] = 0;
	}

	for(int i = 0; i < 256; i++)
	{
		gHandler->cmd.rxBuffer[i] = 0;
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

	uint8_t txbuffer0[] = "AT+QISTAT\r";
	HAL_UART_Transmit(&huart8, (uint8_t*)txbuffer0, sizeof(txbuffer0), 1000);

	HAL_UART_Receive_IT(&huart8, (uint8_t*)rxBuffer, 1);
	while(msgRecv == 0);
	/*HAL_UART_Receive(&huart8, (uint8_t*)rxBuffer, cmd.responseLength, 1000);

	if(strncmp(rxBuffer+cmd.offsetOK,"OK",2) == 0)
	{
		return 0;
	}*/

	return 0;
}

/* 1)check rxBuffer
 * 2) if current message is ready -> stop UART reception
 * 2) if current message is not -> continue the UART reception*/
void gsm_checkMessage()
{
	if()
}

/* helper function for constructing AT command */
gsm_cmd MC60_constructCmd(ATCommandType type, const uint8_t * cmd, const uint8_t *writeCmd, uint8_t responseLength, uint8_t offsetOK)
{
    gsm_cmd cmdConstructed;
//    cmdConstructed.commandType = type;
//    cmdConstructed.cmd = cmd;
//    cmdConstructed.msgLength = 0;
//    if(cmdConstructed.commandType == write)
//    {
//    	cmdConstructed.writeCmd = writeCmd;
//    }
//
//    cmdConstructed.responeMsgNr = 2;
//    cmdConstructed.packetOK = 1;
	strcpy(gHandler->cmd.cmd,cmd);
	strcpy(gHandler->cmd.writeCmd,writeCmd);
	gHandler->cmd.commandType = type;
	gHandler->cmd.msgLength = 0;

    return cmdConstructed;
}

/* initialize MC60 for TCP/IP communcation */
int MC60_init()
{
    int error = 0;
//    gsm_cmd gmi = MC60_constructCmd(exec,CMD_GMI,"",RESP_GMI, OK_GMI);
//    gHandler->cmd = gmi;
//    error |= MC60_sendAT(gmi);
    /* check IP state */
//    struct MC60_cmd qistat = MC60_constructCmd(exec, CMD_QISTAT, "", RESP_QISTAT, OK_QISTAT);
//    error |= MC60_sendAT(qistat);
    gsm_cmd qifcgnt = MC60_constructCmd(write, CMD_QIFGCNT, "0", RESP_QIFGCNT, OK_QIFGCNT);
    error |= MC60_sendAT(qifcgnt);
    //gHandler->cmd = qifcgnt;
//    struct MC60_cmd qicsgp = MC60_constructCmd(write, CMD_QICSGP,"1,\"iot.1nce.net\"",RESP_QICSGP, OK_QICSGP); //here set the APN,USER and PWD according to the SIM card
//    error |= MC60_sendAT(qicsgp);
//    /* visit single server */
//    struct MC60_cmd qimux = MC60_constructCmd(write, CMD_QIMUX, "0", RESP_QIMUX, OK_QIMUX);
//    error |= MC60_sendAT(qimux);
//    /* non-transparent mode*/
//    struct MC60_cmd qimode = MC60_constructCmd(write, CMD_QIMODE, "0", RESP_QIMODE, OK_QIMODE);
//    error |= MC60_sendAT(qimode);
//    /* connect with IP address*/
//    struct MC60_cmd qidnspip = MC60_constructCmd(write, CMD_QIDNSIP, "0", RESP_QIDNSIP, OK_QIDNSIP);
//    error |= MC60_sendAT(qidnspip);
//    /* 3: retry times to resend, 2: 200ms to wait til ack, 512: data packet size, 1: escape sequence is on*/
//    struct MC60_cmd qitcfg = MC60_constructCmd(write, CMD_QITCFG, "3,2,512,1", RESP_QITCFG, OK_QITCFG);
//    error |= MC60_sendAT(qitcfg);
    
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
    gsm_cmd qiopen = MC60_constructCmd(write, CMD_QIOPEN, buffer, RESP_QIOPEN, OK_QIOPEN);
    /* TODO: check for connect OK needs to be implemented*/
    error |= MC60_sendAT(qiopen);
    
    return error;
}

/* close connection with the server */
int MC60_close()
{
    int error = 0;
    /* check conncetion */
//    struct MC60_cmd qisrvc = MC60_constructCmd(read, CMD_QISRVC, "", RESP_QISRVC_READ, OK_QISRVC_READ);
//    error |= MC60_sendAT(qisrvc);
//    /* TODO: check if we are client in the connection */
//    struct MC60_cmd qisrvc_write = MC60_constructCmd(write, CMD_QISRVC, "1", RESP_QISRVC, OK_QISRVC);
//    error |= MC60_sendAT(qisrvc_write);
//    struct MC60_cmd qideact = MC60_constructCmd(exec, CMD_QIDEACT, "", RESP_QIDEACT, OK_QIDEACT);
//    error |= MC60_sendAT(qideact);

    return error;
}

int MC60_recv(uint8_t *data)
{

}
