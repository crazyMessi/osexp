#include "my_ipc.h"

void main()
{
    int count = 0;
    int flag = 0;
    int first = SOFASIZE - 1;
    int end = first;
    int space[SOFASIZE];
    Msg_buf msg;
    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);

    while (1)
    {
        if (count == SOFASIZE)
        {
            printf("full,waiting for next section get ready");
            //full,waiting for a permission from next section
            if (msgrcv(rcv_msq, &msg, MSG_SIZE, ROOM_2_SOFA, WAIT) > 0)
            {
                printf("custom %d leave sofa to chair\n", space[first]);
                msg.mtype = SOFA_2_CHAIR;
                msg.mtext = space[first];
                if (msgsnd(snd_msq, &msg, MSG_SIZE, WAIT) == 0)
                {
                    first = (first + SOFASIZE - 1) % SOFASIZE;
                    count--;
                }
            }
        }

        if (0 < count&&count< SOFASIZE)
        {
            if (msgrcv(rcv_msq, &msg, MSG_SIZE, CHAIR_2_SOFA, NO_WAIT) > 0)
            {
                printf("custom %d leave sofa to chair\n", space[first]);
                msg.mtype = SOFA_2_CHAIR;
                msg.mtext = space[first];
                if (msgsnd(snd_msq, &msg, MSG_SIZE, NO_WAIT) == 0)
                {
                    first = (first + SOFASIZE - 1) % SOFASIZE;
                    count--;
                }
            }

            if (flag)
            {
                if (msgrcv(snd_msq, &msg, MSG_SIZE, ROOM_2_SOFA, NO_WAIT) > 0)
                {
                    printf("rcv custom %d from room\n", msg.mtext);
                    space[end] = msg.mtext;
                    end = (end - 1 + SOFASIZE) % SOFASIZE;
                    count++;
                    flag--;
                }
            }
            else
            {
                msg.mtype = SOFA_2_ROOM;
                if (msgsnd(rcv_msq, &msg, MSG_SIZE, NO_WAIT) == 0)
                {
                    printf("admit a custom from room...\n");
                    flag++;
                }
            }
        }

        if (count == 0)
        {
            //empty,waiting for a custom
            msg.mtype = SOFA_2_ROOM;
            //send a msg that custom is allowed
            if (msgsnd(rcv_msq, &msg, MSG_SIZE, WAIT) == 0)
            {
                if (msgrcv(snd_msq, &msg, MSG_SIZE, ROOM_2_SOFA, WAIT) > 0)
                {
                    space[end] = msg.mtext;
                    end = (end - 1 + SOFASIZE) % SOFASIZE;
                    count++;
                }
            }
        }
    }
}
