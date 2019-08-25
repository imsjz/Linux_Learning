#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("I am child, pid = %d\n", getpid());
        sleep(2);
    }
    else if(pid > 0){
            printf("I am father, pid = %d\n", getpid());
            int ret;
            while(( ret = waitpid(-1, NULL, WNOHANG)) == 0){
                sleep(1);
            }
            printf("ret = %d\n", ret);
            ret = waitpid(-1, NULL, WNOHANG);
            if(ret < 0){
                perror("wait error");
            }
            while(1){
                sleep(1);
            }
    }
    return 0;
}