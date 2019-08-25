#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(2);
        printf("I am child, i will die!\n");
    }
    else if(pid > 0){
        while(1){
            printf("I am father, pid = %d\n", getpid());
            sleep(1);
        }
    }
    return 0;
}