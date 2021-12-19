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
}gui_state;

typedef struct{
	gui_state guiState;
	uint16_t cellNumber; //status of this cell is displayed on the cell status gui screen
}gui_handler;

gui_handler *guiHandler;

#endif /* APP_H_ */
