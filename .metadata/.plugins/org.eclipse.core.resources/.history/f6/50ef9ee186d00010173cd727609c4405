
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

static int prev_status = -1;

// ==== PEDESTRIAN SYSTEM ====

// PED1
int ped1_request = 0;
int ped1_active = 0;
int ped1_cycles = 0;     // Đếm 3 chu kỳ
int ped1_state = 0;      // 0: off, 1: red, 2: green

// PED2
int ped2_request = 0;
int ped2_active = 0;
int ped2_cycles = 0;
int ped2_state = 0;


// ROAD1
int road1_start_red = 0;
int road1_start_green = 0;

// ROAD2
int road2_start_red = 0;
int road2_start_green = 0;



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
            case 4: ped1_request = 1; break;
            case 5: ped2_request = 1; break;


        default:
            break;
    }
}
void setPed1LED(int red, int green) {
    HAL_GPIO_WritePin(GPIOA, PED1_R_Pin, red ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, PED1_G_Pin, green ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void setPed2LED(int red, int green) {
    HAL_GPIO_WritePin(GPIOA, PED2_R_Pin, red ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, PED2_G_Pin, green ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void updatePedestrianLED(void) {
    // Nếu không còn active và không có request thì ép tắt state
    if (!ped1_active && !ped1_request) {
        ped1_state = 0;
    }
    if (!ped2_active && !ped2_request) {
        ped2_state = 0;
    }

    // PED1
    if (ped1_state == 0)      setPed1LED(0, 0); // off
    else if (ped1_state == 1) setPed1LED(1, 0); // red
    else if (ped1_state == 2) setPed1LED(0, 1); // green

    // PED2
    if (ped2_state == 0)      setPed2LED(0, 0);
    else if (ped2_state == 1) setPed2LED(1, 0);
    else if (ped2_state == 2) setPed2LED(0, 1);
}

void enterState(int new_state, int r1, int y1, int g1, int r2, int y2, int g2) {
	status = new_state;
	setTrafficLED(r1, y1, g1, r2, y2, g2);


}

void setPedestrianLED(int ped1_color, int ped2_color) {
	// ped1_color: 0=off, 1=red, 2=green
	// ped2_color: 0=off, 1=red, 2=green

	if (ped1_color == 0) {
		HAL_GPIO_WritePin(GPIOA, PED1_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, PED1_G_Pin, GPIO_PIN_SET);
	} else if (ped1_color == 1) {
		HAL_GPIO_WritePin(GPIOA, PED1_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, PED1_G_Pin, GPIO_PIN_SET);
	} else if (ped1_color == 2) {
		HAL_GPIO_WritePin(GPIOA, PED1_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, PED1_G_Pin, GPIO_PIN_RESET);
	}

	if (ped2_color == 0) {
		HAL_GPIO_WritePin(GPIOA, PED2_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, PED2_G_Pin, GPIO_PIN_SET);
	} else if (ped2_color == 1) {
		HAL_GPIO_WritePin(GPIOA, PED2_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, PED2_G_Pin, GPIO_PIN_SET);
	} else if (ped2_color == 2) {
		HAL_GPIO_WritePin(GPIOA, PED2_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, PED2_G_Pin, GPIO_PIN_RESET);
	}
}
void Pedestrian_Init(void) {
    ped1_request = ped2_request = 0;
    ped1_active  = ped2_active  = 0;
    ped1_cycles  = ped2_cycles  = 0;
    ped1_state   = ped2_state   = 0;

    // TẮT HẲN LED PED
    setPed1LED(0, 0);
    setPed2LED(0, 0);
}

void mode_normal() {
		//index++;


			setNumber(led1_time, led2_time);
			if (led1_time > 0) led1_time--;
			if (led2_time > 0) led2_time--;

			switch (status) {
				case AUTO_R1_G2:
					enterState(AUTO_R1_G2, 1, 0, 0, 0, 0, 1);
					//road1_start_red = 1;
					//road2_start_green = 1;
					if (led2_time <= 0) {

						led2_time = yellow_time;
						status = AUTO_R1_Y2;
					}
					break;

				case AUTO_R1_Y2:
					enterState(AUTO_R1_Y2, 1, 0, 0, 0, 1, 0);
					//road1_start_red = 1;

					if (led2_time <= 0) {
						led1_time = green_time;
						led2_time = red_time;
						status = AUTO_G1_R2;
					}
					break;

				case AUTO_G1_R2:
					enterState(AUTO_G1_R2, 0, 0, 1, 1, 0, 0);
					//road2_start_red = 1;
					//road1_start_green = 1;
					if (led1_time <= 0) {
						led1_time = yellow_time;
						status = AUTO_Y1_R2;
					}
					break;

				case AUTO_Y1_R2:
					enterState(AUTO_Y1_R2, 0, 1, 0, 1, 0, 0);
					//road2_start_red = 1;
					if (led1_time <= 0) {
						led1_time = red_time;
						led2_time = green_time;
						status = AUTO_R1_G2;
					}
					break;

				default:
					break;
			}

			// chỉ set flag 1 lần ở đây
			road1_start_red   = (status == AUTO_R1_G2 && prev_status != AUTO_R1_G2);
			road1_start_green = (status == AUTO_G1_R2 && prev_status != AUTO_G1_R2);

			road2_start_red   = (status == AUTO_G1_R2 && prev_status != AUTO_G1_R2);
			road2_start_green = (status == AUTO_R1_G2 && prev_status != AUTO_R1_G2);

			// PED1 — ROAD1
			    if (ped1_request && !ped1_active) {
			        ped1_active = 1;
			        ped1_cycles = 0;
			        ped1_state = 1;   // RED ngay lập tức
			        ped1_request = 0;
			    }

			    // Khi ROAD1 đang đỏ -> PED1 xanh
			    if (ped1_active && ped1_state == 1) {
			        if (road1_start_red) {
			            ped1_state = 2;  // GREEN
			        }
			    }

			    // Khi ROAD1 đỏ kết thúc → hết 1 cycle
			    if (ped1_active && ped1_state == 2) {
			        if (road1_start_green) {
			            ped1_cycles++;
			            if (ped1_cycles >= 3) {
			                ped1_active = 0;
			                ped1_state = 0;   // tắt
			            } else {
			                ped1_state = 1;   // quay lại đỏ
			            }
			        }
			    }

			    // PED2 — ROAD2
			    if (ped2_request && !ped2_active) {
			        ped2_active = 1;
			        ped2_cycles = 0;
			        ped2_state = 1;   // RED ngay lập tức
			        ped2_request = 0;
			    }

			    // ROAD2 red → PED2 green
			    if (ped2_active && ped2_state == 1) {
			        if (road2_start_red) {
			            ped2_state = 2;  // GREEN
			        }
			    }

			    // ROAD2 red kết thúc → hết 1 cycle
			    if (ped2_active && ped2_state == 2) {
			        if (road2_start_green) {
			            ped2_cycles++;
			            if (ped2_cycles >= 3) {
			                ped2_active = 0;
			                ped2_state = 0;   // tắt
			            } else {
			                ped2_state = 1;   // quay lại đỏ
			            }
			        }
			    }

			    // ==== ÁP LED RA GPIO CHỈ 1 LẦN / TICK ====
			    updatePedestrianLED();

			    prev_status = status;

				road1_start_red = 0;
				road2_start_red = 0;
				road1_start_green = 0;   // 🔥 MUST RESET
				road2_start_green = 0;   // 🔥 MUST RESET


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
           // pedestrian_fsm_road1();
           // pedestrian_fsm_road2();

            break;
       // case MODE_5:
             //   pedestrian_fsm_road1();
              //  pedestrian_fsm_road2();
            //    break;
         default:
            // mode 2/3/4 đã do Task_BlinkLED xử lý
            break;
    }


}

void Task_BlinkLED() {
    switch (mode) {
        case MODE_2: blinkLED(1, 0, 0); //check_button();
        break;
        case MODE_3: blinkLED(0, 1, 0); // check_button();
        break;
        case MODE_4: blinkLED(0, 0, 1); //check_button();
        break;
        default: break;
    }
}

