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
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_RS_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_1
#define LCD_E_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_2
#define LCD_D4_GPIO_Port GPIOB
#define PED1_Pin GPIO_PIN_14
#define PED1_GPIO_Port GPIOB
#define PED2_Pin GPIO_PIN_15
#define PED2_GPIO_Port GPIOB
#define PED1_R_Pin GPIO_PIN_10
#define PED1_R_GPIO_Port GPIOA
#define PED1_G_Pin GPIO_PIN_11
#define PED1_G_GPIO_Port GPIOA
#define PED2_R_Pin GPIO_PIN_12
#define PED2_R_GPIO_Port GPIOA
#define INCREASE_Pin GPIO_PIN_13
#define INCREASE_GPIO_Port GPIOA
#define SET_Pin GPIO_PIN_14
#define SET_GPIO_Port GPIOA
#define PED2_G_Pin GPIO_PIN_15
#define PED2_G_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_3
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_4
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_5
#define LCD_D7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
