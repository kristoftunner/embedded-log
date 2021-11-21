/*
 * gsm.h
 *
 *  Created on: Nov 17, 2021
 *      Author: usr_tunnerk
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include <stdint.h>

/* AT command defines 
 * RESP: size of the response in bytes
 * OK: place of the OK in the response in bytes*/
/* request manufacturer identification*/
#define CMD_GMI "GMI"
#define RESP_GMI 63
#define OK_GMI 59
/* select context as foreground context*/
#define CMD_QIFGCNT "QIFGCNT"
#define RESP_QIFGCNT 37
#define OK_QIFGCNT 16
/* select CSD or GPRS as bearer*/
#define CMD_QICSGP "QICSGP"
#define RESP_QICSGP 6
#define OK_QICSGP 3
/* enable/disable multiple TCP/IP connection*/
#define CMD_QIMUX "QIMUX"
#define RESP_QIMUX 6
#define OK_QIMUX 3
/* set RI time*/
#define CMD_QIMODE "QIMODE"
#define RESP_QIMODE 6
#define OK_QIMODE 3
/* connect with IP address or DNS*/
#define CMD_QIDNSIP "QIDNSIP"
#define RESP_QIDNSIP 6
#define OK_QIDNSIP 3
/* configure transparent mode*/
#define CMD_QITCFG "QITCFG"
#define RESP_QITCFG 6
#define OK_QITCFG 3
/* start TCP/IP task and set APN,USER,PWD*/
#define CMD_QIREGAPP "QIREGAPP"
#define RESP_QIREGAPP 0
#define OK_QIREGAPP 0

/* activate GPRS/CSD context*/
#define CMD_QIACT "QIACT"
#define RESP_QIACT 0
#define OK_QIACT 0

/* get local IP address*/
#define CMD_QILOCIP "QILOCIP"
#define RESP_QILOCIP 0
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
#define RESP_QISTAT 36
#define OK_QISTAT 12

typedef enum {
	test = 0,
	read = 1,
	write = 2,
	exec = 3
}ATCommandType;

struct MC60_cmd
{
	ATCommandType commandType;
	uint8_t *cmd;
	uint8_t *writeCmd;
	uint16_t msgLength;
	uint16_t responseLength;
	uint8_t offsetOK;

};

int MC60_sendAT(struct MC60_cmd cmd);
int MC60_connect(const char *ip, const char *port);
int MC60_init();
void MC60_reset();
int MC60_close();
#endif /* INC_GSM_H_ */
