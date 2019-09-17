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
    //fd绑定本地的ip和端口
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    int ret = bind(fd, (struct sockaddr*)&serv, sizeof(serv));
    if(ret == -1){
        perror("bind error");
        exit(1);
    }

    struct sockaddr_in client;
    socklen_t cli_len = sizeof(client);
    //通信
    char buf[1024] = {0};
    while(1){

        int recvlen = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&client, &cli_len);
        printf("recv buf: %s\n", buf);
        char ip[64] = {0};
        printf("New client ip: %s, port: %d\n",
                inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof(ip)),
                ntohs(client.sin_port));

        //给客户发送数据
        sendto(fd, buf, recvlen, 0, (struct sockaddr*)&client, sizeof(client));
    }
    close(fd);

    return 0;
}