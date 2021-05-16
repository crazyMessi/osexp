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

#define BUFSZ 256
#define MSG_SIZE 1
#define MSG_FLG 0
#define MSGTYPE 1

//建立或获取ipc的一组函数的原型说明
int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);

/*信号灯控制用的共同体*/
typedef union semuns
{
    int val;
} Sem_uns;
/* 消息结构体*/
typedef struct msgbuf
{
    long mtype;
    char mtext[1];
} Msg_buf;

//smoker&producer sharing the library
key_t library_id;
int library_size;
char *library_ptr;

// //smoker&producer sharing the library
// key_t wpos;
// int w_size;
// char* w_ptr;

// //smoker&producer sharing the library
// key_t rpos = 300;
// int r_size = 1;
// char* r_ptr;

//signal for producer
key_t prod_key;
key_t pmtx_key;
int prod_sem;
int pmtx_sem;

//signal for smoker
key_t cmtx_key[3];
int cmtx_sem[3];

//sign val
int sem_val;

//msg
key_t msq;

int sem_flg;
int shm_flg;
int msq_flag;

#endif
