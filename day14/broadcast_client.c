/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-18 20:52:00
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket error");
        exit(1);
    }
    //绑定地址
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(9898);
    inet_pton(AF_INET, "0.0.0.0", &client.sin_addr.s_addr);
    //我忘记绑定了..
    int ret = bind(fd, (struct sockaddr*)&client, sizeof(client));

    //通信
    while(1){

        char buf[1024] = {0};
        int len = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        if(len == -1){
            perror("recv err");
            break;
        }
        else if(len > 0){
            printf("recv from : %s\n", buf);
        }
    }
    close(fd);

    return 0;
}