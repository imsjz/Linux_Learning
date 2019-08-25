#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

int main(){
    printf("I will die!\n");
    //raise(SIGKILL);
    abort();
    return 0;
}