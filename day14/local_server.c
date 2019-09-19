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

    int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket err");
        exit(1);
    }
    //如果套接字文件存在,则删除套接字文件
    unlink("server.socket");

    //绑定
    struct sockaddr_un serv;
    serv.sun_family = AF_LOCAL;
    strncpy(serv.sun_path, "server.socket", sizeof("server.socket"));
    int ret = bind(lfd, (struct sockaddr*)&serv, sizeof(serv));
    if(ret == -1){
        perror("bind err");
        exit(1);
    }

    //设置监听数目
    ret = listen(lfd, 36);
    if(ret == -1){
        perror("listen err");
        exit(1);
    }

    //接受连接
    struct sockaddr_un client;
    socklen_t len = sizeof(client);
    int cfd = accept(lfd, (struct sockaddr*)&client, &len);
    if(cfd == -1){
        perror("accept err");
        exit(1);
    }
    printf("client bind file: %s\n", client.sun_path);

    //通信
    while(1){
        char buf[1024] = {0};
        int recvlen = recv(cfd, buf, sizeof(buf), 0);
        if(recvlen == -1){
            perror("recv error");
            exit(1);
        }
        else if(recvlen == 0){
            printf("Client disconnect ...\n");
            exit(1);
        }
        else{
            printf("recv buf: %s\n", buf);
            send(cfd, buf, recvlen, 0);
        }
    }
    close(cfd);
    close(lfd);

    return 0;
}
