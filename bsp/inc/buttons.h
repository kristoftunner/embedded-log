/*
 * buttons.h
 *
 *  Created on: Nov 1, 2021
 *      Author: krist
 */

#ifndef TESLACTRLINC_BUTTONS_H_
#define TESLACTRLINC_BUTTONS_H_

#include "main.h"
#include "cmsis_os2.h"


enum positions{
	left = 1,
	up = 2,
	center = 3,
	right = 4,
	down = 5
};

typedef struct
{
	osTimerId_t antiGlitchTimer;
	uint8_t buttonState;
}button_handler;

button_handler *bHandler;

void buttonsInit(button_handler *handler);
#endif /* TESLACTRLINC_BUTTONS_H_ */
