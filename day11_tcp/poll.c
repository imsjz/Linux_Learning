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
#include <poll.h>



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

     //poll结构体
     struct pollfd allfd[1024];

     int max_index = 0;

     //init
     for(int i = 0; i < 1024; ++i){
         allfd[i].fd = -1;
         allfd[i].events = POLLIN;
     }
    allfd[0].fd = lfd; //第一个为监听连接的描述符


    while(1){
        int i = 0;
        int ret = poll(allfd, max_index+1, -1);
        if(ret == -1){
            perror("poll error");
            exit(1);
        }
        //测试监听描述符是否准备好
        if(allfd[0].revents & POLLIN){ //按位与,如果某个位为1,肯定大于0
            //接受连接请求
            int cfd = accept(lfd, (struct sockaddr*)&client_addr, &client_len);
            printf("==============\n");

            //cfd添加到poll数组
            for(i = 0; i < 1024; ++i){
                if(allfd[i].fd == -1){
                    allfd[i].fd = cfd;
                    break;
                }
            }
            //更新最后一个元素的下标
            max_index = max_index < i ? i : max_index;
        }

        //上面是处理新的连接,现在遍历allfd数组,进行数据的处理
        for(i = 1; i <= max_index; ++i){
            int fd = allfd[i].fd;
            if(fd == -1){
                //如果fd等于-1,说明这个并没有连接
                continue;
            }
            if(allfd[i].revents & POLLIN){
                //说明客户端发送数据过来
                char buf[1024] = {0}; //最好初始化为0,不初始化会有问题.
                int len = recv(fd, buf, sizeof(buf), 0); //这个len,会把换行符吃掉
                if(len == -1){
                    perror("recv error");
                    exit(1);
                }
                else if(len == 0){
                    printf("客户端主动断开了连接\n");
                    allfd[i].fd = -1;
                    close(fd);
                }
                //正常处理
                else{
                    printf("recv buf = %s", buf);
                    printf("recv buf length = %d\n", len);
                    printf("the strlen of buf = %ld\n", strlen(buf));
                    for(int k = 0; k < len; ++k){ //len不包含'\0'
                        buf[k] = toupper(buf[k]);
                    }
                    printf("buf toupper: %s\n", buf);
                    send(fd, buf, len, 0);
                }

            }
        }
    }

    return 0;
}

