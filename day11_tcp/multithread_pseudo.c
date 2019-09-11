/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-10 12:04:48
 */


typedef struct sockInfo{
    pthread_t id;
    int fd;
    struct sockaddr_in addr;
}SockInfo;

void *worker(void *arg){
    while(1){
        //打印客户端ip和port
        read();
        write();
    }
}

int main(){
    //监听
    int lfd = socket();

    //绑定
    bind();

    //设置监听
    listen();

    SockInfo sock[256];

    //父线程
    while(1){
        sock[i].fd = accept(lfd, &sock[i].addr, &len);
        //创建子线程
        pthread_create(&sock[i].id, NULL, worker, (void *)&sock[i]);
        pthread_deatch(sock[i].id);

    }
}