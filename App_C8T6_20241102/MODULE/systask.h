#ifndef __SYSTASK_H
#define __SYSTASK_H
#include "sys.h"
#include "includes.h"

#define STK_SIZE 128

//START ����
//�����������ȼ�
#define START_TASK_PRIO 10  ///��ʼ��������ȼ�Ϊ���
//���������ջ
extern OS_STK START_TASK_STK[STK_SIZE];
//������
void start_task(void *pdata);


//�����������ȼ�
#define HANDLE_TASK_PRIO 5
//�����ջ
extern OS_STK HANDLE_TASK_STK[STK_SIZE];
//������
void handle_task(void *pdata);

//�����������ȼ�
#define DISPLAY_TASK_PRIO 6
//�����ջ
extern OS_STK DISPLAY_TASK_STK[STK_SIZE];
//������
void display_task(void *pdata);

//�����������ȼ�
#define WATCH_TASK_PRIO 3
//�����ջ
extern OS_STK WATCH_TASK_STK[STK_SIZE];
//������
void watch_task(void *pdata);

//�����������ȼ�
#define LED_TASK_PRIO 4
//�����ջ
extern OS_STK LED_TASK_STK[STK_SIZE];
//������
void led_task(void *pdata);




//�����������ȼ�
#define IWDG_TASK_PRIO 9
//�����ջ
extern OS_STK IWDG_TASK_STK[STK_SIZE];
//������
void iwdg_task(void *pdata);


typedef enum {
    WRITE_SUCCESS,
    WRITE_FAIL,
    USER_EXISTED,
    READ_SUCCESS,
    READ_FAIL,
    NORMAL,
	VALIDATION_LOCAL,
    VALIDATION_REMOTE,
    VALIDATION,
    CARD_DISABLE,
    VALIDATION_FAIL,
    OLED_DEBUG,
} State;

extern State CurrentState;


#endif


