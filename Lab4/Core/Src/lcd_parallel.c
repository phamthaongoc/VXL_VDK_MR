/*
 * lcd_parallel.c
 *
 *  Created on: Dec 9, 2025
 *      Author: kiman
 */

#include "lcd_parallel.h"

#define RS_Pin     LCD_RS_Pin
#define RS_Port    LCD_RS_GPIO_Port
#define E_Pin      LCD_E_Pin
#define E_Port     LCD_E_GPIO_Port
#define D4_Pin     LCD_D4_Pin
#define D4_Port    LCD_D4_GPIO_Port
#define D5_Pin     LCD_D5_Pin
#define D5_Port    LCD_D5_GPIO_Port
#define D6_Pin     LCD_D6_Pin
#define D6_Port    LCD_D6_GPIO_Port
#define D7_Pin     LCD_D7_Pin
#define D7_Port    LCD_D7_GPIO_Port

void LCD_EnablePulse() {
    HAL_GPIO_WritePin(E_Port, E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(E_Port, E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void LCD_Send4Bits(uint8_t data) {
    HAL_GPIO_WritePin(D4_Port, D4_Pin, (data >> 0) & 1);
    HAL_GPIO_WritePin(D5_Port, D5_Pin, (data >> 1) & 1);
    HAL_GPIO_WritePin(D6_Port, D6_Pin, (data >> 2) & 1);
    HAL_GPIO_WritePin(D7_Port, D7_Pin, (data >> 3) & 1);
}

void LCD_Send_Cmd(uint8_t cmd) {
    HAL_GPIO_WritePin(RS_Port, RS_Pin, GPIO_PIN_RESET);

    LCD_Send4Bits(cmd >> 4);
    LCD_EnablePulse();
    LCD_Send4Bits(cmd & 0x0F);
    LCD_EnablePulse();
}

void LCD_Send_Data(uint8_t data) {
    HAL_GPIO_WritePin(RS_Port, RS_Pin, GPIO_PIN_SET);

    LCD_Send4Bits(data >> 4);
    LCD_EnablePulse();
    LCD_Send4Bits(data & 0x0F);
    LCD_EnablePulse();
}

void LCD_Send_String(const char *str) {
    while (*str) LCD_Send_Data(*str++);
}

void LCD_GotoXY(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? col : (0x40 + col);
    LCD_Send_Cmd(0x80 | addr);
}

void LCD_Clear(void) {
    LCD_Send_Cmd(0x01);
    HAL_Delay(3);
}

void LCD_Init(void) {
    HAL_Delay(40);

    LCD_Send4Bits(0x03);
    LCD_EnablePulse();
    LCD_Send4Bits(0x03);
    LCD_EnablePulse();
    LCD_Send4Bits(0x03);
    LCD_EnablePulse();

    LCD_Send4Bits(0x02);
    LCD_EnablePulse();

    LCD_Send_Cmd(0x28);
    LCD_Send_Cmd(0x0C);
    LCD_Send_Cmd(0x06);

    LCD_Clear();
}

