/*
* Filename : ppipe.c
* copyright : (C) 2006 by zhanghonglie
* Function : 利用管道实现在父子进程间传递整数
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int funy(int y);
int funx(int x);

int main(int argc, char *argv[])
{
    int pid;      //进程号
    int x_fx[2];
    int fx_x[2]; 
    int y_fy[2];
    int fy_y[2]; 
    int x,y,fx,fy;
    int pid_fx,pid_fy;
    const char* inx = "input x:";
    const char* iny = "input y:";

    write(STDOUT_FILENO,inx,sizeof(inx));
    scanf("%d",&x);
    pipe(x_fx);
    pipe(fx_x);
    write(STDOUT_FILENO,iny,sizeof(iny));
    scanf("%d",&y);
    pipe(y_fy);
    pipe(fy_y);

    pid_fx = fork();
    pid_fy = fork();
    if(pid_fx==0){
        close(x_fx[1]);
        close(fx_x[0]);
        read(x_fx[0],&x,sizeof(x));
        fx = funx(x);
        write(fx_x[1],&fx,sizeof(fx));
        close(x_fx[0]);
        close(fx_x[1]);
        exit(EXIT_SUCCESS);
    }
    if(pid_fy==0){
        close(y_fy[1]);
        close(fy_y[0]);
        read(y_fy[0],&y,sizeof(y));
        fy = funy(y);
        write(fy_y[1],&fy,sizeof(fy));
        close(y_fy[0]);
        close(fy_y[1]);
        exit(EXIT_SUCCESS);
    }else{
        close(y_fy[0]);
        close(fy_y[1]);
        write(y_fy[1],&y,sizeof(y));
        read(fy_y[0],&fy,sizeof(fy));
        printf("fy:%d\n",fy);
        close(y_fy[1]);
        close(fy_y[0]);


        close(x_fx[0]);
        close(fx_x[1]);
        write(x_fx[1],&x,sizeof(x));
        read(fx_x[0],&fx,sizeof(fx));
        printf("fx:%d\n",fx);
    
        close(x_fx[1]);
        close(fx_x[0]);

        printf("f(x,y):%d\n",fx+fy);
    }



    return EXIT_SUCCESS;
}

int funx(int x){
    if(x>1){
        return x*funx(x-1);
    }else{
        return 1; 
    }
}

int funy(int y){
    if(y>2){
        return funy(y-1)+funy(y-2);
    }else{
        return 1;
    }
} 