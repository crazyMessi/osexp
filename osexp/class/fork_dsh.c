#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int d_var = 1;

int main(void)  /* fork_dsh.c */
{
    pid_t pid;
    int s_var = 2;
    int* h = (int *)malloc(sizeof(int));
    *h = 3;

    pid = fork();
    if (pid == 0) { /* Child process */
        sleep(3);   /* Wait parent run. Not reliable, for demo only! */
        d_var += 100;
        s_var += 100;
        *h += 100;
        printf ("Child: d_var=%d, s_var=%d, *h=%d\n", d_var, s_var, *h);
    }
    else if (pid > 0) { /* Parent process */
        d_var += 10;
        s_var += 10;
        *h += 10;
        wait(NULL);  /* Wait child exit */
        printf ("Parent: d_var=%d, s_var=%d, *h=%d\n", d_var, s_var, *h);
    }
    free(h);
    return 0;
}
