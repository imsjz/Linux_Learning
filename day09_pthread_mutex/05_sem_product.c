/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-25 21:47:28
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t blank, xfull;
#define _SEM_CNT_ 5

int queue[_SEM_CNT_]; //模拟饼筐
int beginnum = 100;

void *thr_producer(void *arg){

    int i = 0;
    while(1){
        sem_wait(&blank); //申请资源 blank--
        printf("---%s---self---%lu---num---%d\n", __FUNCTION__, pthread_self(), beginnum);
        queue[(i++)%_SEM_CNT_] = beginnum++;
        sem_post(&xfull);//xfull++
        sleep(rand() % 3);
    }

    return NULL;
}

void *thr_customer(void *arg){
    int i = 0;
    int num;
    while(1){
        sem_wait(&xfull);
        num = queue[(i++) % _SEM_CNT_];
        printf("---%s---self---%lu---num---%d\n", __FUNCTION__, pthread_self(), num);
        sem_post(&blank);
        sleep(rand() % 3);
    }

    return NULL;
}


int main(){

    //初始化信号量
    sem_init(&blank, 0, _SEM_CNT_);
    sem_init(&xfull, 0, 0); //消费者一开始的初始化默认没有产品

    pthread_t tid[2];
    pthread_create(&tid[0], NULL, thr_producer, NULL);
    pthread_create(&tid[1], NULL, thr_customer, NULL);


    sem_destroy(&blank);
    sem_destroy(&xfull);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}