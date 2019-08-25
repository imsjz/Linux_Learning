#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg){

    int num = (int)arg;
    printf("I am %d thread, self = %lu\n", num, pthread_self());
    return (void *)(100 + num);
}

int main(){

    pthread_t tid[5];
    int i;
    for (i = 0; i < 5; i++){
        pthread_create(&tid[i], NULL, thr, (void *)i); //这里不一定有序
    }
    for (i = 0; i < 5; i++){
        void *ret;
        pthread_join(tid[i], &ret); //阻塞，这里有序
        printf("i = %d, ret = %d\n", i, (int)ret);
    }
    return 0;
}