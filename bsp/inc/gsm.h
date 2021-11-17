/*
 * gsm.h
 *
 *  Created on: Nov 17, 2021
 *      Author: usr_tunnerk
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

#include <stdint.h>

#define CMD_GMI "GMI"
#define RESP_GMI 63
#define OK_GMI 59

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
	uint16_t responseLengt;
	uint8_t offsetOK;

};

int MC90_sendAT(struct MC60_cmd cmd);

#endif /* INC_GSM_H_ */
