#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void catch_sig(int num){
    printf("cat %d sig\n", num);
}
int main(){
    signal(SIGALRM, catch_sig);
    struct itimerval myit = {{3, 0}, {5, 0}}; //第一次等待5秒，之后每隔3秒
    setitimer(ITIMER_REAL, &myit, NULL);

    while(1){
        printf("and who?\n");
        sleep(1);
    }
    return 0;
}