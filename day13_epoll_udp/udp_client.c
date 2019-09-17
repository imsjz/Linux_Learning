/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-17 16:36:24
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 9876

int main(int argc, char *argv[]){

    //创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket error");
        exit(1);
    }

    //初始化服务器的ip和端口
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr.s_addr);


    //通信
    while(1){
        char buf[1024] = {0};
        fgets(buf, sizeof(buf), stdin);
        sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr *)&serv, sizeof(serv));

        //等待服务器发送数据过来
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("recv buf: %s\n", buf);
    }
    close(fd);

    return 0;
}