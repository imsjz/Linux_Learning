/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-05 12:14:32
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"

int main(void){

    int lfd;
    int cfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    char buf[BUFSIZ];
    int n;

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(lfd, 32);
    client_addr_len = sizeof(client_addr);
    cfd = accept(lfd, (struct sockaddr*)&client_addr, &client_addr_len);

    while(1){
        n = read(cfd, buf, sizeof(buf));
        //把读来的小写转大写
        for(int i = 0; i < n; ++i){
            buf[i] = toupper(buf[i]);
        }
        write(cfd, buf, n);
    }


    close(lfd);
    close(cfd);

    return 0;
}