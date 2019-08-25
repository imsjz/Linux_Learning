#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg){

    printf("I am a thread, very happy! tid = %lu\n", pthread_self());
    return NULL;
}

int main(){

    pthread_attr_t attr;
    pthread_attr_init(&attr); //初始化属性

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t tid;
    pthread_create(&tid, &attr, thr, NULL);

    int ret = 0;
    if((ret = pthread_join(tid, NULL)) > 0){
        printf("join err: %d, %s\n", ret, strerror(ret));
    }
    pthread_attr_destroy(&attr);//摧毁属性
    return 0;
}