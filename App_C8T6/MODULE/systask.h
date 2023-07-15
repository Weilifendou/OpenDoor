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
#define HANDLE_TASK_PRIO 1
//�����ջ
extern OS_STK HANDLE_TASK_STK[STK_SIZE];
//������
void handle_task(void *pdata);

//�����������ȼ�
#define DISPLAY_TASK_PRIO 2
//�����ջ
extern OS_STK DISPLAY_TASK_STK[STK_SIZE];
//������
void display_task(void *pdata);

//�����������ȼ�
#define LED_TASK_PRIO 3
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


#endif

