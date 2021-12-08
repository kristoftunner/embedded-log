/*
 * app.h
 *
 *  Created on: Dec 2, 2021
 *      Author: krist
 */

#ifndef APP_H_
#define APP_H_

typedef enum {
	state_cellStatusDisplay,
	state_chargerStatDisplay,
	state_debugDisplay
}app_state;

typedef struct{
	app_state appState;
	uint16_t cellNumber; //status of this cell is displayed on the cell status gui screen
}app_handler;

app_handler *aHandler;
#endif /* APP_H_ */
