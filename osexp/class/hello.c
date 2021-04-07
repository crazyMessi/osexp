#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("Hello World\n");
    printf("My PID is %d\n", getpid());
    printf("My parent's PID is %d\n", getppid());
    printf("Press the Enter key to exit\n");
    getchar();
    return 0;
}
