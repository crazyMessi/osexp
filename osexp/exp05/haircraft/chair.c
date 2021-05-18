#include "my_ipc.h"

void main()
{

    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);
    Msg_buf msg;
    while (1)
    {
        printf("haircraft get ready\n");
        msg.mtype = CHAIR_2_SOFA;
        msgsnd(rcv_msq, &msg, MSG_SIZE, WAIT);
        if (msgrcv(snd_msq, &msg, MSG_SIZE, SOFA_2_CHAIR, NO_WAIT)<0)
        {
            printf("sleep for cus\n");
            msgrcv(snd_msq, &msg, MSG_SIZE, SOFA_2_CHAIR, WAIT);
        }
        //working
        printf("working on %d\n", msg.mtext);
        sleep(1);
        printf("get %d cut\n", msg.mtext);
    }
}