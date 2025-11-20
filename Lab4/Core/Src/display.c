/*
 * display.c
 *
 *  Created on: Nov 6, 2025
 *      Author: Thao Ngoc
 */

#include <display.h>

const uint8_t segNumber[10] = {
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,
    0x90
};

static int led_buffer[4] = {0, 0, 0, 0};
static int display_index = 0;

void setNumber(int num1, int num2) {
    if (num1 < 0) num1 = 0;
    if (num2 < 0) num2 = 0;
    if (num1 > 99) num1 = 99;
    if (num2 > 99) num2 = 99;

    led_buffer[0] = num1 % 10;
    led_buffer[1] = num1 / 10;
    led_buffer[2] = num2 % 10;
    led_buffer[3] = num2 / 10;
}

static void display7seg_output(uint8_t code, int road) {

    uint8_t mask = 0x01;
    for (int i = 0; i < 7; i++) {
        GPIO_PinState state = ((code & mask) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET;
        mask <<= 1;
        if (road == 1) {
            HAL_GPIO_WritePin(GPIOB, SEG1a_Pin << i, state);
        } else {
            HAL_GPIO_WritePin(GPIOB, SEG2a_Pin << i, state);
        }
    }
}

static void disableAllEN(void) {
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_RESET);
}

void update(int index_led) {
    disableAllEN();

    switch (index_led) {
        case 0:
            display7seg_output(segNumber[led_buffer[1]], 1);
            HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
            display7seg_output(segNumber[led_buffer[3]], 2);
            HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
            break;
        case 1:
            display7seg_output(segNumber[led_buffer[0]], 1);
            HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
            display7seg_output(segNumber[led_buffer[2]], 2);
            HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
            break;

        }
}



void Task_Display_Update(void)
{
    // Toggle between displaying ones and tens place
    display_index = 1-display_index;

    // Call update with current index
    update(display_index);
}
