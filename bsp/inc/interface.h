/*
 * interface.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kristoft
 */

#ifndef STM32_INTERFACE_H_
#define STM32_INTERFACE_H_

void Ili_Set_D();
void Ili_Reset_D();
void Ili_Set_Cs();
void Ili_Reset_Cs();
void Ili_Reset_HWRST();
void Ili_Set_HWRST();
void Ili_dly_ms(uint16_t ms);
int Ili_Spi_Send(uint8_t data);
uint8_t Ili_Spi_Read();

#endif /* STM32_INTERFACE_H_ */
