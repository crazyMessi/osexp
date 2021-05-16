#include "my_ipc.h"

int main(int argc,char*argv[]){
    int rate,kind;
    if(argv[0] != NULL) kind = atoi(argv[0]);
    else kind = 1; 
    if(argv[1] != NULL) rate = atoi(argv[0]);
    else rate = 1; //不指定为1秒

    Msg_buf a;
    Msg_buf* request = &a;    
    sem_flg=IPC_CREAT|0644;
    shm_flg=IPC_CREAT|0644;
    msq_flag=IPC_CREAT|0644;
    library_id = 100;
    library_size = 3;
    pmtx_key = 3100;
    msq =5000;
    
    
    
    for(int i=0;i<3;i++){
        cmtx_key[i] = 4200+i;
    }
    
    library_ptr = (char*)set_shm(library_id,library_size,shm_flg);
    pmtx_sem = set_sem(pmtx_key,1,sem_flg);
    cmtx_sem[kind] = set_sem(cmtx_key[kind],0,sem_flg);
    
    int msq_id = set_msq(msq,msq_flag);
    request->mtype = 1;
    request->mtext[0]=(char)kind;
    int i = 0;
    while(1){
        int code =  msgsnd(msq_id,request,sizeof(char),MSG_FLG);
        down(cmtx_sem[kind]);
        down(pmtx_sem); 

        library_ptr[(kind+1)%3]--;
        library_ptr[(kind+2)%3]--;
        
        sleep(rate);
        up(pmtx_sem);
        printf("smoker_%d smoke %d times\n",kind,i);
        i++;
    }
    

}
