#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
void pro_add();
void pro_substract();

int main(int argc, char *argv[])
{
    signal(SIGINT, (sighandler_t)pro_add);
    signal(SIGTSTP, (sighandler_t)pro_substract);
    int pid;
    pid = fork();
    while (1)
    {
        if (pid == 0)
        {
            int policy = 0;
            int cpid = getpid();
            int priority = getpriority(PRIO_PROCESS, cpid);
            printf("I'm process %d,my policy = %d,my priority = %d\n", cpid, policy, priority);
            sleep(1);
        }
        else
        {
            int policy = 0;
            int cpid = getpid();
            int priority = getpriority(PRIO_PROCESS, cpid);
            printf("I'm process %d,my policy = %d,my priority = %d\n", cpid, policy, priority);
            sleep(1);
        }
    }
}

void pro_add()
{
    int pid = getpid();
    int pri = getpriority(PRIO_PROCESS, pid);
    setpriority(PRIO_PROCESS, getpid(), pri + 1);
    return;
}
void pro_substract()
{
    int pid = getpid();
    int pri = getpriority(PRIO_PROCESS, pid);
    setpriority(PRIO_PROCESS, getpid(), pri - 1);
    return;
}
