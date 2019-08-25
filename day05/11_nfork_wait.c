#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    int n = 5;
    int i = 0;
    for (i = 0; i < 5; ++i){
        int pid = fork();
        if(pid == 0){
            printf("i am child, pid = %d\n", getpid());
            break;
        }
    }
    sleep(i);
    //父进程逻辑
    if(i == 5){
        for (i = 0; i < 5; ++i){
            pid_t wpid = wait(NULL);
            printf("wpid = %d\n", wpid);
        }
        while(1){
            sleep(1);
        }
    }
    return 0;
}