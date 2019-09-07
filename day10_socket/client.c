/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-05 12:54:33
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("./a.out [IP] [PORT]\n");
        return -1;
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    //bind(fd, (struct sockaddr*)&client_addr, sizeof(client_addr)); //绑定fd

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    int addr;
    inet_pton(AF_INET, argv[1], &addr);
    server_addr.sin_addr.s_addr = addr;

    int ret;
    socklen_t server_addr_len = sizeof(server_addr);
    char buf[BUFSIZ];
    if((ret = connect(fd, (struct sockaddr*)&server_addr, server_addr_len)) == 0){
        char read_buf[1024];
        while(1){
            int ret = read(STDIN_FILENO, read_buf, sizeof(read_buf));
            int n = write(fd, read_buf, ret);
            int read_size = read(fd, buf, n);
            write(STDOUT_FILENO, buf, read_size);
        }
    }
    else
        printf("connection failed!\n");

    return 0;
}