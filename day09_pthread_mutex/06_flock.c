/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-26 10:56:42
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define _FILE_NAME_ "/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day09_pthread_mutex/temp.lock"

int main(){

    int fd = open(_FILE_NAME_, O_RDWR | O_CREAT, 0664); //user group other
    if(fd < 0){
        perror("open error");
        return -1;
    }

    struct flock lk;
    lk.l_type = F_WRLCK;
    lk.l_whence = SEEK_SET;
    lk.l_start = 0;
    lk.l_len = 0;

    if(fcntl(fd, F_SETLK, &lk) < 0){
        perror("get lock failed");
        exit(1);
    }
    //核心逻辑
    while(1){
        printf("I am alive!\n");
        sleep(1);
    }
    return 0;
}