#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int var = 100;

void *thr(void *arg){

    printf("I am a thread, very happy! tid = %lu, var = %d\n", pthread_self(), var);//2. var = 1003
    sleep(2);
    var = 1001;
    printf("I am a thread, very happy! tid = %lu, var = %d\n", pthread_self(), var); //3. var = 1001

    return NULL;
}

int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, thr, NULL);

    pthread_detach(tid); //线程分离
    printf("I am main thread, self = %lu, var = %d\n", pthread_self(), var); //1.先执行这里， var = 100
    var = 1003;
    sleep(5);
    printf("I am main thread, self = %lu, var = %d\n", pthread_self(), var); //4. var = 1001
    int ret = 0;
    if((ret = pthread_join(tid, NULL)) > 0){
        printf("join err: %d, %s\n", ret, strerror(ret));
    }
    return 0;
}