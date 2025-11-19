/*
 * button.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */


#include "button.h"

int button_flag[N_BUTTONS] = {0};

int button_state[N_BUTTONS] = {NORMAL_STATE};
int button_buffer1[N_BUTTONS];
int button_buffer2[N_BUTTONS];
int button_buffer3[N_BUTTONS];
int press_timer[N_BUTTONS];
int last_button_state[N_BUTTONS] = {NORMAL_STATE};

void subKeyProcess(int index) {
    button_flag[index] = 1;
}

int isButtonPressed() {
    if (button_flag[0]) {
        button_flag[0] = 0;
        return 1;
    }
    return 0;
}

void getKeyInput() {

    button_buffer1[0] = button_buffer2[0];
    button_buffer2[0] = button_buffer3[0];
    button_buffer3[0] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

    if ((button_buffer1[0] == button_buffer2[0]) &&
        (button_buffer2[0] == button_buffer3[0])) {

        if (button_state[0] != button_buffer3[0]) {
            button_state[0] = button_buffer3[0];

            if (button_state[0] == PRESSED_STATE && last_button_state[0] == NORMAL_STATE) {
                subKeyProcess(0);
                press_timer[0] = LONG_PRESS_TIME;
            }
        } else {
            if (button_state[0] == PRESSED_STATE) {
                if (press_timer[0] > 0) press_timer[0]--;
                else {
                    subKeyProcess(0);
                    press_timer[0] = LONG_PRESS_TIME;
                }
            }
        }
        last_button_state[0] = button_state[0];
    }
}
