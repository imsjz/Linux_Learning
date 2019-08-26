/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-25 14:40:54
 */
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int beginnum = 1000;

typedef struct _ProdInfo{
    int num;
    struct _ProdInfo *next;
}ProdInfo;

ProdInfo *Head = NULL;

void *thr_producer(void *arg){

    //负责在链表中添加数据
    while(1){
        ProdInfo *prod = malloc(sizeof(ProdInfo));
        prod->num = beginnum++;
        printf("---%s---self=%lu---%d\n", __FUNCTION__, pthread_self(), prod->num);
        pthread_mutex_lock(&mutex);
        //add to list
        //直接往头上插
        prod->next = Head;
        Head = prod;
        pthread_mutex_unlock(&mutex);
        //发起通知
        pthread_cond_signal(&cond);
        sleep(rand() % 2);

    }
    return NULL;
}

void *thr_costomer(void *arg){
    ProdInfo *prod = NULL;
    while(1){
        //取链表的数据
        pthread_mutex_lock(&mutex);
        // if(Head == NULL){ //用if来判断的话，多线程会出错：假设生产者生产了一个东西，然后发信号，两个线程都接收到了信号，其中一个更快获取到，另一个也会去获取，然而里面没东西了，因此会出错
        //     pthread_cond_wait(&cond, &mutex); //在此之前必须先加锁
        // }
        //用while进行判断更好
        while(Head == NULL){
            pthread_cond_wait(&cond, &mutex);
        }
        prod = Head;
        Head = Head->next;
        printf("---%s---self=%lu---%d\n", __FUNCTION__, pthread_self(), prod->num);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 4);
        free(prod);
    }
    return NULL;
}

int main(){
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, thr_producer, NULL);
    pthread_create(&tid[1], NULL, thr_costomer, NULL);
    pthread_create(&tid[2], NULL, thr_costomer, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}