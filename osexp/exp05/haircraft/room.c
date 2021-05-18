#include "my_ipc.h"

void main()
{
    int count = 0;
    int flag = 0;
    int first = count;
    int end = first;
    int space[ROOMSIZE+1];
    Msg_buf msg;
    int snd_msq = set_msq(SND_MSQ, OPEN_ALL);
    int rcv_msq = set_msq(RCV_MSQ, OPEN_ALL);

    while (1)
    {
        if (count == ROOMSIZE)
        {
            //full,waiting for a permission from next section
            if (msgrcv(snd_msq, &msg, MSG_SIZE, CUS_2_ROOM, WAIT) > 0)
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
        }

        if (0 < count < ROOMSIZE)
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
                    end = (end - 1 + ROOMSIZE) % ROOMSIZE;
                    space[end] = msg.mtext;
                    count++;
                    flag--;
                }
            }
            else
            {
                msg.mtype = ROOM_2_CUS;
                msgsnd(rcv_msq, &msg, MSG_SIZE, NO_WAIT);
                flag++;
            }
        }

        if (count == 0)
        {
            //empty,waiting for a cunstom
            msg.mtype = ROOM_2_CUS;
            if (msgsnd(rcv_msq, &msg, MSG_SIZE, WAIT) == 0)
            {
                if (msgrcv(snd_msq, &msg, MSG_SIZE, CUS_2_ROOM, WAIT) > 0)
                {

                    end = (end - 1 + ROOMSIZE) % ROOMSIZE;
                    space[end] = msg.mtext;
                    count++;
                }
            }
        }
    }
}