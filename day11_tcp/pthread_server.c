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
#include <pthread.h>


typedef struct sockInfo{
    pthread_t pid;
    int fd;
    struct sockaddr_in addr;
}sockInfo;

void *worker(void *arg){
    sockInfo *info = (sockInfo*)arg;
    //通信
    char ip[64];
    char buf[1024];
    while(1){
        printf("Client IP: %s, port: %d\n", 
                inet_ntop(AF_INET, &info->addr.sin_addr.s_addr, ip, sizeof(ip)), 
                ntohs(info->addr.sin_port));
        int len = read(info->fd, buf, sizeof(buf));
        if(len == -1){
            perror("read error");
            pthread_exit(NULL);
        }
        else if(len == 0){
            printf("客户端断开了连接\n");
            close(info->fd);
            break;
        }
        else{
            printf("recv buf: \n");
            write(STDOUT_FILENO, buf, len);
            write(info->fd, buf, len);
        }
    }

    return NULL;
}


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

    //设置端口复用
    int flag = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

    //将套接字绑定到服务器上
    bind(lfd, (struct sockaddr *)&serv_addr, serv_len);

    //设置同时监听的最大连接数
    listen(lfd, 36);
    printf("Start accept......\n");




    int i = 0;
    sockInfo info[256];
    //规定 fd = -1
    for(i = 0; i < sizeof(info) / sizeof(info[0]); ++i){
        info[i].fd = -1;
    }
    socklen_t client_len = sizeof(struct sockaddr_in);



    while(1){
        //选一个没有被使用的，最小的数组元素
        for(i = 0; i < 256; ++i){
            if(info[i].fd == -1)
                break;
        }

        if(i == 256){
            break;
        }

        //主线程 -- 等待接收连接请求
        info[i].fd = accept(lfd, (struct sockaddr*)&info[i].addr, &client_len);

        //创建子线程 -- 通信
        pthread_create(&info[i].pid, NULL, worker, &info[i]);

        //设置分离线程
        pthread_detach(info[i].pid);
    }


    close(lfd);
    //只退出主线程,在main创建的主线程中使用pthread_exit，会退出这个主线程，但是其他共享的资源并没有释放；如果使用exit，那么资源释放了，其他线程就会出错。
    pthread_exit(NULL);
    
    return 0;
}

