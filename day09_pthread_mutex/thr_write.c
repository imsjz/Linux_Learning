/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-25 14:15:02
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t mutex;

char buf[20];


void *thr1(void *arg){

    int i = 0;
    pthread_mutex_lock(&mutex);
    for(; i < 20; ++i){
        usleep(rand()%3);
        buf[i] = '0';
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}


void *thr2(void *arg){

    int i = 0;
    sleep(3);
    pthread_mutex_lock(&mutex);
    for(; i < 20; ++i){
        usleep(rand()%3);
        buf[i] = '1';
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}


int main(){

    memset(buf, 0x00, sizeof(buf));

    pthread_mutex_init(&mutex, NULL); //初始化mutex锁
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, thr1, NULL);
    pthread_create(&tid[1], NULL, thr2, NULL);

    // pthread_join(tid[0], NULL);
    // pthread_join(tid[1], NULL);
    pthread_detach(tid[0]);
    pthread_detach(tid[1]);
    sleep(3);
    printf("buf is %s\n", buf);

    pthread_mutex_destroy(&mutex);
    return 0;
}