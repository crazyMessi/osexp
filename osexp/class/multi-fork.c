// How many processes are created?

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("%d*\n", getpid());
    fork();

    printf("%d**\n", getpid());
    fork();

    printf("%d***\n", getpid());
    fork();
	
    printf("%d****\n", getpid());

    sleep(15);
    return 0;
}
