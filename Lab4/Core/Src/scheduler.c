/*
 * scheduler.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Thao Ngoc
 */


#include "scheduler.h"

sTask SCH_tasks[SCH_MAX_TASKS];
volatile uint32_t tick_ms = 0;

//extern void SCH_Hook_Tick_LED(void);

void SCH_Init(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks[i].pTask = 0;
        SCH_tasks[i].Delay = 0;
        SCH_tasks[i].Period = 0;
        SCH_tasks[i].RunMe = 0;
    }
}

void SCH_Update(void)   // gọi mỗi 10 ms từ timer
{
    tick_ms += 10;

    //SCH_Hook_Tick_LED(); // Nháy LED báo scheduler chạy

    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks[i].pTask) {
            if (SCH_tasks[i].Delay == 0) {
                SCH_tasks[i].RunMe++;
                if (SCH_tasks[i].Period > 0)
                    SCH_tasks[i].Delay = SCH_tasks[i].Period;
            } else {
                SCH_tasks[i].Delay--;
            }
        }
    }
}

void SCH_Dispatch_Tasks(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks[i].RunMe > 0) {
            (*SCH_tasks[i].pTask)();
            SCH_tasks[i].RunMe--;

            if (SCH_tasks[i].Period == 0) {
                SCH_Delete_Task(i);
            }
        }
    }
}

uint8_t SCH_Add_Task(TaskFunction_t pFunction, uint32_t DELAY, uint32_t PERIOD)
{
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks[i].pTask == 0) {
            SCH_tasks[i].pTask  = pFunction;
            SCH_tasks[i].Delay  = DELAY;
            SCH_tasks[i].Period = PERIOD;
            SCH_tasks[i].RunMe  = 0;
            return i;
        }
    }
    return NO_TASK_ID;
}

uint8_t SCH_Delete_Task(uint8_t id)
{
    if (id >= SCH_MAX_TASKS) return 1;

    SCH_tasks[id].pTask = 0;
    SCH_tasks[id].Delay = 0;
    SCH_tasks[id].Period = 0;
    SCH_tasks[id].RunMe = 0;

    return 0;
}
