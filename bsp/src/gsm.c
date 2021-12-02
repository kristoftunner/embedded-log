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

void gsm_reset()
{
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_SET);
  HAL_Delay(1500);
  HAL_GPIO_WritePin(GPIOD,PWR_KEY_Pin,GPIO_PIN_RESET);
  HAL_Delay(1000);
}



int gsm_sendAT()
{
	HAL_StatusTypeDef stat = 0;

	for(int i = 0; i < 256; i++)
	{
		gHandler->cmd.rxBuffer[i] = 0;
		gHandler->cmd.txBuffer[i] = 0;
	}
	strcpy(gHandler->cmd.txBuffer, "AT+");
	gHandler->cmd.msgLength += 3;
	strcat(gHandler->cmd.txBuffer, gHandler->cmd.cmd);
	gHandler->cmd.msgLength += strlen(gHandler->cmd.cmd);

	if(gHandler->cmd.commandType==write)
	{
		strcat(gHandler->cmd.txBuffer,"=");
		strcat(gHandler->cmd.txBuffer, gHandler->cmd.writeCmd);
		gHandler->cmd.msgLength += strlen(gHandler->cmd.writeCmd) + 1;
	}

	strcat(gHandler->cmd.txBuffer,"\r");
	gHandler->cmd.msgLength += 1;

	stat = HAL_UART_Transmit(&huart8, (uint8_t*)(gHandler->cmd.txBuffer), gHandler->cmd.msgLength, 1000);

	/* flush UART recieve register before beginning the reception*/
	__HAL_UART_CLEAR_OREFLAG(&huart8);
	__HAL_UART_CLEAR_NEFLAG(&huart8);
	__HAL_UART_CLEAR_FEFLAG(&huart8);
	__HAL_UART_DISABLE_IT(&huart8, UART_IT_ERR);
	uint8_t temp = (uint8_t)(huart8.Instance->RDR);
	stat = HAL_UART_Receive_IT(&huart8, (uint8_t *)(gHandler->dataRX), 1);

	/* waiting for the reception to end */
	while(gHandler->cmd.dataReadyFlag == 0);

	if(gHandler->cmd.responseOKFlag)
		return 0;
	else
		return 1;
}

/* 1)check rxBuffer
 * 2) if current message is ready -> stop UART reception
 * 2) if current message is not -> continue the UART reception*/
void gsm_processMessage()
{
	if(gHandler->cmd.dataReadyFlag == 0)
	{

		if(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr] == '\n' && gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-1] == '\r')
		{
			gHandler->cmd.delimiterCntr++;

			/* check if response is OK */
			if(gHandler->cmd.currPacketNr == gHandler->cmd.packetOK-1)
			{
				if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-3]),"OK",2) == 0)
					gHandler->cmd.responseOKFlag = 1;
			}

			/* check if all the message packe recieved*/
			if(gHandler->cmd.delimiterCntr == (gHandler->cmd.responePacketNr-1)*2)
			{
				gHandler->cmd.dataReadyFlag = 1;
				return;
			}
			else if((gHandler->cmd.delimiterCntr % 2) == 0)
			{

				gHandler->cmd.currPacketNr++;
			}
		}

		/* if the message sent is recieved, then the first packet is done */
		if((gHandler->cmd.dataPtr-1) == gHandler->cmd.msgLength)
		{
			if(strncmp(&(gHandler->cmd.rxBuffer),&(gHandler->cmd.txBuffer), gHandler->cmd.msgLength) == 0)
			{
				gHandler->cmd.currPacketNr++;
				if(strncmp(&(gHandler->cmd.cmd),"QIACT",5) == 0)
					gHandler->cmd.dataReadyFlag = 1;
			}
		}

		gHandler->cmd.dataPtr++;
		HAL_UART_Receive_IT(&huart8, (uint8_t *)(gHandler->dataRX), 1);
	}
}

/* helper function for constructing AT command */
void gsm_constructCmd(ATCommandType type, const uint8_t * cmd, const uint8_t *writeCmd, uint8_t responsePackets, uint8_t offsetPacket)
{
	strcpy(gHandler->cmd.cmd,cmd);
	strcpy(gHandler->cmd.writeCmd,writeCmd);
	gHandler->cmd.commandType = type;
	gHandler->cmd.msgLength = 0;
	gHandler->cmd.currPacketNr = 1;
	gHandler->cmd.dataReadyFlag = 0;
	gHandler->cmd.responePacketNr = responsePackets;
	gHandler->cmd.currPacketNr = 0;
	gHandler->cmd.dataPtr = 0;
	gHandler->cmd.packetOK = offsetPacket;
	gHandler->dataRX[0] = 0;
	gHandler->cmd.delimiterCntr = 0;
	gHandler->cmd.responseOKFlag = 0;
}

