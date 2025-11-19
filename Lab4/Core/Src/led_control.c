/*
 * led_control.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#include "led_control.h"

void LED1_Toggle() {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void LED2_Toggle() {
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

void LED3_Toggle() {
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void LED4_Toggle() {
    HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void LED_OneShot() {
	HAL_GPIO_TogglePin(LED_ONESHOT_GPIO_Port, LED_ONESHOT_Pin);
}

