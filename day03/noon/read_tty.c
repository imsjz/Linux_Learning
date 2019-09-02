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

    int fd = open("/dev/tty", O_RDWR);

    int flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

    char buf[256];
    int ret = 0;
    while(1){
        ret = read(fd, buf, sizeof(buf));
        if(ret < 0){
            perror("read err");
            printf("ret is %d\n", ret);
        }
        if(ret){
            printf("buf is %s\n", buf);
        }
        printf("haha\n");
        sleep(1);
    }
    return 0;
}