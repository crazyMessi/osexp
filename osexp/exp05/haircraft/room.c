#include "my_ipc.h"

void main()
{
    int count = 0;
    int flag = 0;
    int first = ROOMSIZE - 1;
    int end = first;
    int space[ROOMSIZE];
    Msg_buf msg;
    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);

    while (1)
    {
        // printf("\ncount = %d\n",count);
        if (count == ROOMSIZE)
        {
            printf("full,waiting for next section get ready");
            //full,waiting for a permission from next section
            if (msgrcv(rcv_msq, &msg, MSG_SIZE, SOFA_2_ROOM, WAIT) > 0)
            {
                printf("custom %d leave rest room to sofa\n", space[first]);
                msg.mtype = ROOM_2_SOFA;
                msg.mtext = space[first];
                if (msgsnd(snd_msq, &msg, MSG_SIZE, WAIT) == 0)
                {
                    first = (first + ROOMSIZE - 1) % ROOMSIZE;
                    count--;
                }
            }
        }
        if (0<count&&count<ROOMSIZE)
        {
            if (msgrcv(rcv_msq, &msg, MSG_SIZE, SOFA_2_ROOM, NO_WAIT) > 0)
            {
                printf("custom %d leave rest room to sofa\n", space[first]);
                msg.mtype = ROOM_2_SOFA;
                msg.mtext = space[first];
                if (msgsnd(snd_msq, &msg, MSG_SIZE, NO_WAIT) == 0)
                {
                    first = (first + ROOMSIZE - 1) % ROOMSIZE;
                    count--;
                }
            }

            if (flag)
            {
                if (msgrcv(snd_msq, &msg, MSG_SIZE, CUS_2_ROOM, NO_WAIT) > 0)
                {
                    printf("rcv custom %d from outside\n", msg.mtext);
                    space[end] = msg.mtext;
                    end = (end - 1 + ROOMSIZE) % ROOMSIZE;
                    count++;
                    flag--;
                }
            }
            else
            {
                msg.mtype = ROOM_2_CUS;
                if (msgsnd(rcv_msq, &msg, MSG_SIZE, NO_WAIT) == 0)
                {
                    flag++;
                    printf("admit a custom from outside...\n");
                }
            }
        }
        if (count == 0)
        {
            //empty,waiting for a cunstom
            msg.mtype = ROOM_2_CUS;
            if (msgsnd(rcv_msq, &msg, MSG_SIZE, WAIT) == 0)
            {
                printf("empty!waiting for a custom from outside...\n");
                if (msgrcv(snd_msq, &msg, MSG_SIZE, CUS_2_ROOM, WAIT) > 0)
                {
                    printf("rcv custom %d from outside\n", msg.mtext);
                    space[end] = msg.mtext;
                    end = (end - 1 + ROOMSIZE) % ROOMSIZE;
                    count++;
                }
            }
        }
    }
}