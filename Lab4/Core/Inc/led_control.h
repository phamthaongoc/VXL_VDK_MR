/*
 * led_control.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_


#define LED1_GPIO_Port GPIOA
#define LED1_Pin       GPIO_PIN_0

#define LED2_GPIO_Port GPIOA
#define LED2_Pin       GPIO_PIN_1

#define LED3_GPIO_Port GPIOA
#define LED3_Pin       GPIO_PIN_2

#define LED4_GPIO_Port GPIOA
#define LED4_Pin       GPIO_PIN_3

#define LED_ONESHOT_GPIO_Port GPIOA
#define LED_ONESHOT_Pin       GPIO_PIN_4

void LED1_Toggle(void);
void LED2_Toggle(void);
void LED3_Toggle(void);
void LED4_Toggle(void);

void LED_OneShot_On(void);
void LED_OneShot_Off(void);

#endif /* INC_LED_CONTROL_H_ */
