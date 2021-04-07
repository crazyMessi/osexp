#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid, pid2;

    pid = fork();  /* fork a child process */

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) /* child process */
        printf("I am the child. My PID is %d, my parent's PID is %d\n", getpid(), getppid());
    else { /* parent process */
        printf("I am the parent. My PID is %d, my child's PID is %d\n", getpid(), pid);
        sleep(3);   /* Wait child terminate. Not reliable, for demo only! */
        /* No wait() here, to make child 1 zombie */
        pid2 = fork();  /* fork 2nd child process */
        if(pid2 == 0) /* 2nd child process */
            execlp("ps", "ps", "-Al", (char *)NULL);
        else /* parent process, or fork failed */
            sleep(3);   /* Wait ps done. Not reliable, for demo only! */
    }

    return 0;
}
