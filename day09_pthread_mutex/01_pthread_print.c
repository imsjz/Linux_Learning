#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;

void *thr1(void *arg){

    while(1){
        //先上锁
        pthread_mutex_lock(&mutex); //加锁，当有其他线程占用锁的时候会阻塞
        //##############临界区
        printf("hello");
        sleep(rand() % 3);
        printf("world\n");

        //释放锁
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);

    }
}

void *thr2(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        printf("HELLO");
        sleep(rand() % 3);
        printf("WORLD\n");

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
}

int main(){

    pthread_t tid[2];
    pthread_create(&tid[0], NULL, thr1, NULL);
    pthread_create(&tid[1], NULL, thr2, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}