#include <stdio.h>
#include <sys/time.h>

int main(){

    alarm(1);
    int i = 0;
    while(1){
        printf("i = %d\n", i++);
    }
    return 0;
}