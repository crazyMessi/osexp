#include "my_ipc.h"




int main(int argc,char*argv[]){
    int rate;
    if(argv[0] != NULL) rate = atoi(argv[0]);
    else rate = 3; //不指定为3秒

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
    for(int i = 0;i<3;i++){
        cmtx_sem[i] = set_sem(cmtx_key[i],0,sem_flg);
        library_ptr[i] = 0;
    }
    
    int msq_id = set_msq(msq,msq_flag);
    request->mtype = 1;
    int i = 0;
    while(1){
        int code =msgrcv(msq_id,request,sizeof(char),MSGTYPE,MSG_FLG);
        char kind = request->mtext[0];       
        down(pmtx_sem);

        library_ptr[(kind+1)%3]++;
        library_ptr[(kind+2)%3]++;

        sleep(rate);
        printf("producer finish ask from %d in roop %d\n",kind,i);
        up(pmtx_sem);
        up(cmtx_sem[kind]);
        i++;
    }

}
