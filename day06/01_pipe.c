#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if(pid == 0){
        //son
        sleep(3);
        write(fd[1], "hello", 5);
    }
    else if(pid > 0){
        char buf[12] = {0};
        int ret = read(fd[0], buf, sizeof(buf)); //read读设备是阻塞等待的，读文件不是
        if(ret > 0){
            write(STDOUT_FILENO, buf, ret);
        }
    }
    return 0;
}