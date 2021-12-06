/*
 * NectiveButtonController.cpp
 *
 *  Created on: Nov 10, 2021
 *      Author: krist
 */


#include <NectiveButtonController.hpp>
#include <main.h>
#include <touchgfx/hal/HAL.hpp>
#include "cmsis_os2.h"
#include "buttons.h"

void NectiveButtonController::init()
{

}

bool NectiveButtonController::sample(uint8_t& key)
{
	if(bHandler->buttonState)
	{
		key = bHandler->buttonState - 1;
		bHandler->buttonState = 0;
		return true;
	}

	return false;
}
