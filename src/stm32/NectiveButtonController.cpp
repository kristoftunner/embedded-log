/*
 * NectiveButtonController.cpp
 *
 *  Created on: Nov 10, 2021
 *      Author: krist
 */


#include <NectiveButtonController.hpp>
#include <main.h>
#include <touchgfx/hal/HAL.hpp>

extern "C"{
	extern uint8_t buttonState;
}

void NectiveButtonController::init()
{

}

bool NectiveButtonController::sample(uint8_t& key)
{
	if(buttonState)
	{
		key = buttonState - 1;
		return true;
	}

	return false;
}
