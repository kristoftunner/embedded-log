#include "log.h"
#include "stm32f7xx_hal_uart.h"

char g_log_buff[512];

extern UART_HandleTypeDef huart5;

void MID_LOG_Put(const char *str)
{
	HAL_UART_Transmit(&huart5, (uint8_t *)str, strlen(str), 100);
}

void MID_LOG_Init(void)
{
	log_init(g_log_buff, sizeof(g_log_buff), MID_LOG_Put);
}
