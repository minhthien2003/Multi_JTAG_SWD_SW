/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f0xx_hal.h"

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
#define LED_4_Pin GPIO_PIN_1
#define LED_4_GPIO_Port GPIOF
#define MODE_Pin GPIO_PIN_0
#define MODE_GPIO_Port GPIOA
#define SEC_A_Pin GPIO_PIN_1
#define SEC_A_GPIO_Port GPIOA
#define EN_A_Pin GPIO_PIN_2
#define EN_A_GPIO_Port GPIOA
#define SEC_B_Pin GPIO_PIN_3
#define SEC_B_GPIO_Port GPIOA
#define EN_B_Pin GPIO_PIN_4
#define EN_B_GPIO_Port GPIOA
#define BIT_C_Pin GPIO_PIN_5
#define BIT_C_GPIO_Port GPIOA
#define BIT_B_Pin GPIO_PIN_6
#define BIT_B_GPIO_Port GPIOA
#define BIT_A_Pin GPIO_PIN_7
#define BIT_A_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_1
#define LED_1_GPIO_Port GPIOB
#define LED_2_Pin GPIO_PIN_9
#define LED_2_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_10
#define LED_3_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
