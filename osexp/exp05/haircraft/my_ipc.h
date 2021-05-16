#ifndef MY
#define MY

/*
* Filename : ipc.h
* copyright : (C) 2006 by zhonghonglie
* Function : 声明IPC机制的函数原型和全局变量
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
//建立或获取ipc的一组函数的原型说明
int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);

//==========================MSQ======================================
//request msg quene
#define SND_MSQ 1001
//response msg quene
#define RCV_MSQ 1002
#define MSG_SIZE sizeof(int)

#define CUS_2_ROOM 1
#define ROOM_2_CUS 2
#define ROOM_2_SOFA 3
#define SOFA_2_ROOM 4
#define SOFA_TO_CHAIR 5
#define CHAIR_TO_SOFA 6
// #define CHAIR_SND
// #define _SND
// #define _SND
// #define _SND
#define CUS_RCV_T 4
#define ROOM_RCV_T 5
#define SOFA_RCV_T 6
// #define _RCV
// #define _RCV
// #define _RCV
// #define _RCV
#define BUFSZ 256
#define OPEN_ALL IPC_CREAT | 0644

#define ROOM_SEM_ID 2000
#define ROOMSIZE 13
#define SOFA_SEM_ID 2001
#define SOFASIZE 3

#define NO_WAIT IPC_NOWAIT
#define WAIT 0

/*信号灯控制用的共同体*/
typedef union semuns
{
    int val;
} Sem_uns;
/* 消息结构体*/
typedef struct msgbuf
{
    long mtype;
    int mtext;
} Msg_buf;

#endif
