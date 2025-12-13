/*
 * lcd_parallel.h
 *
 *  Created on: Dec 9, 2025
 *      Author: kiman
 */

#ifndef INC_LCD_PARALLEL_H_
#define INC_LCD_PARALLEL_H_
#include "main.h"

#include "stm32f1xx_hal.h"

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Send_Cmd(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Send_String(const char *str);
void LCD_GotoXY(uint8_t row, uint8_t col);

#endif /* INC_LCD_PARALLEL_H_ */
