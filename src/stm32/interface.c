/*
 * interface.c
 *
 *  Created on: Oct 31, 2021
 *      Author: kristoft
 */

#include "main.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_spi.h"

#include "interface.h"

extern SPI_HandleTypeDef hspi2;

/*Set Reset functions for Display D/C pin*/
inline void Ili_Set_D()
{
	HAL_GPIO_WritePin(DISPLAY_D_GPIO_Port, DISPLAY_D_Pin, GPIO_PIN_SET);
}

inline void Ili_Reset_D()
{
	HAL_GPIO_WritePin(DISPLAY_D_GPIO_Port, DISPLAY_D_Pin, GPIO_PIN_RESET);
}

/*Set, reset functions for Display Chip Select signal*/
inline void Ili_Set_Cs()
{
	HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_SET);
}

inline void Ili_Reset_Cs()
{
	HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_RESET);
}

/*Set, reset funcitons for Display hardware reset pin*/
inline void Ili_Set_HWRST()
{
	HAL_GPIO_WritePin(GPIOB, DISPLAY_RST_Pin, GPIO_PIN_RESET);
}

inline void Ili_Reset_HWRST()
{
	HAL_GPIO_WritePin(GPIOB, DISPLAY_RST_Pin, GPIO_PIN_SET);
}

/*Delay function - using HAL delay*/
inline void Ili_dly_ms(uint16_t ms)
{
	HAL_Delay(ms);
}

/*SPI wrapper function over HAL library*/
inline int Ili_Spi_Send(uint8_t data)
{
	switch(HAL_SPI_Transmit(&hspi2, &data, 1, 0))
	{
	case HAL_OK:
		return 0;
	default:
		return -1;
	}
}

/*SPI wrapper function over HAL library*/
inline uint8_t Ili_Spi_Read()
{
	uint8_t *data;
	HAL_StatusTypeDef temp;
	temp = HAL_SPI_Receive(&hspi2, data, 1, 100);
	return *data;
}
