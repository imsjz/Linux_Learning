#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

int main(){

    sigset_t pend, sigproc;
    //设置阻塞信号，等待按键产生信号
    sigemptyset(&sigproc);//先清空
    sigaddset(&sigproc, SIGINT);
    sigaddset(&sigproc, SIGQUIT);
    //设置阻塞信号集
    sigprocmask(SIG_BLOCK, &sigproc, NULL); //设置了阻塞信号集，发送那个信号就没有用了，因为被阻塞了
    //循环去未决信号集，打印
    while(1){
        sigpending(&pend);
        int i = 1;
        for (; i < 32; ++i){
            if((sigismember(&pend, i) == 1)){
                    printf("1");
            }
            else{
                printf("0");
            }
        }
        printf("\n");
        sleep(1);
    }

    return 0;
}