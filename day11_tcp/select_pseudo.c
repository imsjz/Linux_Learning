

int main()
{
    int lfd = socket();
    bind();
    listen();

    //创建一文件描述符表
    fd_set reads, temp;
    //初始化
    FD_ZERO(&reads);
    //监听的lfd加入reads集合中
    FD_SET(lfd, &reads);
    int maxfd = lfd;

    while(1){
        //委托检测
        temp = reads;
        select(maxfd+1, &temp, NULL, NULL, NULL);

        //判断是不是监听的
        if(FD_ISSET(lfd, &temp)){
            //如果进来,则表明内核将temp改了,检测到变化了
            //所以接受新连接
            int cfd = accpet();
            //把cfd加入读集合
            FD_SET(cfd, &reads);
            //更新maxfd
            maxfd = maxfd < cfd ? cfd:maxfd;
        }
        //接收客户端发送数据
        for(int i = lfd + 1; i <= maxfd; ++i){
            if(FD_ISSET(i, &temp)){
                int len = read();
                if(len == 0){
                    //cfd从读集合中删除
                    FD_CLR(i, &reads);
                }
                write();
            }
        }
    }
    return 0;
}

