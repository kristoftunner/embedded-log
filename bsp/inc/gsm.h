/*
 * gsm.h
 *
 *  Created on: Nov 17, 2021
 *      Author: usr_tunnerk
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include <stdint.h>
#include "main.h"

/* AT command defines 
 * RESP: size of the response in bytes
 * OK: place of the OK in the response in bytes*/
/* request manufacturer identification*/
#define CMD_GMI "GMI"
#define RESP_GMI 4
#define OK_GMI 4
/* select context as foreground context*/
#define CMD_QIFGCNT "QIFGCNT"
#define RESP_QIFGCNT 2
#define OK_QIFGCNT 2
/* select CSD or GPRS as bearer*/
#define CMD_QICSGP "QICSGP"
#define RESP_QICSGP 2
#define OK_QICSGP 2
/* enable/disable multiple TCP/IP connection*/
#define CMD_QIMUX "QIMUX"
#define RESP_QIMUX 2
#define OK_QIMUX 2
/* set RI time*/
#define CMD_QIMODE "QIMODE"
#define RESP_QIMODE 2
#define OK_QIMODE 2
/* connect with IP address or DNS*/
#define CMD_QIDNSIP "QIDNSIP"
#define RESP_QIDNSIP 2
#define OK_QIDNSIP 2
/* configure transparent mode*/
#define CMD_QITCFG "QITCFG"
#define RESP_QITCFG 2
#define OK_QITCFG 2
/* start TCP/IP task and set APN,USER,PWD*/
#define CMD_QIREGAPP "QIREGAPP"
#define RESP_QIREGAPP 2
#define OK_QIREGAPP 2

/* activate GPRS/CSD context*/
#define CMD_QIACT "QIACT"
#define RESP_QIACT 1
#define OK_QIACT 0

/* get local IP address*/
#define CMD_QILOCIP "QILOCIP"
#define RESP_QILOCIP 2
#define OK_QILOCIP 0
/* start TCP or UDP connection*/
#define CMD_QIOPEN "QIOPEN"
#define RESP_QIOPEN 0
#define OK_QIOPEN 0
/* query the data information for sending*/
#define CMD_QISACK "QISACK"
#define RESP_QISACK 0
#define OK_QISACK 0
/* choose connection*/
#define CMD_QISRVC "QISRVC"
#define RESP_QISRVC 0
#define RESP_QISRVC_READ 0
#define OK_QISRVC 0
#define OK_QISRVC_READ 0
/* close TCP or UDP connection*/
#define CMD_QICLOSE "QICLOSE"
#define RESP_QICLOSE 0
#define OK_QICLOSE 0
/* deactivate GPRS/CSD context*/
#define CMD_QIDEACT "QIDEACT"
#define RESP_QIDEACT 0
#define OK_QIDEACT 0
/* deactivate GPRS/CSD context*/
#define CMD_QISTAT "QISTAT"
#define RESP_QISTAT 3
#define OK_QISTAT 2

/*MQTT commands*/
/* config parameters of the MQTT stack */
#define CMD_QMTCFG "QMTFCG"
#define RESP_QMTCFG 2
#define OK_QMTCFG 2

/* open the connection for the mqtt client */
#define CMD_QMTOPEN "QMTOPEN"
#define RESP_QMTOPEN 2
#define OK_QMTOPEN 2

/* Cloes network for mqtt client*/
#define CMD_QMTCLOSE "QMTCLOSE"
#define RESP_QMTCLOSE 0
#define OK_QMTCLOSE 0

/* connect to an mqtt server */
#define CMD_QMTCONN "QMTCONN"
#define RESP_QMTCONN 2
#define OK_QMTCONN 2

/* Disconnect from mqtt server */
#define CMD_QMTDISC "QMTDISC"
#define RESP_QMTDISC
#define OK_QMTDISC 0

/* subrscribe to mqtt server topic */
#define CMD_QMTSUB "QMTSUB"
#define RESP_QMTSUB 0
#define OK_QMTSUB 0

/* publish to mqtt server topic */
#define CMD_QMTPUB "QMTPUB"
#define RESP_QMTPUB 2
#define OK_QMTPUB 2

/* unsubscribe from mqtt server topic */
#define CMD_QMTUNS "QMTUNS"
#define RESP_QMTUNS 0
#define OK_QMTUNS 0

typedef enum
{
	IP_INITIAL,
	IP_START,
	IP_CONFIG,
	IP_IND,
	IP_GRPSACT,
	IP_STATUS,
	TCP_CONNECTING,
	CONNECT_OK,
	IP_CLOSE,
	PDP_DEACT,
	IP_ERROR
}TCPIP_status;

typedef enum
{

}network_status;

typedef enum {
	test = 0,
	read = 1,
	write = 2,
	exec = 3
}ATCommandType;

typedef struct
{
	ATCommandType commandType;
	uint8_t cmd[256];
	uint8_t writeCmd[256];
	uint8_t rxBuffer[256];
	uint8_t txBuffer[256];
	uint16_t msgLength;
	uint16_t responePacketNr; //number of response packets separated by \r\n
	uint8_t currPacketNr;
	uint8_t packetOK; //packet number of the OK response packet
	uint8_t offsetOK; //OK offset in the rxBuffer
	uint8_t dataPtr;
	uint8_t dataReadyFlag;
	uint8_t responseOKFlag;
	uint8_t delimiterCntr;
}gsm_cmd;

typedef struct
{
	UART_HandleTypeDef *port;
	uint8_t dataRX[2];	// valamiért az egybájtos változóval nem működött az UART recieve IT
	gsm_cmd cmd;
	uint8_t ipAddr[20];
}gsm_handler;




gsm_handler *gHandler;

void gsm_bufferAdd(gsm_cmd *cmd, uint8_t val);
int gsm_sendAT();
void gsm_processMessage();
int gsm_connect();
int gsm_init();
void gsm_reset();
int gsm_close();
TCPIP_status gsm_getTCPStatus();
int gsm_getIp();
int gsm_mqttSend(char *jsonString);
#endif /* INC_GSM_H_ */
