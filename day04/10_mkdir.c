/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 21:15:22
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("./a.out dirname\n");
        return -1;
    }
    mkdir(argv[1], 0777);

    return 0;
}