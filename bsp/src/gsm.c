/*
 * gsm.c
 *
 *  Created on: 17 Nov 2021
 *      Author: usr_tunnerk
 */
#include <string.h>
#include <stdint.h>
#include "gsm.h"
#include "log.h"
#include "main.h"

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
	int msgTimeoutCntr = 0;
	gHandler->cmd.msgLength =0;

	for(int i = 0; i < sizeof(gHandler->cmd.txBuffer); i++)
	{
		gHandler->cmd.rxBuffer[i] = 0;
		gHandler->cmd.txBuffer[i] = 0;
	}
	strcpy(gHandler->cmd.txBuffer, "AT+");
	gHandler->cmd.msgLength = 3;
	strcat(gHandler->cmd.txBuffer, gHandler->cmd.cmd);
	gHandler->cmd.msgLength += strlen(gHandler->cmd.cmd);

	if(gHandler->cmd.commandType==write)
	{
		strcat(gHandler->cmd.txBuffer,"=");
		strcat(gHandler->cmd.txBuffer, gHandler->cmd.writeCmd);
		gHandler->cmd.msgLength += strlen(gHandler->cmd.writeCmd) + 1;
	}
	else if(gHandler->cmd.commandType==test)
	{
		strcat(gHandler->cmd.txBuffer,"=?");
		gHandler->cmd.msgLength += 2;
	}
	else if(gHandler->cmd.commandType==read)
	{
		strcat(gHandler->cmd.txBuffer,"?");
		gHandler->cmd.msgLength += 1;
	}
	strcat(gHandler->cmd.txBuffer,"\r");
	gHandler->cmd.msgLength += 1;

	stat = HAL_UART_Transmit(gHandler->port, (uint8_t*)(gHandler->cmd.txBuffer), gHandler->cmd.msgLength, 1000);

	/* flush UART recieve register before beginning the reception*/
	__HAL_UART_CLEAR_OREFLAG(gHandler->port);
	__HAL_UART_CLEAR_NEFLAG(gHandler->port);
	__HAL_UART_CLEAR_FEFLAG(gHandler->port);
	__HAL_UART_DISABLE_IT(gHandler->port, UART_IT_ERR);
	uint8_t temp = (uint8_t)(gHandler->port->Instance->RDR);
	stat = HAL_UART_Receive_IT(gHandler->port, (uint8_t *)(gHandler->dataRX), 1);

	/* if we are sending a publish message, then first check for mqttPubSendFlag("<" character)*/
	if(strncmp(&(gHandler->cmd.cmd),"QMTPUB",6) == 0)
	{
		while(gHandler->cmd.mqttPubSendFlag == 0);
		HAL_Delay(10);
		HAL_UART_Transmit(gHandler->port, (uint8_t *)gHandler->cmd.publishBuffer,strlen(gHandler->cmd.publishBuffer),100);
	}
	/* waiting for the reception to end */
	while((gHandler->cmd.dataReadyFlag == 0) && (gHandler->cmd.msgTimout == 0))
	{
		HAL_Delay(500);
		msgTimeoutCntr++;
		if(msgTimeoutCntr > 10)
			gHandler->cmd.msgTimout = 1;
	}

	if(gHandler->cmd.responseOKFlag && (gHandler->cmd.msgTimout == 0))
		return 0;
	else
	{
		if(gHandler->cmd.msgTimout)
			gHandler->errorCode = GSMERROR_MSGTIMOUT;
		return 1;
	}
}

/* 1)check rxBuffer
 * 2) if current message is ready -> stop UART reception
 * 2) if current message is not -> continue the UART reception*/
