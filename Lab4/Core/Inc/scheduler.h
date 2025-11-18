/*
 * scheduler.h
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include <stdint.h>

#define SCH_MAX_TASKS 10
#define NO_TASK_ID 255

typedef void (*TaskFunction_t)(void);

typedef struct {
    TaskFunction_t pTask;
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
} sTask;

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Add_Task(TaskFunction_t pFunction, uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint8_t taskID);

#endif /* INC_SCHEDULER_H_ */
