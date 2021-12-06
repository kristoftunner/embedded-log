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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define BTN_LEFT_Pin GPIO_PIN_11
#define BTN_LEFT_GPIO_Port GPIOF
#define BTN_LEFT_EXTI_IRQn EXTI15_10_IRQn
#define BTN_UP_Pin GPIO_PIN_12
#define BTN_UP_GPIO_Port GPIOF
#define BTN_UP_EXTI_IRQn EXTI15_10_IRQn
#define BTN_CENTER_Pin GPIO_PIN_14
#define BTN_CENTER_GPIO_Port GPIOF
#define BTN_CENTER_EXTI_IRQn EXTI15_10_IRQn
#define BTN_RIGHT_Pin GPIO_PIN_15
#define BTN_RIGHT_GPIO_Port GPIOF
#define BTN_RIGHT_EXTI_IRQn EXTI15_10_IRQn
#define BTN_DOWN_Pin GPIO_PIN_0
#define BTN_DOWN_GPIO_Port GPIOG
#define BTN_DOWN_EXTI_IRQn EXTI0_IRQn
#define DISPLAY_PWM_Pin GPIO_PIN_11
#define DISPLAY_PWM_GPIO_Port GPIOE
#define DISPLAY_SCK_Pin GPIO_PIN_10
#define DISPLAY_SCK_GPIO_Port GPIOB
#define DISPLAY_RST_Pin GPIO_PIN_11
#define DISPLAY_RST_GPIO_Port GPIOB
#define DISPLAY_MOSI_Pin GPIO_PIN_15
#define DISPLAY_MOSI_GPIO_Port GPIOB
#define PWR_KEY_Pin GPIO_PIN_13
#define PWR_KEY_GPIO_Port GPIOD
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
