#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){

    //创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket error");
        exit(1);
    }
    //绑定server的ip和端口
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8787);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(fd, (struct sockaddr*)&serv, sizeof(serv));
    if(ret == -1){
        perror("bind err");
        exit(1);
    }

    //初始化客户端地址信息
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9898);
    //使用广播地址给客户端发送数据
    inet_pton(AF_INET, "192.168.1.255", &client.sin_addr.s_addr);

    //给服务器开启广播权限
    int flag = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));

    //通信
    while(1){
        //一直给客户端发数据
        static int num = 0;
        char buf[1024] = {0};
        sprintf(buf, "hello, udp == %d\n", num++);
        int ret = sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*)&client, sizeof(client));
        if(ret == -1){
            perror("sendto err");
            break;
        }
        printf("server == send buf: %s\n", buf);

        sleep(1);

    }
    close(fd);

    return 0;
}