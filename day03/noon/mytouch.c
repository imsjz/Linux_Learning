/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-29 10:49:02
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("./a.out filename\n");
        return -1;
    }
    int fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    close(fd);
    return 0;
}