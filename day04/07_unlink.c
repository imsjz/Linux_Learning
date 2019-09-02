/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 19:52:22
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    int fd = open("world", O_WRONLY | O_CREAT, 0664);

    unlink("world");
    int ret = write(fd, "hello",5);
    if(ret > 0){
        printf("write ok!%d\n", ret);
    }
    else if(ret < 0){
        perror("write err");
    }
    close(fd);

    return 0;
}