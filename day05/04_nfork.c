#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//13_循环创建n个子进程控制顺序
int main(){
    int n = 5;
    int i = 0;
    pid_t pid = 0;
    for (i = 0; i < n; ++i){
        pid = fork();
        if(pid == 0){
            //son
            printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
            break; //子进程退出循环
        }
        else if(pid > 0){
            //printf("I am father, pid = %d, ppid = %d\n", getpid(), getppid());
        }
    }
    sleep(i);
    if(i < 5) //子进程
        printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
    else{ // father
        printf("I am father, pid = %d, ppid = %d\n", getpid(), getppid());
    }
    return 0;
}