/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define encode1_Pin GPIO_PIN_0
#define encode1_GPIO_Port GPIOA
#define encode1A1_Pin GPIO_PIN_1
#define encode1A1_GPIO_Port GPIOA
#define arm1_Pin GPIO_PIN_2
#define arm1_GPIO_Port GPIOA
#define arm1A3_Pin GPIO_PIN_3
#define arm1A3_GPIO_Port GPIOA
#define encode2_Pin GPIO_PIN_5
#define encode2_GPIO_Port GPIOA
#define chassis1_Pin GPIO_PIN_6
#define chassis1_GPIO_Port GPIOA
#define chassis1A7_Pin GPIO_PIN_7
#define chassis1A7_GPIO_Port GPIOA
#define chassis2_Pin GPIO_PIN_0
#define chassis2_GPIO_Port GPIOB
#define chassis2B1_Pin GPIO_PIN_1
#define chassis2B1_GPIO_Port GPIOB
#define paw_Pin GPIO_PIN_14
#define paw_GPIO_Port GPIOB
#define pawB15_Pin GPIO_PIN_15
#define pawB15_GPIO_Port GPIOB
#define arm2_Pin GPIO_PIN_9
#define arm2_GPIO_Port GPIOA
#define encode2B3_Pin GPIO_PIN_3
#define encode2B3_GPIO_Port GPIOB
#define chassis3_Pin GPIO_PIN_6
#define chassis3_GPIO_Port GPIOB
#define chassis3B7_Pin GPIO_PIN_7
#define chassis3B7_GPIO_Port GPIOB
#define chassis4_Pin GPIO_PIN_8
#define chassis4_GPIO_Port GPIOB
#define chassis4B9_Pin GPIO_PIN_9
#define chassis4B9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
