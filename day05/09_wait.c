#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("I am child, i will die!\n");
        sleep(2);
        while(1){
            printf("I am child\n");
            sleep(1);
        }
        exit(101);
    }
    else if(pid > 0){
            printf("I am father, wait for child die!\n");
            int status;

            pid_t wpid = wait(&status); //进程阻塞
            printf("wait ok, wpid = %d, pid = %d\n", wpid, pid);
            if(WIFEXITED(status)){
                printf("child exit with %d\n", WEXITSTATUS(status));
            }
            if(WIFSIGNALED(status)){
                printf("child kill with %d\n", WTERMSIG(status));
            }

            while(1){
                sleep(1);
            }
    }
    return 0;
}