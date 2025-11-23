
#include "fsm.h"

int status = AUTO_R1_G2;
int mode = MODE_1;

static int led1_time = 5;
static int led2_time = 3;
static int blink_state = 0;

static int red_time = 5;
static int yellow_time = 2;
static int green_time = 3;

static int cnt = 0;
static int flag = 1;
static int index = 1;
static int next = 0;

void setTrafficLED(int r1, int y1, int g1, int r2, int y2, int g2) {
	HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, r1 ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, y1 ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, g1 ? GPIO_PIN_RESET : GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, r2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, y2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, g2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void check_button() {
    int button_event = isButtonPressed();
    if (button_event == 0) {
            return;
        }
    switch (button_event) {
        case 1: // MODE
            next = (next + 1) % 4;
            mode = MODE_1 + next;

            cnt = 0;

            // Chỉ bật flag nếu là mode chỉnh
            if (mode == MODE_2 || mode == MODE_3 || mode == MODE_4)
                flag = 1;
            else
                flag = 0;

            break;

        case 2: // INCREASE
            if (flag) cnt++;
            if (cnt > 99) cnt = 0;
            break;

        case 3: // SET
            switch (mode) {
                case MODE_2:
                    red_time = cnt;
                    mode = MODE_3;
                    next = mode - MODE_1;   // <--- FIX
                    cnt = 0;
                    break;

                case MODE_3:
                    yellow_time = cnt;
                    mode = MODE_4;
                    next = mode - MODE_1;   // <--- FIX

                    cnt = 0;
                    break;

                case MODE_4:
                    green_time = cnt;

                    // check điều kiện hợp lệ
                    if (red_time != yellow_time + green_time) {
                        red_time = 5;
                        yellow_time = 2;
                        green_time = 3;
                    }

                    // quay về MODE_1
                    mode = MODE_1;
                    next = 0;
                    cnt = 0;
                    flag = 0;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}


void enterState(int new_state, int r1, int y1, int g1, int r2, int y2, int g2) {
	status = new_state;
	setTrafficLED(r1, y1, g1, r2, y2, g2);
}

void mode_normal() {
		//index++;


			setNumber(led1_time, led2_time);
			if (led1_time > 0) led1_time--;
			if (led2_time > 0) led2_time--;



			switch (status) {
				case AUTO_R1_G2:
					enterState(AUTO_R1_G2, 1, 0, 0, 0, 0, 1);
					if (led2_time <= 0) {

						led2_time = yellow_time;
						status = AUTO_R1_Y2;
					}
					break;

				case AUTO_R1_Y2:
					enterState(AUTO_R1_Y2, 1, 0, 0, 0, 1, 0);
					if (led2_time <= 0) {
						led1_time = green_time;
						led2_time = red_time;
						status = AUTO_G1_R2;
					}
					break;

				case AUTO_G1_R2:
					enterState(AUTO_G1_R2, 0, 0, 1, 1, 0, 0);
					if (led1_time <= 0) {
						led1_time = yellow_time;
						status = AUTO_Y1_R2;
					}
					break;

				case AUTO_Y1_R2:
					enterState(AUTO_Y1_R2, 0, 1, 0, 1, 0, 0);
					if (led1_time <= 0) {
						led1_time = red_time;
						led2_time = green_time;
						status = AUTO_R1_G2;
					}
					break;

				default:
					break;
			}

		//update(index % 2);

}

void blinkLED(int red, int yellow, int green) {
		index = (index + 1) % 2;
		setNumber(mode + 1, cnt);

		blink_state = !blink_state;

		if (red) {
			HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, GPIO_PIN_SET);
		}

		if (yellow) {
			HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, GPIO_PIN_SET);
		}

		if (green) {
			HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, blink_state ? GPIO_PIN_RESET : GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, GPIO_PIN_SET);
		}

		//update(index);

}

void Task_FSM() {
	// check_button();
    switch (mode) {
        case MODE_1:
            mode_normal();
            break;
         default:
            // mode 2/3/4 đã do Task_BlinkLED xử lý
            break;
    }


}

void Task_BlinkLED() {
    switch (mode) {
        case MODE_2: blinkLED(1, 0, 0);//check_button();
        break;
        case MODE_3: blinkLED(0, 1, 0);// check_button();
        break;
        case MODE_4: blinkLED(0, 0, 1); //check_button();
        break;
        default: break;
    }
}

