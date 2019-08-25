#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

int main(){
    int ret = 0;
    ret = alarm(6);
    printf("ret = %d\n", ret);
    sleep(2);
    ret = alarm(5);
    printf("ret = %d\n", ret);
    while(1){
        printf("you \n");
        sleep(1);
    }
    return 0;
}