void gsm_processMessage()
{
	/* If configuring the GSM module OR publishing then parse UART input*/
	if(gHandler->cmd.dataReadyFlag == 0 && ((gHandler->mqttPubSubStatus == MQTT_INITIAL) || gHandler->mqttPubSubStatus == MQTT_PUBLISHING))
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

			/* check if all the message packe recieved
			 * for some reason quectel module ends the command echo message with "\r\n" only for the QMTPUB command
			 * */
			if(strncmp(&(gHandler->cmd.cmd),"QMTPUB",6) == 0)
			{
				if(gHandler->cmd.delimiterCntr == (gHandler->cmd.responePacketNr-1)*2+1)
				{
					gHandler->cmd.dataReadyFlag = 1;
					return;
				}
				else if((gHandler->cmd.delimiterCntr % 2) == 0)
				{

					gHandler->cmd.currPacketNr++;
				}
			}
			else
			{
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

		/* Checking the MQTT specific messages */
		/* If message: MQTT Publish, then check for the ">" character*/
		if(strncmp(&(gHandler->cmd.cmd),"QMTPUB",6) == 0)
		{
			if(gHandler->dataRX[0] = 0x3c)
			{
				gHandler->cmd.mqttPubSendFlag = 1;
				//gHandler->cmd.dataReadyFlag = 1;
				//gHandler->cmd.responseOKFlag = 1;
			}
		}

		gHandler->cmd.dataPtr++;
	}
	else
	{
		if(gHandler->cmd.subrscribeBuffer[gHandler->cmd.subscribeDataPtr] == '\n' && gHandler->cmd.subrscribeBuffer[gHandler->cmd.subscribeDataPtr-1] == '\r')
		{
			gHandler->cmd.delimiterCntr++;
			if(gHandler->cmd.delimiterCntr == 2)
			{
				if(strncmp(&(gHandler->cmd.subrscribeBuffer[2]),"+QMTRECV",8) == 0)
				{
					gHandler->cmd.dataReadyFlag = 1;
				}
			}
		}
		gHandler->cmd.subscribeDataPtr++;
	}

	HAL_UART_Receive_IT(gHandler->port, (uint8_t *)(gHandler->dataRX), 1);
}

/* helper function for constructing AT command */
void gsm_constructCmd(ATCommandType type, const uint8_t *cmd, const uint8_t *writeCmd, uint8_t responsePackets, uint8_t offsetPacket)
{
	/* Clearing out buffers of the cmd struct */
	for(int i = 0; i < sizeof(gHandler->cmd.cmd)/sizeof(gHandler->cmd.cmd[0]); i++)
	{
		gHandler->cmd.cmd[i] = 0;
	}
	for(int i = 0; i < sizeof(gHandler->cmd.publishBuffer)/sizeof(gHandler->cmd.publishBuffer[0]); i++)
	{
		gHandler->cmd.publishBuffer[i] = 0;
	}
	for(int i = 0; i < sizeof(gHandler->cmd.rxBuffer)/sizeof(gHandler->cmd.rxBuffer[i]); i++)
	{
		gHandler->cmd.rxBuffer[i] = 0;
		gHandler->cmd.txBuffer[i] = 0;
	}

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
	gHandler->cmd.msgTimout = 0;
	gHandler->cmd.mqttPubSendFlag = 0;
}

/* initialize gsm for TCP/IP communcation
 * Using the TCPIP stack in NON-TRANSPARENT mode with DNSIP address resolution*/
