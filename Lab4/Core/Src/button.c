/*
 * Logic:
 * - Nhấn xuống: toggle ngay (one toggle)
 * - Giữ 2s: toggle lần nữa (auto repeat)
 * - Giữ thêm 2s: toggle tiếp...
 * - Nhả trước 2s: không toggle thêm
 */

#include "button.h"

#define LONG_PRESS_TIME 200   // 200 * 10ms = 2s

int buffer1 = NORMAL_STATE;
int buffer2 = NORMAL_STATE;
int buffer3 = NORMAL_STATE;

int button_state = NORMAL_STATE;

int press_timer = 0;
int long_press_started = 0;

int button_flag = 0;

void subKeyProcess() {
    button_flag = 1;  // toggle event
}

int isButtonPressed() {
    if (button_flag) {
        button_flag = 0;
        return 1;
    }
    return 0;
}

void getKeyInput() {

    // Debounce
    buffer1 = buffer2;
    buffer2 = buffer3;
    buffer3 = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

    if (buffer1 == buffer2 && buffer2 == buffer3) {

        // ---------------------------
        //  NHẤN XUỐNG → TOGGLE NGAY
        // ---------------------------
        if (button_state == NORMAL_STATE && buffer3 == PRESSED_STATE) {
            button_state = PRESSED_STATE;

            subKeyProcess();          // toggle ngay
            press_timer = LONG_PRESS_TIME;
            long_press_started = 1;   // đã bắt đầu long press
        }

        // ---------------------------
        //  ĐANG GIỮ NÚT
        // ---------------------------
        else if (button_state == PRESSED_STATE && buffer3 == PRESSED_STATE) {

            if (press_timer > 0) {
                press_timer--;
            }
            else {
                // đủ 2s → toggle tiếp
                subKeyProcess();
                press_timer = LONG_PRESS_TIME; // reset để auto repeat
            }
        }

        // ---------------------------
        //  THẢ NÚT
        // ---------------------------
        else if (button_state == PRESSED_STATE && buffer3 == NORMAL_STATE) {
            button_state = NORMAL_STATE;

            // Nếu chưa từng giữ đủ 2s, thì short press không toggle thêm
            press_timer = 0;
            long_press_started = 0;
        }
    }
}
