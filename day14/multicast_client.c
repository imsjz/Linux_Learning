/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-18 22:00:17
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){

    //创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket error");
        exit(1);
    }
    //绑定server的ip和端口
    struct sockaddr_in cli;
    memset(&cli, 0, sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_port = htons(9898); //绑定端口
    cli.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(fd, (struct sockaddr*)&cli, sizeof(cli));
    if(ret == -1){
        perror("bind err");
        exit(1);
    }

    //加入到组播地址
    struct ip_mreqn fl;
    inet_pton(AF_INET, "239.0.0.10", &fl.imr_multiaddr.s_addr);
    inet_pton(AF_INET, "0.0.0.0", &fl.imr_address.s_addr);
    fl.imr_ifindex = if_nametoindex("enp5s0");
    setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &fl, sizeof(fl));



    //通信
    while(1){
        char buf[1024] = {0};
        int len = recvfrom(fd, buf, sizeof(buf), 0, 
                NULL, NULL);
        if(len == -1){
            perror("recvfrom err");
            break;
        }
        printf("client == recv buf: %s\n", buf);
    }
    close(fd);

    return 0;
}