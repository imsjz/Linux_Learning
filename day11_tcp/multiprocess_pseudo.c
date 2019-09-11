/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-09 15:24:55
 */

void recycle(int num){
    while(waitpid(-1, NULL, wnohang) > 0); // WNOHANG     return immediately if no child has exited.
}

int main(){
    //监听
    int lfd = socket();
    //绑定
    bind();
    //设置监听
    listen();

    //用信号回收子进程
    struct sigaction act;
    act.sa_handler = recycle; //处理函数
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    //父进程
    while(1){
        int cfd = accept();
        //创建子进程
        pid_t pid = fork();
        //子进程
        if(pid == 0){
            close(lfd);
            //通信
            while(1){
                int len = read();
                if(len == -1){
                    exit(1);
                }
                else if(len == 0){
                    close(cfd);
                    break;
                }
                else{
                    write();
                }
            }
            //退出子进程
            return 0; //exit(1);
        }
        else{
            //父进程
            close(cfd);
        }
    }
}