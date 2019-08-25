#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("./a.out fifoname");
        return -1;
    }
    printf("begin open write...\n");
    int fd = open(argv[1], O_WRONLY);
    printf("end open write...\n");
    char buf[256];
    int num = 1;
    while(1){
        memset(buf, 0x00, sizeof(buf));
        sprintf(buf, "xiaoming%04d", num++);
        write(fd, buf, sizeof(buf));
        //sleep(1);
    }
    close(fd);
    return 0;
}