/* initialize gsm for TCP/IP communcation */
int gsm_init()
{
    int error = 0;
    gsm_constructCmd(exec, CMD_GMI, "", RESP_GMI, OK_GMI);
    gsm_sendAT();
    /* check IP state */
    gsm_constructCmd(exec, CMD_QISTAT, "", RESP_QISTAT, OK_QISTAT);
    error |= gsm_sendAT();
    gsm_constructCmd(write, CMD_QIFGCNT, "0", RESP_QIFGCNT, OK_QIFGCNT);
    error |= gsm_sendAT();
    gsm_constructCmd(write, CMD_QICSGP,"1,\"iot.1nce.net\"",RESP_QICSGP, OK_QICSGP); //here set the APN,USER and PWD according to the SIM card
    error |= gsm_sendAT();
    /* visit single server */
    gsm_constructCmd(write, CMD_QIMUX, "0", RESP_QIMUX, OK_QIMUX);
    error |= gsm_sendAT();
    /* non-transparent mode*/
    gsm_constructCmd(write, CMD_QIMODE, "0", RESP_QIMODE, OK_QIMODE);
    error |= gsm_sendAT();
    /* connect with IP address*/
    gsm_constructCmd(write, CMD_QIDNSIP, "0", RESP_QIDNSIP, OK_QIDNSIP);
    error |= gsm_sendAT();
    /* 3: retry times to resend, 2: 200ms to wait til ack, 512: data packet size, 1: escape sequence is on*/
    gsm_constructCmd(write, CMD_QITCFG, "3,2,512,1", RESP_QITCFG, OK_QITCFG);
    error |= gsm_sendAT();
    
    return error;
}

/* get IP address of the GSM module */
int gsm_getIp()
{
	int error = 0;
	gsm_constructCmd(exec, CMD_QILOCIP, "", RESP_QILOCIP, OK_QILOCIP);
	gsm_sendAT();
	//strcpy the ip address
	uint16_t temp = gHandler->cmd.dataPtr - gHandler->cmd.msgLength-3;
	strncpy(gHandler->ipAddr, &(gHandler->cmd.rxBuffer[gHandler->cmd.msgLength+2]),temp);

	return 0;
}
/* connect to the server */
int gsm_connect(const char *ip, const char *port)
{
    int error = 0;
    gsm_getTCPStatus();
    gsm_constructCmd(exec, CMD_QIREGAPP, "", RESP_QIREGAPP, OK_QIREGAPP);
    error |= gsm_sendAT();

    while(gsm_getTCPStatus() == IP_INITIAL);

    gsm_constructCmd(exec, CMD_QIACT, "", RESP_QIACT, OK_QIACT);
    gsm_sendAT();

    while(gsm_getTCPStatus() == IP_START);

    gsm_getIp();

    while(gsm_getTCPStatus() == IP_GRPSACT);


    while(gsm_getTCPStatus() == IP_STATUS);

    uint8_t buffer[100];
    strcpy(buffer,"\"TCP\",\"");
    strcat(buffer,ip);
    strcat(buffer, "\",");
    strcat(buffer,port);
    gsm_constructCmd(write, CMD_QIOPEN, buffer, RESP_QIOPEN, OK_QIOPEN);
    /* TODO: check for connect OK needs to be implemented*/
    error |= gsm_sendAT();
    
    return error;
}

/* get the status of the TCPIP stack */
TCPIP_status gsm_getTCPStatus()
{
	TCPIP_status stat = IP_ERROR;
	int error = 0;
	gsm_constructCmd(exec, CMD_QISTAT, "", RESP_QISTAT, OK_QISTAT);
	error |= gsm_sendAT();

	if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-11]),"IP INITIAL",10) == 0)
	{
		stat = IP_INITIAL;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-9]),"IP START",8) == 0)
	{
		stat = IP_START;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-10]),"IP CONFIG",9) == 0)
	{
		stat = IP_CONFIG;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-7]),"IP IND",6) == 0)
	{
		stat = IP_IND;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-11]),"IP GPRSACT",10) == 0)
	{
		stat = IP_GRPSACT;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-10]),"IP STATUS",9) == 0)
	{
		stat = IP_STATUS;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-13]),"TCP CONNECTING",14) == 0)
	{
		stat = TCP_CONNECTING;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-9]),"IP CLOSE",8) == 0)
	{
		stat = IP_CLOSE;
	}
	else if(strncmp(&(gHandler->cmd.rxBuffer[gHandler->cmd.dataPtr-11]),"CONNECT OK",10) == 0)
	{
		stat = CONNECT_OK;
	}
	else
	{
		stat = IP_ERROR;
	}

	return stat;
}

/* close connection with the server */
int gsm_close()
{
    int error = 0;
    /* check conncetion */
//    struct gsm_cmd qisrvc = gsm_constructCmd(read, CMD_QISRVC, "", RESP_QISRVC_READ, OK_QISRVC_READ);
//    error |= gsm_sendAT(qisrvc);
//    /* TODO: check if we are client in the connection */
//    struct gsm_cmd qisrvc_write = gsm_constructCmd(write, CMD_QISRVC, "1", RESP_QISRVC, OK_QISRVC);
//    error |= gsm_sendAT(qisrvc_write);
//    struct gsm_cmd qideact = gsm_constructCmd(exec, CMD_QIDEACT, "", RESP_QIDEACT, OK_QIDEACT);
//    error |= gsm_sendAT(qideact);

    return error;
}

int gsm_recv(uint8_t *data)
{

}
