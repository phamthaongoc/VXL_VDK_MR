/*
 * button.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET


int isButtonPressed();
void getKeyInput();

void Task_Button_Read(void);
#endif /* INC_BUTTON_H_ */
