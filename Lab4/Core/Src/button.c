/*
 * button.c
 *
 *  Created on: Nov 6, 2025
 *      Author: Thao Ngoc 
 */


#include "button.h"
#include "fsm.h"

#define N_BUTTONS 5
#define LONG_PRESS_TIME 200

volatile int button_flag[N_BUTTONS] = {0};
volatile int button_state[N_BUTTONS] = {NORMAL_STATE};
int button_buffer1[N_BUTTONS];
int button_buffer2[N_BUTTONS];
int button_buffer3[N_BUTTONS];
int press_timer[N_BUTTONS];

void subKeyProcess(int index) {
	button_flag[index] = 1;
}

int isButtonPressed() {
	for (int i = 0; i < N_BUTTONS; i++) {
		if (button_flag[i]) {
			button_flag[i] = 0;
			return i + 1;
		}
	}
	return 0;
}

int isPedestrianButtonPressed() {
	// Chỉ kiểm tra PED1 (index 3) và PED2 (index 4)
	for (int i = 3; i < N_BUTTONS; i++) {
		if (button_flag[i]) {
			button_flag[i] = 0;
			return i - 2;  // Return 1 for PED1, 2 for PED2
		}
	}
	return 0;
}

void getKeyInput() {
	// MODE
	button_buffer1[0] = button_buffer2[0];
	button_buffer2[0] = button_buffer3[0];
	button_buffer3[0] = HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);

	//INCREASE
	button_buffer1[1] = button_buffer2[1];
	button_buffer2[1] = button_buffer3[1];
	button_buffer3[1] = HAL_GPIO_ReadPin(INCREASE_GPIO_Port, INCREASE_Pin);

	// SET
	button_buffer1[2] = button_buffer2[2];
	button_buffer2[2] = button_buffer3[2];
	button_buffer3[2] = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);

	// PED1
	button_buffer1[3] = button_buffer2[3];
	button_buffer2[3] = button_buffer3[3];
	button_buffer3[3] = HAL_GPIO_ReadPin(PED1_GPIO_Port, PED1_Pin);

	// PED2
	button_buffer1[4] = button_buffer2[4];
	button_buffer2[4] = button_buffer3[4];
	button_buffer3[4] = HAL_GPIO_ReadPin(PED2_GPIO_Port, PED2_Pin);


	for (int i = 0; i < N_BUTTONS; i++) {
		if ((button_buffer1[i] == button_buffer2[i]) && (button_buffer2[i] == button_buffer3[i])) {
			if (button_state[i] != button_buffer3[i]) {
				button_state[i] = button_buffer3[i];
				if (button_state[i] == PRESSED_STATE) {
					subKeyProcess(i);
					press_timer[i] = LONG_PRESS_TIME;
				}
			} else {
				if (button_state[i] == PRESSED_STATE) {
					if (press_timer[i] > 0) {
						press_timer[i]--;

					//}// else {
						//subKeyProcess(i);  // auto repeat
						//press_timer[i] = LONG_PRESS_TIME;
					}
				}
			}
		}
	}
}


void Task_Button_Read(void) {
    getKeyInput();
    check_button();
   // check_pedestrian_button();
}
