#include "my_ipc.h"

void main(int argc,char* argv[])
{
    if (argv[1]==NULL){
        argv[1] = "1";
    }
    
    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);
    Msg_buf msg;
    while (1)
    {
        printf("haircraft %s get ready\n",argv[1]);
        msg.mtype = CHAIR_2_SOFA;
        msgsnd(rcv_msq, &msg, MSG_SIZE, WAIT);
        if (msgrcv(snd_msq, &msg, MSG_SIZE, SOFA_2_CHAIR, NO_WAIT)<0)
        {
            printf("haircraft %s sleep for cus\n",argv[1]);
            msgrcv(snd_msq, &msg, MSG_SIZE, SOFA_2_CHAIR, WAIT);
        }

        //working
        printf("haircraft %s working on %d\n", argv[1],msg.mtext);
        sleep(10);
        printf("get %d cut\n", msg.mtext);
    }
}