#ifndef __SYSTASK_H
#define __SYSTASK_H
#include "sys.h"
#include "includes.h"

#define STK_SIZE 128

//START 任务
//设置任务优先级
#define START_TASK_PRIO 10  ///开始任务的优先级为最低
//任务任务堆栈
extern OS_STK START_TASK_STK[STK_SIZE];
//任务函数
void start_task(void *pdata);


//设置任务优先级
#define HANDLE_TASK_PRIO 1
//任务堆栈
extern OS_STK HANDLE_TASK_STK[STK_SIZE];
//任务函数
void handle_task(void *pdata);

//设置任务优先级
#define DISPLAY_TASK_PRIO 2
//任务堆栈
extern OS_STK DISPLAY_TASK_STK[STK_SIZE];
//任务函数
void display_task(void *pdata);

//设置任务优先级
#define LED_TASK_PRIO 3
//任务堆栈
extern OS_STK LED_TASK_STK[STK_SIZE];
//任务函数
void led_task(void *pdata);




//设置任务优先级
#define IWDG_TASK_PRIO 9
//任务堆栈
extern OS_STK IWDG_TASK_STK[STK_SIZE];
//任务函数
void iwdg_task(void *pdata);


#endif


