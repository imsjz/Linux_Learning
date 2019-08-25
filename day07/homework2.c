#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
pid_t pid;
int flag = 0;
int count = 0;

void cat_sig_child(int num){
    sleep(1);
    printf("child count = %d\n", count);
    count += 2;
    //flag = 1;
    kill(getppid(), SIGUSR1);
}

void cat_sig_parent(int num){
    sleep(1);
    printf("parent count = %d\n", count);
    count += 2;
    //flag = 1;
    kill(pid, SIGUSR2);
}

int main(){
    pid = fork();
    if(pid == 0){
        //子进程
        count = 1;
        signal(SIGUSR2, cat_sig_child);
        //pid_t ppid = getppid();
        while(1){
            // if(flag == 1){
            //     kill(ppid, SIGUSR1);
            //     flag = 0;
            // }
        }
    }
    else if(pid > 0){
        usleep(10);
        count = 2;
        signal(SIGUSR1, cat_sig_parent);
        kill(pid, SIGUSR2); //首先父进程发送SIGUSR2给子进程
        while(1){
            // if(flag == 1){
            //     kill(pid, SIGUSR2);
            //     flag = 0;
            // }
        }
    }
    return 0;
}