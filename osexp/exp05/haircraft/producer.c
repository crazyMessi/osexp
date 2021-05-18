#include "my_ipc.h"

void main()
{
    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);
    int i = 1;
    Msg_buf msg;
    while (i++)
    {

        if (msgrcv(rcv_msq, &msg, sizeof(int), ROOM_2_CUS, NO_WAIT)>0)
        {
            msg.mtext = i;
            msg.mtype = CUS_2_ROOM;
            if (msgsnd(snd_msq, &msg, sizeof(int), NO_WAIT)==0)
            {
                printf("custom %d enter\n", i);
                sleep(1);
            }
            continue;
        }
        sleep(1);
    }
}