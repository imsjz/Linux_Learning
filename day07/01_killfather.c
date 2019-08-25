#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main(){

    int i;
    for (i = 0; i < 5; ++i){
        pid_t pid = fork();
        if(pid == 0){
            break;
        }
    }
    if(i == 2){
        printf("I will kill father in 5s\n");
        sleep(5);
        kill(getppid(), SIGKILL);
        while(1){
            sleep(1);
        }
    }
    else if(i == 5){
        //父进程
        while(1){
            printf("I am parent\n");
            sleep(1);
        }
    }
        return 0;
}