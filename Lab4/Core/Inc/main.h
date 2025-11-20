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
#include "stm32f1xx_hal.h"

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
#define MODE_Pin GPIO_PIN_13
#define MODE_GPIO_Port GPIOC
#define NAV1G_Pin GPIO_PIN_0
#define NAV1G_GPIO_Port GPIOA
#define NAV1Y_Pin GPIO_PIN_1
#define NAV1Y_GPIO_Port GPIOA
#define NAV1R_Pin GPIO_PIN_2
#define NAV1R_GPIO_Port GPIOA
#define NAV2G_Pin GPIO_PIN_3
#define NAV2G_GPIO_Port GPIOA
#define NAV2Y_Pin GPIO_PIN_4
#define NAV2Y_GPIO_Port GPIOA
#define NAV2R_Pin GPIO_PIN_5
#define NAV2R_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_6
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_7
#define EN1_GPIO_Port GPIOA
#define SEG1a_Pin GPIO_PIN_0
#define SEG1a_GPIO_Port GPIOB
#define SEG1b_Pin GPIO_PIN_1
#define SEG1b_GPIO_Port GPIOB
#define SEG1c_Pin GPIO_PIN_2
#define SEG1c_GPIO_Port GPIOB
#define SEG1d_Pin GPIO_PIN_10
#define SEG1d_GPIO_Port GPIOB
#define SEG2e_Pin GPIO_PIN_11
#define SEG2e_GPIO_Port GPIOB
#define SEG2f_Pin GPIO_PIN_12
#define SEG2f_GPIO_Port GPIOB
#define SEG2g_Pin GPIO_PIN_13
#define SEG2g_GPIO_Port GPIOB
#define SET_Pin GPIO_PIN_14
#define SET_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_8
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_9
#define EN3_GPIO_Port GPIOA
#define INCREASE_Pin GPIO_PIN_13
#define INCREASE_GPIO_Port GPIOA
#define SEG1dB3_Pin GPIO_PIN_3
#define SEG1dB3_GPIO_Port GPIOB
#define SEG1e_Pin GPIO_PIN_4
#define SEG1e_GPIO_Port GPIOB
#define SEG1f_Pin GPIO_PIN_5
#define SEG1f_GPIO_Port GPIOB
#define SEG1g_Pin GPIO_PIN_6
#define SEG1g_GPIO_Port GPIOB
#define SEG2a_Pin GPIO_PIN_7
#define SEG2a_GPIO_Port GPIOB
#define SEG2b_Pin GPIO_PIN_8
#define SEG2b_GPIO_Port GPIOB
#define SEG2c_Pin GPIO_PIN_9
#define SEG2c_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
