/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 13:36:27
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        perror("./a.out filename");
        return -1;
    }
    truncate(argv[1], 4);
    

    return 0;
}