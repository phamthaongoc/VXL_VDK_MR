/*
 * button.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


#define N_BUTTONS 1
#define LONG_PRESS_TIME 200

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int button_flag[N_BUTTONS];

void getKeyInput(void);
int isButtonPressed(void);


#endif /* INC_BUTTON_H_ */
