/*
 * buttons.c
 *
 *  Created on: Nov 10, 2021
 *      Author: krist
 */
#include "main.h"
#include "stm32f7xx_hal_gpio.h"
#include "app.h"
#include "buttons.h"
#include "cmsis_os2.h"

/* 1 - left
 * 2 - up
 * 3 - center
 * 4 - right
 * 5 - down*/

/* idk why but cannot declare this in app.h->linker error:multiple declaration */
app_state appState = state_cellStatusDisplay;

void buttonsInit(button_handler *handler)
{
	bHandler = handler;
	bHandler->buttonState = 0;
	bHandler->timerFlag = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
{
  /* PIN_11 - BTN_5 - Sch: Left(B1)
   * PIN_12 - BTN_2 - Sch: Up(B3)
   * PIN_14 - BTN_3 - Sch: Center(B4)
   * PIN_15 - BTN_1 - Sch: Right(B6)
   * PIN_0 - BTN_4 - Sch: Down(B5) */

	switch(GPIO_pin)
	{

		case GPIO_PIN_11:
			if(bHandler->timerFlag == 0)
			{
				bHandler->timerFlag = 1;
				HAL_TIM_Base_Start_IT(bHandler->antiGlitchTimer);
				bHandler->buttonState = left;
				if(appState != state_debugDisplay)
				{
					appState++;
				}
			}
			break;
		case GPIO_PIN_12:
			if(bHandler->timerFlag == 0)
			{
				HAL_TIM_Base_Start_IT(bHandler->antiGlitchTimer);
				bHandler->timerFlag = 1;
				bHandler->buttonState = up;
			}
			break;
		case GPIO_PIN_14:
			if(bHandler->timerFlag == 0)
			{
				bHandler->timerFlag = 1;
				HAL_TIM_Base_Start_IT(bHandler->antiGlitchTimer);
				bHandler->buttonState = center;
			}
			break;
		case GPIO_PIN_15:
			if(bHandler->timerFlag == 0)
			{
				bHandler->timerFlag = 1;
				HAL_TIM_Base_Start_IT(bHandler->antiGlitchTimer);
				bHandler->buttonState = right;
				if(appState != state_cellStatusDisplay)
				{
					appState--;
				}
			}
			break;
		case GPIO_PIN_0:
			if(bHandler->timerFlag == 0)
			{
				bHandler->timerFlag = 1;
				HAL_TIM_Base_Start_IT(bHandler->antiGlitchTimer);
				bHandler->buttonState = down;
			}
			break;
		default:
			bHandler->buttonState = 0;
	}
}

