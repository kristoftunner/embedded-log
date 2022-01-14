/** @file gsm.h */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include <stdint.h>
#include "main.h"

/* AT command defines 
 * RESP: number of response messages separated by \r\n
 * OK: place of the OK packet in the messages
 * 		messages are separated by \r\n, the first message
 * 		is the command echoed back from the GSM module which is counted as well*/
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
/* TODO: fill out OK and RESP
 * start TCP or UDP connection*/
#define CMD_QIOPEN "QIOPEN"
#define RESP_QIOPEN 0
#define OK_QIOPEN 0
/* TODO: fill out OK and RESP
 * query the data information for sending*/
#define CMD_QISACK "QISACK"
#define RESP_QISACK 0
#define OK_QISACK 0
/* TODO: fill out OK and RESP
 * choose connection*/
#define CMD_QISRVC "QISRVC"
#define RESP_QISRVC 0
#define RESP_QISRVC_READ 0
#define OK_QISRVC 0
#define OK_QISRVC_READ 0
/* TODO: fill out OK and RESP
 * close TCP or UDP connection*/
#define CMD_QICLOSE "QICLOSE"
#define RESP_QICLOSE 0
#define OK_QICLOSE 0
/* TODO: fill out OK and RESP
 * deactivate GPRS/CSD context*/
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
#define RESP_QMTOPEN 3
#define OK_QMTOPEN 2

/* TODO: fill out OK and RESP
 * Cloes network for mqtt client*/
#define CMD_QMTCLOSE "QMTCLOSE"
#define RESP_QMTCLOSE 0
#define OK_QMTCLOSE 0

/* connect to an mqtt server */
#define CMD_QMTCONN "QMTCONN"
#define RESP_QMTCONN 3
#define OK_QMTCONN 2

/* TODO: fill out OK and RESP
 * Disconnect from mqtt server */
#define CMD_QMTDISC "QMTDISC"
#define RESP_QMTDISC 0
#define OK_QMTDISC 0

/* TODO: fill out OK and RESP
 * subrscribe to mqtt server topic */
#define CMD_QMTSUB "QMTSUB"
#define RESP_QMTSUB 3
#define OK_QMTSUB 2

/* publish to mqtt server topic */
#define CMD_QMTPUB "QMTPUB"
#define RESP_QMTPUB 3
#define OK_QMTPUB 3

/* TODO: fill out OK and RESP
 * unsubscribe from mqtt server topic */
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

/* enums of the MQTT AT commands return codes*/
typedef struct
{
	uint8_t connRetCode;
	uint8_t connResult;
	uint8_t connState;
	uint8_t openResult;
	uint8_t tcpipConnectId;
}MQTT_status;

typedef enum
{
	GSM_PWR_DOWN,
	GSM_PWR_UP,
	GSM_INITIALIZED,
	GSM_MQTT_CONNECTED,
	GSM_FAIL
}gsm_status;

typedef enum
{
	GSMERROR_NOERROR,
	GSMERROR_MSGTIMOUT
}gsm_errorCode;
typedef enum {
	test = 0,
	read = 1,
	write = 2,
	exec = 3
}ATCommandType;

/* enum for the states of the MQTT task*/
typedef enum {
	MQTT_INITIAL,
	MQTT_RECIEVING,
	MQTT_RECIEVED,
	MQTT_PUBLISHING
}MQTT_pubSubStatus;

/* enum for MQTT message type(Publish, subscribe)*/
typedef enum{
	PUBMSG,
	SUBMSG,
}MQTT_msgType;

/**
 * @brief MQTT message control block for sending/recieving MQTT messages  
 * 
 */
typedef struct
{
	MQTT_msgType msgFlag;
	uint8_t jsonString[1024];
	uint8_t topic[32];
	/* msgValid flag, indicating for the gsm_mqttProcess that it is a valid publish message*/
}MQTT_controlMsg;

/* this struct includes all the information needed for AT command sending/recieving*/
typedef struct
{
	ATCommandType commandType;
	uint8_t cmd[32];
	uint8_t writeCmd[64];
	uint8_t rxBuffer[128];
	uint8_t txBuffer[128];
	uint8_t publishBuffer[1024];
	uint8_t subrscribeBuffer[256];
	uint16_t subscribeDataPtr;
	uint16_t msgLength;
	uint16_t responePacketNr; //number of response packets separated by \r\n
	uint8_t currPacketNr;
	uint8_t packetOK; //packet number of the OK response packet
	uint8_t offsetOK; //OK offset in the rxBuffer
	uint8_t dataPtr;
	uint8_t dataReadyFlag;
	uint8_t responseOKFlag;
	uint8_t mqttPubSendFlag;
	uint8_t delimiterCntr;
	uint8_t msgTimout;
}gsm_cmd;

typedef struct
{
	UART_HandleTypeDef *port;
	uint8_t dataRX[2];	// valamiért az egybájtos változóval nem működött az UART recieve IT
	gsm_cmd cmd;
	uint8_t ipAddr[20];
	gsm_status gsmState;
	gsm_errorCode errorCode;
	MQTT_status mqttStat;
	MQTT_pubSubStatus mqttPubSubStatus;
}gsm_handler;

gsm_handler *gHandler;

int gsm_sendAT();
void gsm_processMessage();
int gsm_connect();
int gsm_startController(gsm_handler *handler);
int gsm_init();
void gsm_reset();
int gsm_close();
TCPIP_status gsm_getTCPStatus();
void gsm_updateMqttStatus();
int gsm_getIp();
int gsm_mqttPub(char *jsonString, char *topic);
int gsm_mqttSub(char *topic);

/**
 * @brief MQTT processing function
 * 
 * @param subrscribeMsg 
 * @param publishMsg 
 */
void gsm_mqttProcess(MQTT_controlMsg *subrscribeMsg, MQTT_controlMsg *publishMsg);
void gsm_mqttParseMsg(MQTT_controlMsg *subrscribeMsg);
#endif /* INC_GSM_H_ */
