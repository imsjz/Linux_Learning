/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-29 13:02:20
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

    write(fd, "helloworld", 11);

    char buf[256] = {0};
    lseek(fd, 0, SEEK_SET);
    int ret = read(fd, buf, sizeof(buf));

    if(ret){
        write(STDOUT_FILENO, buf, ret);
    }

    close(fd);
    return 0;
}