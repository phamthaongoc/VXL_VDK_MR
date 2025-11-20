/*
 * fsm.c - Traffic Light FSM using Scheduler instead of Timer
 *
 * Changes from timer-based:
 * - timer1_flag được thay bằng periodic scheduler tasks
 * - timerRun() không cần thiết nữa
 * - Tasks được gọi từ SCH_Dispatch_Tasks()
 */

#include "fsm.h"
#include "scheduler.h"

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

// Forward declarations of scheduler tasks
void Task_FSM_Normal(void);
void Task_FSM_Blink(void);
void Task_Button_Scan(void);

/*
 * ================================================================
 * Khởi tạo FSM với Scheduler
 * Được gọi một lần trong main()
 * ================================================================
 */
void FSM_Init(void)
{
    // Add periodic tasks to scheduler
    // Task FSM Normal: chạy mỗi 500ms (50 ticks)
    SCH_Add_Task(Task_FSM_Normal, 0, 50);

    // Task FSM Blink: chạy mỗi 250ms (25 ticks)
    SCH_Add_Task(Task_FSM_Blink, 0, 25);

    // Task Button Scan: chạy mỗi 10ms (1 tick) - để debounce
    SCH_Add_Task(Task_Button_Scan, 0, 1);

    // Initialize first state
    status = AUTO_R1_G2;
    setTrafficLED(1, 0, 0, 0, 0, 1);
}

/*
 * ================================================================
 * GPIO Control - Set Traffic LEDs
 * ================================================================
 */
void setTrafficLED(int r1, int y1, int g1, int r2, int y2, int g2)
{
    HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, r1 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, y1 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, g1 ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, r2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, y2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, g2 ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

/*
 * ================================================================
 * Button Handling - Non-blocking via Scheduler
 * ================================================================
 * Được gọi mỗi 10ms từ scheduler
 */
void check_button(void)
{
    int button_event = isButtonPressed();
    switch (button_event) {
        case 1: // Button MODE - Chuyển mode
            next = (next + 1) % 4;
            mode = MODE_1 + next;
            cnt = 0;
            flag = 1;
            break;

        case 2: // Button INCREASE - Tăng counter
            if (flag) cnt++;
            if (cnt > 99) cnt = 0;
            break;

        case 3: // Button SET - Lưu giá trị
            switch (mode) {
                case MODE_2:
                    red_time = cnt;
                    mode = MODE_3;
                    break;
                case MODE_3:
                    yellow_time = cnt;
                    mode = MODE_4;
                    break;
                case MODE_4:
                    green_time = cnt;
                    // Validate: red_time phải = yellow_time + green_time
                    if (red_time != yellow_time + green_time) {
                        red_time = 5;
                        yellow_time = 2;
                        green_time = 3;
                    }
                    mode = MODE_1;
                    break;
                default:
                    break;
            }
            cnt = 0;
            break;

        default:
            break;
    }
}

/*
 * ================================================================
 * State Management
 * ================================================================
 */
void enterState(int new_state, int r1, int y1, int g1, int r2, int y2, int g2)
{
    status = new_state;
    setTrafficLED(r1, y1, g1, r2, y2, g2);
}

/*
 * ================================================================
 * MODE 1: Normal Auto Mode - Periodic Task (500ms)
 * ================================================================
 * Được gọi mỗi 500ms từ scheduler
 * Tương đương cũ: if (timer1_flag == 1) trong mode_normal()
 */
void Task_FSM_Normal(void)
{
    // Chỉ chạy khi mode = MODE_1 (auto mode)
    if (mode != MODE_1) return;

    // Decrease timers
    if (led1_time > 0) led1_time--;
    if (led2_time > 0) led2_time--;

    // Update display
    setNumber(led1_time, led2_time);

    // FSM state machine
    switch (status) {
        case AUTO_R1_G2:
            // NAV1: Red, NAV2: Green
            enterState(AUTO_R1_G2, 1, 0, 0, 0, 0, 1);
            if (led2_time <= 0) {
                led2_time = yellow_time;
                status = AUTO_R1_Y2;
            }
            break;

        case AUTO_R1_Y2:
            // NAV1: Red, NAV2: Yellow
            enterState(AUTO_R1_Y2, 1, 0, 0, 0, 1, 0);
            if (led2_time <= 0) {
                led1_time = green_time;
                led2_time = red_time;
                status = AUTO_G1_R2;
            }
            break;

        case AUTO_G1_R2:
            // NAV1: Green, NAV2: Red
            enterState(AUTO_G1_R2, 0, 0, 1, 1, 0, 0);
            if (led1_time <= 0) {
                led1_time = yellow_time;
                status = AUTO_Y1_R2;
            }
            break;

        case AUTO_Y1_R2:
            // NAV1: Yellow, NAV2: Red
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
    update(index % 2);
}

/*
 * ================================================================
 * MODE 2-4: Blink Mode - Periodic Task (250ms)
 * ================================================================
 * Được gọi mỗi 250ms từ scheduler
 * Tương đương cũ: if (timer1_flag) trong blinkLED()
 */
void Task_FSM_Blink(void)
{
    // Chỉ chạy khi mode là MODE_2, MODE_3, hoặc MODE_4
    if (mode == MODE_1) return;

    // Toggle blink state
    blink_state = !blink_state;

    // Update display
    setNumber(mode + 1, cnt);

    // Control which LEDs blink
    switch (mode) {
        case MODE_2:
            // Blink RED on both NAV
            if (blink_state) {
                HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, GPIO_PIN_RESET);
            } else {
                HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, GPIO_PIN_SET);
            }
            // Keep other LEDs OFF
            HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, GPIO_PIN_SET);
            break;

        case MODE_3:
            // Blink YELLOW on both NAV
            if (blink_state) {
                HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, GPIO_PIN_RESET);
            } else {
                HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, GPIO_PIN_SET);
            }
            // Keep other LEDs OFF
            HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, GPIO_PIN_SET);
            break;

        case MODE_4:
            // Blink GREEN on both NAV
            if (blink_state) {
                HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, GPIO_PIN_RESET);
            } else {
                HAL_GPIO_WritePin(GPIOA, NAV1G_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOA, NAV2G_Pin, GPIO_PIN_SET);
            }
            // Keep other LEDs OFF
            HAL_GPIO_WritePin(GPIOA, NAV1R_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV1Y_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2R_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, NAV2Y_Pin, GPIO_PIN_SET);
            break;

        default:
            break;
    }
    update(index);
}

/*
 * ================================================================
 * Button Scan Task - Periodic Task (10ms)
 * ================================================================
 * Được gọi mỗi 10ms từ scheduler
 * Handles debounce via button.c (getKeyInput)
 */
void Task_Button_Scan(void)
{
    // Call getKeyInput for debounce (mỗi 10ms)
    getKeyInput();

    // Check button events
    check_button();
}

/*
 * ================================================================
 * Main FSM Dispatcher - Called from main loop
 * ================================================================
 * Thay thế cũ: fsm_for_input_processing()
 * Bây giờ không cần gọi vì tasks được quản lý bởi scheduler
 */
void fsm_for_input_processing(void)
{
    // Bây giờ FSM được quản lý bởi scheduler tasks
    // Không cần gọi thủ công nữa
    // Tất cả xử lý đã được chuyển sang tasks:
    // - Task_FSM_Normal (500ms)
    // - Task_FSM_Blink (250ms)
    // - Task_Button_Scan (10ms)
}
