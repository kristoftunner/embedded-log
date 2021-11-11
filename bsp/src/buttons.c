/*
 * buttons.c
 *
 *  Created on: Nov 10, 2021
 *      Author: krist
 */
#include "main.h"
#include "stm32f7xx_hal_gpio.h"

/* 1 - left
 * 2 - up
 * 3 - center
 * 4 - right
 * 5 - down*/

uint8_t buttonState = 0;

static enum positions{
	left = 1,
	up = 2,
	center = 3,
	right = 4,
	down = 5
};

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
			buttonState = left;
			break;
		case GPIO_PIN_12:
			buttonState = up;
			break;
		case GPIO_PIN_14:
			buttonState = center;
			break;
		case GPIO_PIN_15:
			buttonState = right;
			break;
		case GPIO_PIN_0:
			buttonState = down;
			break;
		default:
			buttonState = 0;
	}
}

