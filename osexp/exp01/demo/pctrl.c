#include "pctl.h"
int main(int argc, char *argv[])
{
char *args[] = {"/bin/ls","-a",NULL}; //子进程要缺省执行的命令
int pid_1,pid_2; //存放子进程号
int status_1,status_2; //存放子进程返回状态
while(1){
pid_1=fork() ;
if(pid_1<0) // 建立子进程失败?
{
printf("Create Process fail!\n");
exit(EXIT_FAILURE);
}
if(pid_1 == 0) // 子进程执行代码段
{
//报告父子进程进程号
printf("I am Child-ls process %d\nMy father is %d\n",getpid(),getppid());/*getpid 返回当前进程
的进程号，getppid 返回当前进程父进程的进程号*/
pid_2=fork();
if(pid_2<0)// 建立子进程失败?
{
printf("Create Process fail!\n");
exit(EXIT_FAILURE) ;
}
if(pid_2==0) // 子进程执行代码段
{//报告父子进程进程号
printf("I am Child-ps process %d\nMy father is %d\n",getpid(),getppid());
printf("%d child will Running: \n",getpid()); /*子进程被键盘中断信号唤醒继续执行*/
status_2=execve("/bin/ps",NULL,NULL);//装入并执行新的程序
}else{
printf("wait for the ps-child end%d\n",pid_2);
waitpid(pid_2,&status_2,0);//等待子进程 2 结束
//status 用于保留子进程的退出状态
}
printf("%d child will Running: \n",getpid()); //装入并执行新的程序 char *argv[]={"0",NULL};
status_1 = execve("/bin/ls",argv,NULL);
}
else{
printf("I am Parent process %d\n",getpid());
printf("wait for the ls-child end %d\n",pid_1);
waitpid(pid_1,&status_1,0);
printf("child end,sleep...\n");
sleep(3);// sleep 函数会令调用进程的执行挂起睡眠 3 秒
}
}
return EXIT_SUCCESS;
}
————————————————
版权声明：本文为CSDN博主「Soul fragments」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_43943977/article/details/101833797