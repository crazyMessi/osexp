#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) { /* child process */
        printf("I am the child. My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        sleep(3);   /* Wait parent run. Not reliable, for demo only! */
        printf("Wake up. My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        execlp("ls", "ls", (char *)NULL);
        printf("Unreachable 1!\n");
    }
    else { /* parent process */
        printf("I am the parent. My PID is %d, my child's PID is %d\n", getpid(), pid);
        sleep(1);   /* Wait child run. Not reliable, for demo only! */
        exit(0);
        printf("Unreachable 2!\n");
    }

    printf("Unreachable 3!\n");
    return 0;
}
