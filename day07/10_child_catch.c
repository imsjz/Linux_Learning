#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void catch_sig(int num){
    //这种一次只能完成一次的回收
    //pid_t wpid = waitpid(-1, NULL, WNOHANG);
    pid_t wpid;
    while((wpid = waitpid(-1, NULL, WNOHANG)) > 0){
    printf("wait child %d ok \n", wpid);
    }
}

int main(){

    int i = 0;
    pid_t pid;
    //在创建子进程之前屏蔽SIGCHLD信号
    sigset_t myset, oldset;
    sigemptyset(&myset);
    sigaddset(&myset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &myset, &oldset);
    for (; i < 10; ++i){
        pid = fork();
        if(pid == 0)
            break;
    }
    if(i == 10){
        //parent

        //模拟进程注册晚于子进程死亡时间
        sleep(2);
        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = catch_sig;

        sigaction(SIGCHLD, &act, NULL);

        //待父进程绑定之后解除屏蔽现场
        sigprocmask(SIG_SETMASK, &oldset, NULL);
        while(1){
            sleep(1);
        }
    }
    else if(i < 10){
        //son
        printf("I am %d child, pid = %d\n", i, getpid());
        //sleep(i);

    }
        return 0;
}