int gsm_init()
{
	int error = 0;
	gHandler->mqttStat.connResult = 0;
	gHandler->mqttStat.connRetCode = 0;
	gHandler->mqttStat.connState = 0;
	gHandler->mqttStat.openResult = 0;
	gHandler->mqttPubSubStatus = MQTT_INITIAL;
	gHandler->errorCode = GSMERROR_NOERROR;

    gsm_constructCmd(exec, CMD_GMI, "", RESP_GMI, OK_GMI);
    error |= gsm_sendAT();

    /* If we cannot talk with the GSM module, restart it */
    if(gHandler->errorCode == GSMERROR_MSGTIMOUT)
    {
    	return 1;
    }

    LOG_INF("Initializing the GSM module\r\n");
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
    gsm_constructCmd(write, CMD_QIDNSIP, "1", RESP_QIDNSIP, OK_QIDNSIP);
    error |= gsm_sendAT();
    /* 3: retry times to resend, 2: 200ms to wait til ack, 512: data packet size, 1: escape sequence is on*/
    gsm_constructCmd(write, CMD_QITCFG, "3,2,512,1", RESP_QITCFG, OK_QITCFG);
    error |= gsm_sendAT();
    
    LOG_INF("GSM module initialized\r\n");

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
int gsm_connect()
{
    int error = 0;
    int ipIndCntr = 0;
    int mqttConnCntr = 0;
    HAL_Delay(1500);

    while(gsm_getTCPStatus() != IP_INITIAL)
    {
    	HAL_Delay(200);
    }

    gsm_constructCmd(exec, CMD_QIREGAPP, "", RESP_QIREGAPP, OK_QIREGAPP);
    error |= gsm_sendAT();

    HAL_Delay(1500);

    while(gsm_getTCPStatus() != IP_START)
    {
    	HAL_Delay(200);
    }

    gsm_constructCmd(exec, CMD_QIACT, "", RESP_QIACT, OK_QIACT);
    gsm_sendAT();

    while(gsm_getTCPStatus() == IP_IND)
    {
    	HAL_Delay(200);
    	ipIndCntr++;
    	if(ipIndCntr > 10)
    	{
    		LOG_ERR("MC60 stuck at TPCIP QIACT\r\n");
    		return 1;
    	}
    }

    gsm_getIp();

    HAL_Delay(100);

    while(gsm_getTCPStatus() == IP_GRPSACT)
    {
    	HAL_Delay(200);
    }

    while(gsm_getTCPStatus() != IP_STATUS)
    {
    	HAL_Delay(200);
    }

    uint8_t buffer[100];
    strcpy(buffer,"0,\"be.met3r.com\",1883");
    gsm_constructCmd(write, CMD_QMTOPEN, buffer, RESP_QMTOPEN, OK_QMTOPEN);
    error |= gsm_sendAT();
    gsm_updateMqttStatus();

    LOG_INF("MQTT TCPIP connect ID:%d\r\n", gHandler->mqttStat.tcpipConnectId);
    LOG_INF("Open result:%d\r\n",gHandler->mqttStat.openResult);

    /* TODO: check for OPEN OK*/
    HAL_Delay(200);
    strcpy(buffer,"0,\"clientExample\"");
    gsm_constructCmd(write, CMD_QMTCONN, buffer, RESP_QMTCONN, OK_QMTCONN);
    error |= gsm_sendAT();
    
    /* check if connect OK*/
    gsm_updateMqttStatus();

    while(gHandler->mqttStat.connState != 3)
    {
    	HAL_Delay(500);
    	gsm_constructCmd(read, CMD_QMTCONN, "", RESP_QMTCONN, OK_QMTCONN);
    	gsm_sendAT();
    	gsm_updateMqttStatus();
    	mqttConnCntr++;
    	if(mqttConnCntr > 10)
    	{
    		LOG_ERR("MC60 stuck at MQTT Connect command\r\n");
    		return 1;
    	}
    }

    LOG_INF("MQTT in connected state\r\n");

    return 0;
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

void gsm_updateMqttStatus()
{
	/* checking the result of the QMTCONN */
	if(strncmp(&(gHandler->cmd.txBuffer),"AT+QMTCONN=",11) == 0)
	{
		gHandler->mqttStat.connResult = gHandler->cmd.rxBuffer[51]-48;
		gHandler->mqttStat.connRetCode = gHandler->cmd.rxBuffer[53]-48;
	}
	else if(strncmp(&(gHandler->cmd.txBuffer),"AT+QMTCONN?",11) == 0)
	{
		gHandler->mqttStat.connState = gHandler->cmd.rxBuffer[26]-48;
	}
	else if(strncmp(&(gHandler->cmd.txBuffer),"AT+QMTOPEN=",11) == 0)
	{
		gHandler->mqttStat.openResult = gHandler->cmd.rxBuffer[53]-48;
		gHandler->mqttStat.tcpipConnectId = gHandler->cmd.rxBuffer[51]-48;
	}
	else if(strncmp(&(gHandler->cmd.txBuffer),"AT+QMTOPEN?",11) == 0)
	{
		gHandler->mqttStat.tcpipConnectId = gHandler->cmd.rxBuffer[24]-48;
	}
}

/* close connection with the server */
/* TODO: implement function */
int gsm_close()
{
    int error = 0;
    return error;
}

/* State machine for the MC60 controller engine
 * GSM power up(with PWR_KEY)->initialize->connect->connected*/
int gsm_startController(gsm_handler *handler)
{
	int error = 0;
	gHandler = handler;
	gHandler->gsmState = GSM_PWR_DOWN;
	while(1)
	{
		switch(gHandler->gsmState)
		{
		case GSM_PWR_DOWN:
			LOG_INF("Starting GSM module\r\n");
			gsm_reset();
			gHandler->gsmState = GSM_PWR_UP;
			break;
		case GSM_PWR_UP:
			gsm_init();
			if(gHandler->errorCode == GSMERROR_MSGTIMOUT)
			{
				gHandler->gsmState = GSM_PWR_DOWN;
				LOG_INF("GSM message timeout, restarting GSM module!\r\n");
			}
			else
				gHandler->gsmState = GSM_INITIALIZED;
			break;
		case GSM_INITIALIZED:
			gsm_connect();
			if(gHandler->mqttStat.connState == 3)
				gHandler->gsmState = GSM_MQTT_CONNECTED;
			else
				gHandler->gsmState = GSM_PWR_DOWN;
			break;
		case GSM_MQTT_CONNECTED:
			return 0;
		}
	}
}

/* MQTT Subscribe function*/
int gsm_mqttSub(char *topic)
{
	int error = 0;
	uint8_t buffer[30];
	
	gHandler->mqttPubSubStatus = MQTT_INITIAL;

	for(int i = 0; i < sizeof(gHandler->cmd.subrscribeBuffer); i++)
	{
		gHandler->cmd.subrscribeBuffer[i];
	}
	for(int i = 0; i < sizeof(buffer); i++)
	{
		buffer[i] = 0;
	}

	if(strlen(topic) >sizeof(buffer))
	{
		LOG_ERR("MQTT topic is too long, get larger buffer!\r\n");
		return 1;
	}

	strcpy(buffer, "0,1,\"");
	strcat(buffer, topic);
	strcat(buffer, "\",2");

	gsm_constructCmd(write, CMD_QMTSUB, buffer, RESP_QMTSUB, OK_QMTSUB);
	error |= gsm_sendAT();
	if(gHandler->cmd.rxBuffer[47] == 48)
	{
		gHandler->mqttPubSubStatus = MQTT_RECIEVING;
	}
	else
	{
		gHandler->mqttPubSubStatus = MQTT_INITIAL;
		LOG_ERR("Could not subrscribe to topic!\r\n");
		return 1;
	}

	LOG_INF("subscribed to:%s\r\n",topic);

	HAL_UART_Receive_IT(gHandler->port, (uint8_t *)(gHandler->dataRX), 1);

	/* Clear the flags for the first reception */
	gHandler->cmd.subscribeDataPtr = 0;
	gHandler->cmd.delimiterCntr = 0;
	gHandler->cmd.dataReadyFlag = 0;
	return error;
}

/**
 * @brief	MQTT message process control function 
 * 
 * @param subrscribeMsg 
 * @param publishMsg 
 */
void gsm_mqttProcess(MQTT_controlMsg *subrscribeMsg, MQTT_controlMsg *publishMsg)
{
	int error = 0;
	switch(gHandler->mqttPubSubStatus)
	{
	case MQTT_INITIAL:
		LOG_WRN("MQTT subrscription failed!\r\n");
		break;
	case MQTT_RECIEVING:
		if(gHandler->cmd.dataReadyFlag)
		{
			/* clear the subrscribeMsg and parse the recieved JSON input*/
			for(int i = 0; i < sizeof(subrscribeMsg->jsonString)/sizeof(subrscribeMsg->jsonString[0]); i++)
			{
				subrscribeMsg->jsonString[i] = 0;
			}
			for(int i = 0; i < sizeof(subrscribeMsg->topic)/sizeof(subrscribeMsg->topic[0]); i++)
			{
				subrscribeMsg->topic[i] = 0;
			}

			gsm_mqttParseMsg(subrscribeMsg);

			/* clear the subrscribebuffer and the flags needed for message reception*/
			gHandler->cmd.subscribeDataPtr = 0;
			for(int i = 0; i < sizeof(gHandler->cmd.subrscribeBuffer)/sizeof(gHandler->cmd.subrscribeBuffer[0]); i++)
			{
				gHandler->cmd.subrscribeBuffer[i] = 0;
			}
			gHandler->mqttPubSubStatus = MQTT_RECIEVED;
			gHandler->cmd.subscribeDataPtr = 0;
			gHandler->cmd.delimiterCntr = 0;
			gHandler->cmd.dataReadyFlag = 0;
		}
		else
		{
			;	
		}
		break;
	case MQTT_PUBLISHING:
		error |= gsm_mqttPub(publishMsg->jsonString, publishMsg->topic);
		break;
	}
}

void gsm_mqttParseMsg(MQTT_controlMsg *subrscribeMsg)
{
	/*parse publishbuffer*/
	uint8_t delimiter = 44;
	uint8_t *topic,*msg = NULL;
	int msgSize,topicSize = 0;
	topic = strchr(gHandler->cmd.subrscribeBuffer,delimiter)+3;
	if(topic != NULL)
	{
		msg = strchr(topic,delimiter)+1;
		if(msg != NULL)
		{
			msgSize = strlen(msg)-2;
			topicSize = msg-topic-1;
			strncpy(subrscribeMsg->jsonString, msg, msgSize);
			strncpy(subrscribeMsg->topic, topic, topicSize);
		}
	}
}
 
/**
 * @brief MQTT publishing function
 * 
 * @param jsonString 		string for the message
 * @param topic 			MQTT topic name
 * @return int 				error return, 0 if OK 
 */
int gsm_mqttPub(char *jsonString, char *topic)
{
	int error = 0;
	uint8_t buffer[30];

	gHandler->mqttPubSubStatus = MQTT_PUBLISHING;

	if(strlen(jsonString) > sizeof(gHandler->cmd.publishBuffer))
	{
		LOG_ERR("JSON string too long\r\n");
		return 1;
	}
	if(strlen(topic) > sizeof(buffer))
	{
		LOG_ERR("MQTT Topic is too long, get larger buffer!\r\n");
		return 1;
	}

	strcpy(buffer, "0,0,0,0,\"");
	strcat(buffer, topic);
	strcat(buffer,"\"");
	gsm_constructCmd(write, CMD_QMTPUB, buffer, RESP_QMTPUB, OK_QMTPUB);
	strcpy(gHandler->cmd.publishBuffer, jsonString);
	strcat(gHandler->cmd.publishBuffer, "\032\032");
	error |= gsm_sendAT();
	LOG_INF("published:%s\r\n",gHandler->cmd.publishBuffer);

	/* clearing the needed message flags and enabling the UART recieve interrupt for the mqtt message reception*/
	gHandler->cmd.subscribeDataPtr = 0;
	gHandler->cmd.delimiterCntr = 0;
	gHandler->cmd.dataReadyFlag = 0;
	HAL_UART_Receive_IT(gHandler->port, (uint8_t *)(gHandler->dataRX), 1);
	if(error == 0)
	{
		gHandler->mqttPubSubStatus = MQTT_RECIEVING;
		return 0;
	}
	else
	{
		return 1;
	}
}
