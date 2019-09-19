/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-19 12:57:16
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(){

    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd == -1){
        perror("socket err");
        exit(1);
    }
    //如果套接字文件存在,删除
    unlink("client.socket");

    //绑定
    struct sockaddr_un client;
    client.sun_family = AF_LOCAL;
    strncpy(client.sun_path, "client.socket", sizeof("client.socket"));
    int ret = bind(fd, (struct sockaddr*)&client, sizeof(client));
    if(ret == -1){
        perror("bind err");
        exit(1);
    }

    //客户端发起连接
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, "server.socket", sizeof("server.socket"));
    ret = connect(fd, (struct sockaddr*)&server, sizeof(server));
    if(ret == -1){
        perror("connect err");
        exit(1);
    }

    //通信
    while(1){
        char buf[1024] = {0};
        fgets(buf, sizeof(buf), stdin);
        int sendlen = send(fd, buf, strlen(buf)+1, 0);


        //接收数据
        recv(fd, buf, sizeof(buf), 0);
        printf("recv buf: %s\n", buf);
    }
    close(fd);

    return 0;
}
