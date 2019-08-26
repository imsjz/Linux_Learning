/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-25 13:10:03
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int beginNum = 1000;

void *thr_write(void *arg){
    while(1){
        pthread_rwlock_wrlock(&rwlock);
        printf("---%s---self---%lu---beginnum---%d\n", __FUNCTION__, pthread_self(), ++beginNum);
        usleep(2000); //模拟占用时间， 2毫秒
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return  NULL;
}

void *thr_read(void *arg){
    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("---%s---self---%lu---beginnum---%d\n", __FUNCTION__, pthread_self(), beginNum);
        usleep(2000); //模拟占用时间， 2毫秒
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return NULL;
}

int main(){
    int n = 8, i = 0;
    pthread_t tid[n]; // 5-read, 3-write
    for(; i < 5; ++i){
        pthread_create(&tid[i], NULL, thr_read, NULL);
    }
    for(; i < n; ++i){
        pthread_create(&tid[i], NULL, thr_write, NULL);
    }

    //等待回收线程
    for(i = 0; i < n; ++i){
        pthread_join(tid[i], NULL);
    }

    return 0;
}