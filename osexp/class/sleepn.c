#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int n;

    if(argc <= 1) {
        n = 1;
        printf("Sleep 1s\n");
    }
    else {
        n = atoi(argv[1]);
        printf("Sleep %s(%d)s\n", argv[1], n);
    }

    sleep(n);
    printf("Wake(%ds)\n", n);
    return 0;
}
