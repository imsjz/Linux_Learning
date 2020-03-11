/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-09 16:05:22
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/select.h>



int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("eg: ./a.out port\n");
        exit(1);
    }
    struct sockaddr_in serv_addr;
    socklen_t serv_len = sizeof(serv_addr);
    int port = atoi(argv[1]);

    //创建套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    //初始化服务器 的结构体
    memset(&serv_addr, 0, serv_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    //将套接字绑定到服务器上
    bind(lfd, (struct sockaddr *)&serv_addr, serv_len);

    //设置同时监听的最大连接数
    listen(lfd, 36);
    printf("Start accept......\n");


    struct sockaddr_in client_addr; //客户端地址
    socklen_t client_len = sizeof(client_addr);


    //最大文件描述符
    int maxfd = lfd;
    //文件描述符读集合
    fd_set reads, temp;
    //init
    FD_ZERO(&reads);
    FD_SET(lfd, &reads);
    while(1){
        //委托内核做IO检测
        temp = reads; //保证temp是最新的
        int ret = select(maxfd+1, &temp, NULL, NULL, NULL); //最后一个参数为NULL,阻塞,直到有一个以上文件描述符准备好才返回
        if(ret == -1){
            perror("select error");
            exit(1);
        }
        //客户端发起了新连接
        if(FD_ISSET(lfd, &temp)){
            //接受连接请求, --accept不阻塞
            int cfd = accept(lfd, (struct sockaddr *)&client_addr, &client_len);
            if(cfd == -1){
                perror("accept error");
                exit(1);
            }
            char ip[64];
            printf("new client IP: %s, Port: %d\n", 
                   inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(client_addr.sin_port));
            //将cfd加入到待检测的读集合中 -- 下一次就可以检测到了
            FD_SET(cfd, &reads);
            //更新最大文件描述符
            maxfd = maxfd < cfd ? cfd : maxfd;
        }
        //已经连接上来的客户端给我发数据
        for(int i = lfd + 1; i <= maxfd; ++i){
            if(FD_ISSET(i, &temp)){
                char buf[1024] = {0};
                int len = recv(i, buf, sizeof(buf), 0);
                if(len == -1){
                    perror("recv error");
                    exit(1);
                }
                else if(len == 0) {
                    printf("客户端已经断开连接\n");
                    close(i);
                    //从读集合中删掉
                    FD_CLR(i, &reads);
                }
                else{
                    //正常的数据接收和发送
                    printf("recv buf: %s\n", buf);
                    send(i, buf, strlen(buf), 0);
                }
            }
        }
    }

    return 0;
}

