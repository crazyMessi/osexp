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
        execlp("ls", "ls", (char *)NULL);
        printf("Unreachable!\n");
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        printf("I am the parent. My PID is %d, my child's PID is %d\n", getpid(), pid);
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;
}

