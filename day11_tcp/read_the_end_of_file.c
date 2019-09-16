/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-15 14:28:51
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]){

    char buf[BUFSIZE] = {0};

    int r_fd = open(argv[1], O_RDONLY);

    int len = read(r_fd, buf, BUFSIZE);

    printf("Read buf: %s", buf);
    printf("The length of buf read: %d\n", len);
    printf("The strlen of buf: %ld\n", strlen(buf));

    return 0;
}