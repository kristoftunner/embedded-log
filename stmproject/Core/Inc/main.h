/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LIFE_LED_Pin GPIO_PIN_2
#define LIFE_LED_GPIO_Port GPIOB
#define BTN_5_Pin GPIO_PIN_11
#define BTN_5_GPIO_Port GPIOF
#define BTN_2_Pin GPIO_PIN_12
#define BTN_2_GPIO_Port GPIOF
#define BTN_3_Pin GPIO_PIN_14
#define BTN_3_GPIO_Port GPIOF
#define BTN_1_Pin GPIO_PIN_15
#define BTN_1_GPIO_Port GPIOF
#define BTN_4_Pin GPIO_PIN_0
#define BTN_4_GPIO_Port GPIOG
#define DISPLAY_PWM_Pin GPIO_PIN_11
#define DISPLAY_PWM_GPIO_Port GPIOE
#define DISPLAY_SCK_Pin GPIO_PIN_10
#define DISPLAY_SCK_GPIO_Port GPIOB
#define DISPLAY_RST_Pin GPIO_PIN_11
#define DISPLAY_RST_GPIO_Port GPIOB
#define DISPLAY_MOSI_Pin GPIO_PIN_15
#define DISPLAY_MOSI_GPIO_Port GPIOB
#define UART7_DE_Pin GPIO_PIN_6
#define UART7_DE_GPIO_Port GPIOG
#define DISPLAY_D_Pin GPIO_PIN_15
#define DISPLAY_D_GPIO_Port GPIOA
#define DISPLAY_CS_Pin GPIO_PIN_3
#define DISPLAY_CS_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
