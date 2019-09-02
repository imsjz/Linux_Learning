/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-29 16:06:40
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    int num = 3;
    char filename[128] = {0};
    while(1){
        sprintf(filename, "tmp_%04d", num++); //sprintf和strcpy的区别就是前者可以设置格式
        if((open(filename, O_RDONLY | O_CREAT, 0664)) < 0){
            perror("open err");
            break;
        }
    }
    printf("num = %d\n", num-2);
    return 0;
}