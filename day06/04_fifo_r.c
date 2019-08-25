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
    printf("begin open read...\n");
    int fd = open(argv[1], O_RDONLY);
    printf("end open read...\n");
    char buf[256];
    int ret;
    while(1){
        ret = read(fd, buf, sizeof(buf));
        if(ret > 0){
            printf("read: %s\n", buf);
        }
    }
    close(fd);
    return 0;
}