/*
 * led_control.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#include "led_control.h"

void LED1_Toggle(void) {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void LED2_Toggle(void) {
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

void LED3_Toggle(void) {
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void LED4_Toggle(void) {
    HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void LED_OneShot_On(void) {
    HAL_GPIO_WritePin(LED_ONESHOT_GPIO_Port, LED_ONESHOT_Pin, GPIO_PIN_SET);
}

void LED_OneShot_Off(void) {
    HAL_GPIO_WritePin(LED_ONESHOT_GPIO_Port, LED_ONESHOT_Pin, GPIO_PIN_RESET);
}

