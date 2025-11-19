/*
 * button.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define N_BUTTONS 1
#define LONG_PRESS_TIME 200

#define NORMAL_STATE  1
#define PRESSED_STATE 0

extern int button_flag ;

void getKeyInput(void);
int isButtonPressed(void);


#endif /* INC_BUTTON_H_ */
